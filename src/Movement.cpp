#include <sstream>
#include <cassert>
#include "log.h"
#include "Movement.h"
#include "Mobile.h"
#include "Transform.h"
#include "Collider.h"

// Max speed multiplier (in case FPS fall to low)
static const float MULT_LIMIT = 5.0f;

Movement::Movement(string const &name):
  System( name), prev_(-1) {
}

Movement::~Movement() {
}

void
Movement::init( EntityManager&) {
}

void
Movement::update(EntityManager &em, int now) {
  clearCollisions(em);

  int delta = (prev_ == -1) ? 0 : (now - prev_);
  float mult = delta / 16.666f;
  if (mult > MULT_LIMIT) {
    mult = MULT_LIMIT;
  }
  
  TEntityList entities = em.getEntities(Mobile::TYPE, Transform::TYPE);
  for (TEntityIterator it = entities.begin(); it < entities.end(); ++it) {
    Entity *entity = *it;
    Mobile *m = entity->getComponent<Mobile>();
    Transform *t = entity->getComponent<Transform>();

    // First, try to do the move
    float dx = m->getSpeedX() * mult;
    float dy = m->getSpeedY() * mult;

    float dxAllowed = dx;
    float dyAllowed = dy;
    bool moveAllowed = true;
    if (entity->hasComponent(Collider::TYPE)) {
      Collider *col = entity->getComponent<Collider>();
      if (col->isSolid()) {
        moveAllowed = resolveCollisions(em, entity, col, dx, dy,
                                        dxAllowed, dyAllowed);
      }
    }
    t->moveBy(dxAllowed, dyAllowed);
  }
  
  prev_ = now;
}

void
Movement::clearCollisions(EntityManager &em) const {
  TEntityList entities = em.getEntities(Collider::TYPE);
  for (TEntityIterator it = entities.begin(); it < entities.end(); ++it) {
    Collider *coll = (*it)->getComponent<Collider>();
    coll->clearCollisions();
  }
}

bool
Movement::resolveCollisions(EntityManager &em, Entity *ecol, Collider *col,
                            float dx, float dy,
                            float &dxAllowed, float &dyAllowed) const {
  bool moveAllowed = true;

  TEntityList allColl = em.getEntities(Collider::TYPE);
  for (TEntityIterator it = allColl.begin(); it < allColl.end(); ++it) {
    Entity *ecol2 = *it;
    if (ecol2 == ecol) {
      continue; // Don't collide with myself
    }
    Collider *col2 = ecol2->getComponent<Collider>();
    if (Movement::collide(ecol, col, ecol2, col2,
                          dx, dy, dxAllowed, dyAllowed)) {
      col->addCollision(ecol2);
    }
  }
  return moveAllowed;
}

bool
Movement::overlap(float minx1, float maxx1, float miny1, float maxy1,
                  float minx2, float maxx2, float miny2, float maxy2) {
  if ((minx1 > maxx2) || (minx2 > maxx1)) {
    return false;
  }
  if ((miny1 > maxy2) || (miny2 > maxy1)) {
    return false;
  }
  return true;
}

bool
Movement::collide(Entity *ecol1, Collider *col1, Entity *ecol2, Collider *col2,
                  float dx, float dy, float &dxAllowed, float &dyAllowed) {
  assert(ecol1->hasComponent(Collider::TYPE));
  assert(ecol2->hasComponent(Collider::TYPE));
  Transform *t1 = ecol1->getComponent<Transform>();
  Transform *t2 = ecol2->getComponent<Transform>();
  float minx1 = t1->getX() - col1->getLeft();
  float minx2 = t2->getX() - col2->getLeft();
  float maxx1 = t1->getX() + col1->getRight();
  float maxx2 = t2->getX() + col2->getRight();
  float miny1 = t1->getY() - col1->getTop();
  float miny2 = t2->getY() - col2->getTop();
  float maxy1 = t1->getY() + col1->getBottom();
  float maxy2 = t2->getY() + col2->getBottom();
  bool collide = overlap(minx1 + dx, maxx1 + dx, miny1 + dy, maxy1 + dy,
                         minx2, maxx2, miny2, maxy2);

  if (collide) {
    if (overlap(minx1 + dxAllowed, maxx1 + dxAllowed,
                miny1 + dyAllowed, maxy1 + dyAllowed,
                minx2, maxx2, miny2, maxy2)) {
      if (!overlap(minx1, maxx1,
                   miny1 + dyAllowed, maxy1 + dyAllowed,
                   minx2, maxx2, miny2, maxy2)) {
        dxAllowed = 0;
        
      } else if (!overlap(minx1 + dxAllowed, maxx1 + dxAllowed,
                          miny1, maxy1,
                          minx2, maxx2, miny2, maxy2)) {
        dyAllowed = 0;
        
      } else {
        dxAllowed = 0;
        dyAllowed = 0;
      }
    }
  }
  return collide;
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
