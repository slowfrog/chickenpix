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
  CL_KEY_ESCAPE
};

CLInputState::CLInputState(CL_InputDevice *keyboard):
  keyboard_(keyboard) {
}

bool
CLInputState::isKeyDown(Key const k) const {
  return keyboard_->get_keycode(KEYMAP[k]);
}

bool
CLInputState::isButtonDown(MouseButton const b) const {
  // TODO
  return false;
}

InputState::MousePos
CLInputState::getMousePosition() const {
  return MousePos({0, 0});
}
