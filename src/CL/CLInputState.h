#pragma once

#include "../InputState.h"

class CL_InputDevide;

class CLInputState: public InputState {
private:
  VisualContext &vc_;
  CL_InputDevice *keyboard_;
  CL_InputDevice *mouse_;
  
public:
  CLInputState(VisualContext &vc, CL_InputDevice *keyboard,
               CL_InputDevice *mouse);
  
  inline
  virtual ~CLInputState() {
  }

  virtual VisualContext &getVisualContext() const;
  virtual bool isKeyDown(Key k) const;
  virtual bool isButtonDown(MouseButton b) const;
  virtual MousePos getMousePosition() const;
};
