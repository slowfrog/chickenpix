#include <sstream>
#include <cassert>
#include "log.h"
#include "Movement.h"
#include "Mobile.h"
#include "Transform.h"
#include "Collider.h"

Movement::Movement(string const &name):
  System( name) {
}

Movement::~Movement() {
}

void
Movement::init( EntityManager&) {
}

void
Movement::update(EntityManager &em, int now) {
  TEntityList entities = em.getEntities(Mobile::TYPE, Transform::TYPE);
  for (TEntityIterator it = entities.begin(); it < entities.end(); ++it) {
    Entity *entity = *it;
    Mobile *m = entity->getComponent<Mobile>();
    Transform *t = entity->getComponent<Transform>();

    bool moveAllowed = true;
    if (entity->hasComponent(Collider::TYPE)) {
      Collider *col = entity->getComponent<Collider>();
      if (col->isSolid()) {
        TEntityList colls = findCollisions( em, entity, col);
        if (colls.size() > 0) {
          LOG2 << "COLLISION\n";
        }
      }
    }

    if (moveAllowed) {
      t->moveBy(m->getSpeedX(), m->getSpeedY());
    }
  }
}

TEntityList
Movement::findCollisions(EntityManager &em, Entity *ecol, Collider *col) const {
  TEntityList collisions;
  
  TEntityList allColl = em.getEntities(Collider::TYPE);
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
Movement::exit( EntityManager&) {
}

string
Movement::toString() const {
  ostringstream out;
  out << "{Movement-System name=" << getName() << "}" << ends;
  return out.str();
}
