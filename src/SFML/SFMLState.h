#pragma once
#include <SFML/Graphics.hpp>
#include "../Component.h"

class SFMLState: public Component {
private:
  sf::RenderWindow &window;

public:
  static const Type TYPE = SFMLSTATE_TYPE;

  SFMLState(sf::RenderWindow &window);
  virtual ~SFMLState();

  sf::RenderWindow &getWindow();

  virtual string toString() const;
};
