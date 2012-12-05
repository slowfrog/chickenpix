/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
