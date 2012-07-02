#pragma once

#include "../InputState.h"

namespace sf {
  class RenderWindow;
};

class SFMLInputState: public InputState {
private:
  sf::RenderWindow *window_;
  
public:
  SFMLInputState(sf::RenderWindow *window);
  
  inline
  virtual ~SFMLInputState() {
  }

  virtual bool isKeyDown(Key k) const;
  virtual bool isButtonDown(MouseButton) const;
  virtual MousePos getMousePosition() const;
};
