#pragma once
#include "SFML.h"

#include "../Inputs.h"
#include "SFMLInputState.h"

class SFMLInputs: public Inputs {
private:
  sf::RenderWindow *window_;
  SFMLInputState *state_;
public:
  SFMLInputs( string const &name);
  virtual ~SFMLInputs();

  virtual void init ( EntityManager&);
  virtual void exit ( EntityManager&);
  
  virtual void pumpEvents();
  
  virtual InputState const *getInputState() const;

  virtual string toString() const;
};
