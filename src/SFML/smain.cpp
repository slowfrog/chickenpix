#include <iostream>
#include "SFML.h"
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
#include "SFMLSystemFactory.h"
#include "../Main.h"

#include "../EntityBuilder.h"
#include "../SystemManager.h"

#ifndef _WINDOWS_
#include <unistd.h>
#endif

using namespace std;

// Interface to SFML timing functions
class SFMLTimer{
private:
  sf::Clock clock_;
  
public:
  int getTime() {
    return (int) floor(1000 * clock_.GetElapsedTime());
  }
  
  void sleep(int time) {
    sf::Sleep(time / 1000.0f);
  }
};

int main(int argc, char const *argv[]) {
  SFMLSystemFactory *pSFMLFactory(NULL);
  try {
    pSFMLFactory = new SFMLSystemFactory;
    assert( pSFMLFactory );
    runGame<SFMLTimer>( pSFMLFactory);
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
  
  // Delete unused pointer(s)
  if ( pSFMLFactory ){
    delete pSFMLFactory;
  }

  // Exit
  return 0;
}
