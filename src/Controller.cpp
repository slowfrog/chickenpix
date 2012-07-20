#include <sstream>
#include "Controller.h"

Controller::Controller(const string &name):
  Component(Controller::TYPE) {
  addName(name);
}

Controller::~Controller() {
}

void
Controller::addName(const string &name) {
  for (vector<string>::const_iterator it = names_.begin(); it < names_.end();
       ++it) {
    if (name == *it) {
      return;
    }
  }
  names_.push_back(name);
}

void
Controller::removeName(const string &name) {
  for (vector<string>::iterator it = names_.begin(); it < names_.end();
       ++it) {
    if (name == *it) {
      names_.erase(it);
      return;
    }
  }
}

string
Controller::toString() const {
  ostringstream out;
  out << "{Controller [ ";
  for (vector<string>::const_iterator it = names_.begin(); it < names_.end();
       ++it) {
    out << (*it) << " ";
  }
  out << "]}" << ends;
  return out.str();
}
