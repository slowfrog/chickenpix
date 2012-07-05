#include <sstream>
#include "Collider.h"

Collider::Collider(bool solid, float size):
  Component(TYPE), solid_(solid), size_(size), collisions_() {
}

Collider::~Collider() {
}

void
Collider::clearCollisions() {
  collisions_.clear();
}

void
Collider::addCollision(Entity *entity) {
  collisions_.push_back(entity);
}

const TEntityList &
Collider::getCollisions() const {
  return collisions_;
}

string
Collider::toString() const {
  ostringstream out;
  out << "{Collider " << (solid_ ? "solid" : "not solid") << " size=" <<
    size_ << " collisions:" << collisions_.size() << "}" << ends;
  return out.str();
}
