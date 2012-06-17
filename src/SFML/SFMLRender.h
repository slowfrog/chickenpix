#include <SFML/Graphics.hpp>
#include "System.h"

class SFMLRender: public System {
public:
  sf::RenderWindow *window;
  
public:
  SFMLRender(string const &name, EntityManager &em);
  virtual ~SFMLRender();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  virtual string toString() const;
};
