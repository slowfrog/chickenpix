#include <sstream>
#include "Movement.h"
#include "Mobile.h"
#include "Transform.h"

Movement::Movement(string const &name, EntityManager &em):
  System(name, em) {
}

Movement::~Movement() {
}

void
Movement::init() {
}

void
Movement::update(int now) {
  vector<Entity *>entities = _em.getEntities(Mobile::TYPE, Transform::TYPE);
  for (vector<Entity *>::iterator it = entities.begin(); it < entities.end(); ++it) {
    Entity *entity = *it;
    Mobile *m = entity->getComponent<Mobile>();
    Transform *t = entity->getComponent<Transform>();
    t->moveBy(m->getSpeedX(), m->getSpeedY());
  }
}

void
Movement::exit() {
}

string
Movement::toString() const {
  ostringstream out;
  out << "{Movement-System name=" << getName() << "}" << ends;
  return out.str();
}
