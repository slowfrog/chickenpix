#include <sstream>
#include <cassert>
#include "log.h"
#include "Movement.h"
#include "Mobile.h"
#include "Transform.h"
#include "Collider.h"

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
  TEntityList entities = _em.getEntities(Mobile::TYPE, Transform::TYPE);
  for (TEntityIterator it = entities.begin(); it < entities.end(); ++it) {
    Entity *entity = *it;
    Mobile *m = entity->getComponent<Mobile>();
    Transform *t = entity->getComponent<Transform>();

    // First, try to do the move
    float prevX = t->getX();
    float prevY = t->getY();
    t->moveBy(m->getSpeedX(), m->getSpeedY());

    bool moveAllowed = true;
    if (entity->hasComponent(Collider::TYPE)) {
      Collider *col = entity->getComponent<Collider>();
      if (col->isSolid()) {
        moveAllowed = resolveCollisions(entity, col);
      }
    }

    // If collision detected that the move was not allowed, revert to the
    // previous position
    if (!moveAllowed) {
      t->moveTo(prevX, prevY);
    }
  }
}

bool
Movement::resolveCollisions(Entity *ecol, Collider *col) const {
  bool moveAllowed = true;
  TEntityList colls = findCollisions(ecol, col);
  for (TEntityIterator it = colls.begin(); it < colls.end(); ++it) {
    Collider *coll = (*it)->getComponent<Collider>();
    if (coll->isSolid()) {
      moveAllowed = false;
    }
    col->addCollision(*it);
  }
  return moveAllowed;
}

TEntityList
Movement::findCollisions(Entity *ecol, Collider *col) const {
  TEntityList collisions;
  
  TEntityList allColl = _em.getEntities(Collider::TYPE);
  for (TEntityIterator it = allColl.begin(); it < allColl.end(); ++it) {
    Entity *ecol2 = *it;
    if (ecol2 == ecol) {
      continue; // Don't collide with myself
    }
    Collider *col2 = ecol2->getComponent<Collider>();
    if (Movement::collide(ecol, col, ecol2, col2)) {
      collisions.push_back(ecol2);
    }
  }
  return collisions;
}

bool
Movement::collide(Entity *ecol1, Collider *col1, Entity *ecol2, Collider *col2) {
  assert(ecol1->hasComponent(Collider::TYPE));
  assert(ecol2->hasComponent(Collider::TYPE));
  Transform *t1 = ecol1->getComponent<Transform>();
  Transform *t2 = ecol2->getComponent<Transform>();
  float minx1 = t1->getX() - (col1->getSize() / 2);
  float minx2 = t2->getX() - (col2->getSize() / 2);
  float maxx1 = minx1 + col1->getSize();
  float maxx2 = minx2 + col2->getSize();
  if ((minx1 > maxx2) || (minx2 > maxx1)) {
    return false;
  }
  
  float miny1 = t1->getY() - (col1->getSize() / 2);
  float miny2 = t2->getY() - (col2->getSize() / 2);
  float maxy1 = miny1 + col1->getSize();
  float maxy2 = miny2 + col2->getSize();
  if ((miny1 > maxy2) || (miny2 > maxy1)) {
    return false;
  }

  return true;
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
