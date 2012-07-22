#include <sstream>
#include "Collider.h"
#include "ComponentRegistry.h"

Component::Type
Collider::TYPE = COLLIDER_TYPE;

Collider::Collider(bool solid, float size):
  Component(TYPE), solid_(solid),
  left_(size), top_(size), right_(size), bottom_(size), 
  collisions_() {
}

Collider::Collider(bool solid, float left, float top, float right, float bottom):
  Component(TYPE), solid_(solid),
  left_(left), top_(top), right_(right), bottom_(bottom), 
  collisions_() {
}

Collider::~Collider() {
}

void
Collider::clearCollisions() {
  collisions_.clear();
}

void
Collider::addCollision(Entity *entity) {
  collisions_.push_back(entity->getId());
}

const TEntityIdList &
Collider::getCollisions() const {
  return collisions_;
}

string
Collider::toString() const {
  ostringstream out;
  out << "{Collider " << (solid_ ? "solid" : "not solid") << " left=" <<
    left_ << " top=" << top_ << " right=" << right_ << " bottom=" << bottom_ <<
    " collisions:" << collisions_.size() << "}" << ends;
  return out.str();
}
