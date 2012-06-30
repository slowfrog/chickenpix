#include <iostream>
#include <sstream>
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

void
Render::update(int now) {
  int delta = (last == -1) ? 0 : (now - last);
  last = now;
  
  VisualContext *vc = getVisualContext();
  clear(*vc);

  // The point of view is computed with:
  // - the position of the entity having the Camera component
  // - offset by the specific camera position
  // - centered on the screen
  Entity *cameraEntity = _em.getEntity(Camera::TYPE);
  Camera *camera = cameraEntity->getComponent<Camera>();
  Transform *transform = cameraEntity->getComponent<Transform>();
  float offsetX = transform->getX() + camera->getOffsetX() - (vc->getWidth() / 2);
  float offsetY = transform->getY() + camera->getOffsetY() - (vc->getHeight() / 2);
  
  // Visual
  vector<Entity *> visuals = _em.getEntities(BVisual::TYPE, Transform::TYPE);
  for (vector<Entity *>::iterator it = visuals.begin(); it < visuals.end(); it++) {
    Entity *entity = *it;
    Transform *t = entity->getComponent<Transform>();
    BVisual *v = entity->getComponent<BVisual>();

    v->draw(*vc, t->getX() - offsetX, t->getY() - offsetY, delta);
  }

  paint(*vc);
  delete vc;
}


string
Render::toString() const {
  ostringstream out;
  out << "{Render-system name=" << getName() << ends;
  return out.str();
}
