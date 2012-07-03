#include "Controller.h"

Controller::Controller(const string &name):
  Component(Controller::TYPE), name_(name) {
}

Controller::~Controller() {
}

string
Controller::toString() const {
  return "{Controller " + name_ + "}";
}
