#pragma once
#include "SFML.h"

#include "../Inputs.h"
#include "SFMLInputState.h"

class SFMLInputs: public Inputs {
private:
  sf::RenderWindow *window_;
  SFMLInputState *state_;
public:
  SFMLInputs(string const &name, EntityManager &em);
  virtual ~SFMLInputs();

  virtual void init();
  virtual void pumpEvents();
  virtual void exit();
  virtual InputState const *getInputState() const;

  virtual string toString() const;
};
