#include <iostream>
#include <SFML/System.hpp>
#include "log.h"
#include "../Animation.h"
#include "../EntityManager.h"
#include "../Scripting.h"
#include "SFMLInputs.h"
#include "SFMLLoader.h"
#include "SFMLRender.h"

#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[]) {
  // init log
  ILog::setLogger( new CLogOutput, LEVEL_DEBUG);
  
  char buffer[528];
  /* Get the current working directory: */
  if( getcwd( buffer, 527 ) == NULL ){}
  
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
  //LOG( em.toString() );
  LOG2DBG << em.toString() << "\n"; // (exemple dutilisation)
  LOG2MAIN<< em.toString() << "\n"; // pas affiché

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
