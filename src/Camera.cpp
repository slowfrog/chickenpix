#include "Camera.h"

Camera::Camera():
  Component(Camera::TYPE), offsetX_(0.0f), offsetY_(0.0f) {
}

Camera::Camera(float offsetX, float offsetY):
  Component(Camera::TYPE), offsetX_(offsetX), offsetY_(offsetY) {
}

Camera::~Camera() {
}

string
Camera::toString() const {
  return "{Camera}";
}
