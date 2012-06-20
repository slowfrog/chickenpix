#include <iostream>
#include <sstream>
#include "Transform.h"
#include "Render.h"
#include "BVisual.h"
#include "VisualContext.h"

Render::Render(string const &name, EntityManager &em):
  System(name, em) {
}

Render::~Render() {
}

void
Render::update(int now) {
  VisualContext *vc = getVisualContext();

  clear(*vc);
  
  // Visual
  vector<Entity *> visuals = em.getEntities(BVisual::TYPE, Transform::TYPE);
  for (vector<Entity *>::iterator it = visuals.begin(); it < visuals.end(); it++) {
    Entity *entity = *it;
    Transform *t = entity->getComponent<Transform>();
    BVisual *v = entity->getComponent<BVisual>();

    v->draw(*vc, t->getX(), t->getY());
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
