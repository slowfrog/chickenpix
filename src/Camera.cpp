#include <sstream>
#include "Camera.h"
#include "ComponentRegistry.h"

Component::Type
Camera::TYPE = CAMERA_TYPE;

Camera::Camera():
  Component(Camera::TYPE), offsetX_(0.0f), offsetY_(0.0f), width_(0), height_(0) {
}

Camera::Camera(float offsetX, float offsetY, unsigned int width, unsigned int height):
  Component(Camera::TYPE), offsetX_(offsetX), offsetY_(offsetY), width_(width), height_(height) {
}

Camera::~Camera() {
}

string
Camera::toString() const {
  ostringstream out;
  out << "{Camera offset=" << offsetX_ << "," << offsetY_ <<
    " size=" << width_ << "," << height_ <<  "}" << ends;
  return out.str();
}
