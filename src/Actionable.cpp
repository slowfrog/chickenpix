#include "log.h"
#include "Actionable.h"


Actionable::Actionable():
  Component(TYPE) {
}

Actionable::~Actionable() {
}

string
Actionable::toString() const {
  return "{Actionable}";
}

void
Actionable::setAction(const string &action) {
  LOG2 << "SETTING ACTION: " << action << "\n";
  action_ = action;
}

const string &
Actionable::getAction() const {
  return action_;
}

void
Actionable::clearAction() {
  action_ = "";
}
