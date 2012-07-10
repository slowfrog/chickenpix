#include "SystemFactory.h"

// Scripting
Scripting*
CSystemFactory::createScripting( const std::string &name){
  return new Scripting( name);
}

// Movement
Movement* 
CSystemFactory::createMovement( const std::string &name){
  return new Movement( name);
}

// Animation
Animation*
CSystemFactory::createAnimation( const std::string &name){
  return new Animation( name);
}

// Sounds
Sounds*
CSystemFactory::createSounds( const std::string &name){
  return new Sounds( name);
}



