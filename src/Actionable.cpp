#include "log.h"
#include "Actionable.h"
#include "ComponentRegistry.h"

Component::Type
Actionable::TYPE = ACTIONABLE_TYPE;

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
