#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Transform.h"
#include "Render.h"
#include "BVisual.h"
#include "Camera.h"
#include "Collider.h"
#include "MapInfo.h"
#include "VisualContext.h"

// z-order comparator
static bool
compareEntitiesOnZOrder(Entity * const &entity1, Entity * const &entity2) {
  BVisual *vis1 = entity1->getComponent<BVisual>();
  BVisual *vis2 = entity2->getComponent<BVisual>();
  return BVisual::compareZOrder(*vis1, *vis2);
}

Render::Render(string const &name):
  System( name), last( -1) {
}

Render::~Render() {
}

void
Render::applyCameraConstraints(EntityManager &em, Entity *cameraEntity) {
  Entity *mapEntity = em.getFirst(MapInfo::TYPE);
  if (!mapEntity) {
    return;
  }
  MapInfo *mapinfo = mapEntity->getComponent<MapInfo>();
  
  Camera *camera = cameraEntity->getComponent<Camera>();
  assert( camera);
  Transform *transform = cameraEntity->getComponent<Transform>();
  assert( transform);

  float halfWidth = camera->getWidth() / 2.0f;
  float cameraX = transform->getX() + camera->getOffsetX();
  if (cameraX - halfWidth < mapinfo->getMinX()) {
    camera->setOffsetX(mapinfo->getMinX() + halfWidth - transform->getX());
  } else if (cameraX + halfWidth > mapinfo->getMaxX()) {
    camera->setOffsetX(mapinfo->getMaxX() - halfWidth - transform->getX());
  }

  float halfHeight = camera->getHeight() / 2.0f;
  float cameraY = transform->getY() + camera->getOffsetY();
  if (cameraY - halfHeight < mapinfo->getMinY()) {
    camera->setOffsetY(mapinfo->getMinY() + halfHeight - transform->getY());
  } else if (cameraY + halfHeight > mapinfo->getMaxY()) {
    camera->setOffsetY(mapinfo->getMaxY() - halfHeight - transform->getY());
  }
}

void
Render::update( EntityManager &em, int now) {
  int delta = (last == -1) ? 0 : (now - last);
  last = now;
  
  VisualContext *vc = getVisualContext();
  clear(*vc);

  // The point of view is computed with:
  // - the position of the entity having the Camera component
  // - offset by the specific camera position
  // - clipped to the width and height of the view of the camera (if != 0)
  // - centered on the screen
  Entity *cameraEntity = em.getFirst(Camera::TYPE);
  assert( cameraEntity);
  
  Camera *camera = cameraEntity->getComponent<Camera>();
  assert( camera);

  // Save non-constrained camera offset (restored after drawing)
  float prevOffsetX = camera->getOffsetX();
  float prevOffsetY = camera->getOffsetY();
  applyCameraConstraints(em, cameraEntity);
  
  Transform *transform = cameraEntity->getComponent<Transform>();
  assert( transform);
  
  unsigned int width = (camera->getWidth() > 0 ?
                        camera->getWidth() :
                        vc->getWidth());
  unsigned int height = (camera->getHeight() > 0 ?
                         camera->getHeight() :
                         vc->getHeight());
  float offsetX = transform->getX() + camera->getOffsetX() - (width / 2);
  float offsetY = transform->getY() + camera->getOffsetY() - (height / 2);
  float minX = offsetX;
  float minY = offsetY;
  float maxX = minX + width;
  float maxY = minY + height;
  
  // Visual
  vector<Entity *> visuals = em.getEntities(BVisual::TYPE, Transform::TYPE);
  // Sort by z-order
  stable_sort(visuals.begin(), visuals.end(), compareEntitiesOnZOrder);

  int painted = 0;
  for (vector<Entity *>::iterator it = visuals.begin(); it < visuals.end(); it++) {
    Entity *entity = *it;
    Transform *t = entity->getComponent<Transform>();
    BVisual *v = entity->getComponent<BVisual>();

    float x0 = t->getX() - v->getCenterX();
    float y0 = t->getY() - v->getCenterY();
    if (!v->isGUI()) { // Non GUI element move with the camera
      if ((x0 > maxX) ||
          (y0 > maxY) ||
          (x0 + v->getWidth(*vc) < minX) ||
          (y0 + v->getHeight(*vc) < minY)) {
        continue; // Off screen: don't draw
      }
      painted++;
      if (entity->hasComponent(Collider::TYPE)) {
        Collider *coll = entity->getComponent<Collider>();
        v->debugDraw(*vc, x0 - offsetX, y0 - offsetY, delta,
                     coll->getLeft(), coll->getTop(),
                     coll->getRight(), coll->getBottom());
      } else {
        v->draw(*vc, x0 - offsetX, y0 - offsetY, delta);
      }
      
    } else { // GUI elements are fixed
      painted++;
      v->draw(*vc, x0, y0, delta);
    }
  }

  paint(*vc);
  delete vc;

  // Restore non-constrained camera offset
  camera->setOffsetX(prevOffsetX);
  camera->setOffsetY(prevOffsetY);
}


string
Render::toString() const {
  ostringstream out;
  out << "{Render-system name=" << getName() << ends;
  return out.str();
}
