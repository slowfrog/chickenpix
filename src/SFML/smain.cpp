#include <iostream>
#include <SFML/System.hpp>
#include "../log.h"
#include "../Animation.h"
#include "../EntityManager.h"
#include "../Movement.h"
#include "../Scripting.h"
#include "../TagEntityManager.h"
#include "SFMLInputs.h"
#include "SFMLLoader.h"
#include "SFMLRender.h"

#include "../EntityBuilder.h"

#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[]) {
  try{
    // init log
    ILog::setLogger( new CLogOutput, LEVEL_DEBUG);
    
    // Test tag => to remove
    CTagEntityMng::get()->resetTagCollection();
    CTagEntityMng::get()->registerTag(1, "Hero", true); // you can not have another tag hero
    CTagEntityMng::get()->registerTag(1, "Kindly");
    
    CTagEntityMng::get()->registerTag(10, "Bat");
    CTagEntityMng::get()->registerTag(11, "Bat");
    CTagEntityMng::get()->registerTag(12, "Bat");
    
    CTagEntityMng::get()->registerTag(20, "Frog");
    CTagEntityMng::get()->registerTag(20, "little");
    CTagEntityMng::get()->registerTag(20, "Jump");
    
    LOG2<< "Entity: "<<CTagEntityMng::get()->getEntityByTag( "Hero") <<"\n";
    LOG2<< "Entity: "<<CTagEntityMng::get()->getFirstEntityByTag( "Bat") <<"\n";
    
    CTagEntityMng::TCollectionIdEntity v = CTagEntityMng::get()->getEntitiesByTag("Bat");
    for(unsigned int i=0; i< v.size(); i++)
      LOG2<<"Entity : "<<v[i]<<"\n";
    
    CTagEntityMng::TCollectionTag vt = CTagEntityMng::get()->getTagsByEntity( 20);
    for(unsigned int i=0; i< vt.size(); i++)
      LOG2<<"Tag(s) : "<<vt[i]<<"\n";
    
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
    Movement movement("Movement", em);
    movement.init();
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
