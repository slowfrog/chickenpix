#pragma once

#include "../InputState.h"

class VisualContext;
namespace sf {
  class RenderWindow;
};

class SFMLInputState: public InputState {
private:
  VisualContext &vc_;
  sf::RenderWindow *window_;
  
public:
  SFMLInputState(VisualContext &vc, sf::RenderWindow *window);
  
  inline
  virtual ~SFMLInputState() {
  }

  virtual VisualContext &getVisualContext() const;
  virtual bool isKeyDown(Key k) const;
  virtual bool isButtonDown(MouseButton) const;
  virtual MousePos getMousePosition() const;
};
