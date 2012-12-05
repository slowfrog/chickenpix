/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
