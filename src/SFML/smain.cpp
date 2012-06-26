#include <iostream>
#include <SFML/System.hpp>
#include "../Animation.h"
#include "../EntityManager.h"
#include "../Scripting.h"
#include "SFMLInputs.h"
#include "SFMLLoader.h"
#include "SFMLRender.h"

using namespace std;

int main(int argc, char const *argv[]) {

  // Init
  EntityManager em("SFML-main");
  SFMLRender sfrender("SFMLRender", em);
  sfrender.init();
  Animation anim("Animation", em);
  anim.init();
  SFMLInputs sfinputs("SFMLInput", em);
  sfinputs.init();
  SFMLLoader sfloader("SFMLLoader", em, "resources/resources.xml");
  sfloader.init();
  Scripting scripting("Scripting", em);
  scripting.init();
  cout << em.toString() << endl;

  // One step
  sf::Clock clock;
  int prev = (int) floor(1000 * clock.GetElapsedTime());
  while (true) {
    int now = (int) floor(1000 * clock.GetElapsedTime());
    
    // Process inputs
    sfinputs.update(now);
    if (sfinputs.isExitRequested()) {
      break;
    }

    scripting.update(now);
    anim.update(now);
    sfrender.update(now);

    prev = now;
    // Do ~60FPS
    sf::Sleep(0.015f);
  }
  scripting.exit();
  sfloader.exit();
  sfinputs.exit();
  anim.exit();
  sfrender.exit();

  // Exit
  
  return 0;
}
