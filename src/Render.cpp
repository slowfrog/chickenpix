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
  // - clipped to the width and height of the view of the camera (if != 0)
  // - centered on the screen
  Entity *cameraEntity = _em.getEntity(Camera::TYPE);
  Camera *camera = cameraEntity->getComponent<Camera>();
  Transform *transform = cameraEntity->getComponent<Transform>();
  float offsetX = transform->getX() + camera->getOffsetX() - (vc->getWidth() / 2);
  float offsetY = transform->getY() + camera->getOffsetY() - (vc->getHeight() / 2);
  float minX = offsetX;
  float minY = offsetY;
  unsigned int width = camera->getWidth() > 0 ? camera->getWidth() : vc->getWidth();
  unsigned int height = camera->getHeight() > 0 ? camera->getHeight() : vc->getHeight();
  float maxX = minX + width;
  float maxY = minY + height;
  
  // Visual
  vector<Entity *> visuals = _em.getEntities(BVisual::TYPE, Transform::TYPE);
  int painted = 0;
  for (vector<Entity *>::iterator it = visuals.begin(); it < visuals.end(); it++) {
    Entity *entity = *it;
    Transform *t = entity->getComponent<Transform>();
    BVisual *v = entity->getComponent<BVisual>();

    if (!v->isGUI()) { // Non GUI element move with the camera
      if ((t->getX() > maxX) || (t->getY() > maxY) ||
          (t->getX() + v->getWidth(*vc) < minX) || (t->getY() + v->getHeight(*vc) < minY)) {
        continue; // Off screen: don't draw
      }
      painted++;
      v->draw(*vc, t->getX() - offsetX, t->getY() - offsetY, delta);
      
    } else { // GUI elements are fixed
      painted++;
      v->draw(*vc, t->getX(), t->getY(), delta);
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
