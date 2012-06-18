#include <sstream>
#include "SFMLState.h"

SFMLState::SFMLState(sf::RenderWindow &window):
  Component(TYPE), window(window) {
}

SFMLState::~SFMLState() {
}

sf::RenderWindow &
SFMLState::getWindow() {
  return window;
}

string
SFMLState::toString() const {
  ostringstream out;
  out << "{SFMLState}" << ends;
  return out.str();
}
