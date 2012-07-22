#include <sstream>
#include "Transform.h"
#include "ComponentRegistry.h"

Component::Type
Transform::TYPE = TRANSFORM_TYPE;

Transform::Transform(float x, float y):
  Component(TYPE), x(x), y(y) {
}

Transform::~Transform() {
}

string
Transform::toString() const {
  ostringstream out;
  out << "{Transform x=" << x << ", y=" << y << "}" << ends;
  return out.str();
};
