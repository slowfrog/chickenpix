#include "Controller.h"

Controller::Controller():
  Component(Controller::TYPE) {
}

Controller::~Controller() {
}

string
Controller::toString() const {
  return "{Controller}";
}
