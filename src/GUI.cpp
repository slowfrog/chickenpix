#include "GUI.h"
#include "ComponentRegistry.h"

Component::Type
GUI::TYPE = GUI_TYPE;

GUI::GUI():
  Component(TYPE) {
}

GUI::~GUI() {
}

string
GUI::toString() const {
  return "{GUI}";
}
