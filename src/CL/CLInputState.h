#pragma once

#include "../InputState.h"

class CL_InputDevide;

class CLInputState: public InputState {
private:
  CL_InputDevice *keyboard_;
  CL_InputDevice *mouse_;
  
public:
  CLInputState(CL_InputDevice *keyboard, CL_InputDevice *mouse);
  
  inline
  virtual ~CLInputState() {
  }

  virtual bool isKeyDown(Key k) const;
  virtual bool isButtonDown(MouseButton b) const;
  virtual MousePos getMousePosition() const;
};
