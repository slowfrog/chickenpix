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
  SFMLInputs sfinputs("SFMLInput", em);
  sfinputs.init();
  SFMLLoader sfloader("SFMLLoader", em);
  sfloader.init();

  cout << em.toString() << endl;

  // One step
  sf::Clock clock;
  int prev = floor(1000 * clock.GetElapsedTime());
  while (true) {
    int now = floor(1000 * clock.GetElapsedTime());
    
    // Process inputs
    sfinputs.update(now);
    if (sfinputs.isExitRequested()) {
      break;
    }
        
    sfrender.update(now);

    prev = now;
    // Do ~60FPS
    sf::Sleep(0.015f);
  }
  sfloader.exit();
  sfinputs.exit();
  sfrender.exit();

  // Exit
  
  return 0;
}
