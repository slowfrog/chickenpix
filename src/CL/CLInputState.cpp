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
 
#include "CL.h"
#include "CLInputState.h"

static int KEYMAP[] = {
  CL_KEY_0,
  CL_KEY_1,
  CL_KEY_2,
  CL_KEY_3,
  CL_KEY_4,
  CL_KEY_5,
  CL_KEY_6,
  CL_KEY_7,
  CL_KEY_8,
  CL_KEY_9,
  CL_KEY_SPACE,
  CL_KEY_UP,
  CL_KEY_DOWN,
  CL_KEY_LEFT,
  CL_KEY_RIGHT,
  CL_KEY_ESCAPE,
  CL_KEY_TAB,
  CL_KEY_A,
  CL_KEY_B,
  CL_KEY_C,
  CL_KEY_D,
  CL_KEY_E,
  CL_KEY_F,
  CL_KEY_G,
  CL_KEY_H,
  CL_KEY_I,
  CL_KEY_J,
  CL_KEY_K,
  CL_KEY_L,
  CL_KEY_M,
  CL_KEY_N,
  CL_KEY_O,
  CL_KEY_P,
  CL_KEY_Q,
  CL_KEY_R,
  CL_KEY_S,
  CL_KEY_T,
  CL_KEY_U,
  CL_KEY_V,
  CL_KEY_W,
  CL_KEY_X,
  CL_KEY_Y,
  CL_KEY_Z,
  CL_KEY_ENTER
};

static int BUTTONMAP[] = {
  CL_MOUSE_LEFT,
  CL_MOUSE_RIGHT,
  CL_MOUSE_MIDDLE
};

CLInputState::CLInputState(VisualContext &vc, CL_InputDevice *keyboard,
                           CL_InputDevice *mouse):
  vc_(vc), keyboard_(keyboard), mouse_(mouse) {
}

VisualContext &
CLInputState::getVisualContext() const {
  return vc_;
}

bool
CLInputState::isKeyDown(Key const k) const {
  return keyboard_->get_keycode(KEYMAP[k]);
}

bool
CLInputState::isButtonDown(MouseButton const b) const {
  return mouse_->get_keycode(BUTTONMAP[b]);
}

InputState::MousePos
CLInputState::getMousePosition() const {
  return MousePos(mouse_->get_x(), mouse_->get_y());
}
