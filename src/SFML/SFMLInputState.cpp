#include "SFML.h"

#include "SFMLInputState.h"

static
sf::Key::Code KEYMAP[] = {
  sf::Key::Num0,
  sf::Key::Num1,
  sf::Key::Num2,
  sf::Key::Num3,
  sf::Key::Num4,
  sf::Key::Num5,
  sf::Key::Num6,
  sf::Key::Num7,
  sf::Key::Num8,
  sf::Key::Num9,
  sf::Key::Space,
  sf::Key::Up,
  sf::Key::Down,
  sf::Key::Left,
  sf::Key::Right,
  sf::Key::Escape,
};

SFMLInputState::SFMLInputState(sf::RenderWindow *window) :
  window_(window) {
}

bool
SFMLInputState::isKeyDown(Key const k) const {
  return window_->GetInput().IsKeyDown(KEYMAP[k]);
}

bool
SFMLInputState::isButtonDown(MouseButton const b) const {
  return false;
}

InputState::MousePos
SFMLInputState::getMousePosition() const {
  return MousePos({0, 0});
}
