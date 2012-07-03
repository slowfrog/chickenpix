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

static
sf::Mouse::Button BUTTONMAP[] = {
  sf::Mouse::Left,
  sf::Mouse::Right,
  sf::Mouse::Middle
};

SFMLInputState::SFMLInputState(VisualContext &vc, sf::RenderWindow *window) :
  vc_(vc), window_(window) {
}

VisualContext &
SFMLInputState::getVisualContext() const {
  return vc_;
}

bool
SFMLInputState::isKeyDown(Key const k) const {
  return window_->GetInput().IsKeyDown(KEYMAP[k]);
}

bool
SFMLInputState::isButtonDown(MouseButton const b) const {
  return window_->GetInput().IsMouseButtonDown(BUTTONMAP[b]);
}

InputState::MousePos
SFMLInputState::getMousePosition() const {
  return MousePos(window_->GetInput().GetMouseX(), window_->GetInput().GetMouseY());
}
