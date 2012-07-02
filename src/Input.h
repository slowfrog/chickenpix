#pragma once
#include "Component.h"

class InputState;

class Input: public Component {
private:
  InputState const *state_;
  
public:
  static const Type TYPE = INPUT_TYPE;

  Input();
  virtual ~Input();

  inline
  void setInputState(InputState const *state) {
    state_ = state;
  }

  inline
  InputState const *getInputState() const {
    return state_;
  }
  
  virtual string toString() const;
};
