#include <iostream>
#include <SFML/System.hpp>
#include "EntityManager.h"
#include "SFML/SFMLInputs.h"
#include "SFML/SFMLLoader.h"
#include "SFML/SFMLRender.h"

using namespace std;

int main(int argc, char const *argv[]) {

  // Init
  EntityManager em("main");
  SFMLRender sfrender("SFMLRender", em);
  sfrender.init();
  SFMLInputs sfinput("SFMLInput", em);
  sfinput.init();
  SFMLLoader sfloader("SFMLLoader", em);
  sfloader.init();

  cout << em.toString() << endl;

  // One step
  sf::Clock clock;
  int prev = floor(1000 * clock.GetElapsedTime());
  while (true) {
    int now = floor(1000 * clock.GetElapsedTime());
    if (now > 5000) {
      break;
    }
    sfinput.update(now);
    sfrender.update(now);

    prev = now;
    // Do ~60FPS
    sf::Sleep(0.015f);
  }

  sfrender.exit();

  // Exit
  
  return 0;
}
