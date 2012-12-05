/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
  sf::Key::Tab,
  sf::Key::A,
  sf::Key::B,
  sf::Key::C,
  sf::Key::D,
  sf::Key::E,
  sf::Key::F,
  sf::Key::G,
  sf::Key::H,
  sf::Key::I,
  sf::Key::J,
  sf::Key::K,
  sf::Key::L,
  sf::Key::M,
  sf::Key::N,
  sf::Key::O,
  sf::Key::P,
  sf::Key::Q,
  sf::Key::R,
  sf::Key::S,
  sf::Key::T,
  sf::Key::U,
  sf::Key::V,
  sf::Key::W,
  sf::Key::X,
  sf::Key::Y,
  sf::Key::Z,
  sf::Key::Return
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
