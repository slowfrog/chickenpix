#include <iostream>
#include <sstream>
#include <algorithm>
#include "Transform.h"
#include "Render.h"
#include "BVisual.h"
#include "Camera.h"
#include "VisualContext.h"

Render::Render(string const &name, EntityManager &em):
  System(name, em), last(-1) {
}

Render::~Render() {
}

static bool
compareEntitiesOnZOrder(Entity * const &entity1, Entity * const &entity2) {
  BVisual *vis1 = entity1->getComponent<BVisual>();
  BVisual *vis2 = entity2->getComponent<BVisual>();
  return BVisual::compareZOrder(*vis1, *vis2);
}


void
Render::update(int now) {
  int delta = (last == -1) ? 0 : (now - last);
  last = now;
  
  VisualContext *vc = getVisualContext();
  clear(*vc);

  // The point of view is computed with:
  // - the position of the entity having the Camera component
  // - offset by the specific camera position
  // - clipped to the width and height of the view of the camera (if != 0)
  // - centered on the screen
  Entity *cameraEntity = _em.getFirst(Camera::TYPE);
  Camera *camera = cameraEntity->getComponent<Camera>();
  Transform *transform = cameraEntity->getComponent<Transform>();
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
  vector<Entity *> visuals = _em.getEntities(BVisual::TYPE, Transform::TYPE);
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
      v->draw(*vc, x0 - offsetX, y0 - offsetY, delta);
      
    } else { // GUI elements are fixed
      painted++;
      v->draw(*vc, x0, y0, delta);
    }
  }

  paint(*vc);
  delete vc;

  //cout << "Painted: " << painted << "/" << visuals.size() << endl;
}


string
Render::toString() const {
  ostringstream out;
  out << "{Render-system name=" << getName() << ends;
  return out.str();
}
