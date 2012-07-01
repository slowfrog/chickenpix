#include <iostream>
#include <SFML/System.hpp>
#include "../log.h"
#include "../Animation.h"
#include "../EntityManager.h"
#include "../Movement.h"
#include "../Scripting.h"
#include "../TagEntityManager.h"
#include "../FightSystem.h"
#include "SFMLInputs.h"
#include "SFMLLoader.h"
#include "SFMLRender.h"

#include "../EntityBuilder.h"
#include "../SystemManager.h"

#ifndef _WINDOWS_
#include <unistd.h>
#endif

using namespace std;

int main(int argc, char const *argv[]) {
  try{
    // init log
    ILog::setLogger( new CLogOutput, LEVEL_DEBUG);
    CTagEntityMng::get()->resetTagCollection();
    
    // Init
    EntityManager em("SFML-main");
    SFMLRender sfrender("SFMLRender", em, 800, 600);
    sfrender.init();
    Animation anim("Animation", em);
    anim.init();
    SFMLInputs sfinputs("SFMLInput", em);
    sfinputs.init();
    SFMLLoader sfloader("SFMLLoader", em, "resources/resources.xml");
    sfloader.setEntitiesDesc( "resources/entities.xml");
    sfloader.init();
    Scripting scripting("Scripting", em);
    scripting.init();
    Movement movement("Movement", em);
    movement.init();
    
    //EntityManager emf("SFML-fight");
    //CFightSystem fight("FightSystem", emf);
    //fight.init();
    
    //CSystemManager::get()->createEntityManager( "SFML-fight");
    //CSystemManager::get()->registerSystem( "SFML-fight", &fight);
    
    //CSystemManager::destroy();
    
    //return 0;
    //cout << em.toString() << endl;
    LOG2<< em.toString() <<"\n";
    //LOG2<< emf.toString() <<"\n";
    
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
      movement.update(now);
      anim.update(now);
      sfrender.update(now);
      
      prev = now;
      // Do ~60FPS
      sf::Sleep(0.015f);
    }
    movement.exit();
    scripting.exit();
    sfloader.exit();
    sfinputs.exit();
    anim.exit();
    sfrender.exit();
  }
  catch (const std::string &msg) {
    LOG2<<"*** Exception with message : "<<msg<<" ***\n";
  }
  catch (int n) {
    LOG2<<"*** Exception with number : "<<n<<" ***\n";
  }
  catch (...) {
    LOG2<<"*** Unknown exception ***\n";
  }

  // Exit
  return 0;
}
