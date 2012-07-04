#include "SystemFactory.h"

// Scripting
Scripting*
CSystemFactory::createScripting( EntityManager &em, const std::string &name){
  return new Scripting( name, em);
}

// Movement
Movement* 
CSystemFactory::createMovement( EntityManager &em, const std::string &name){
  return new Movement( name, em);
}

// Animation
Animation*
CSystemFactory::createAnimation( EntityManager &em, const std::string &name){
  return new Animation( name, em);
}

// Sounds
Sounds*
CSystemFactory::createSounds( EntityManager &em, const std::string &name){
  return new Sounds( name, em);
}



