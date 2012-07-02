#include <cassert>
#include "SFMLLoader.h"
#include "SFMLRender.h"
#include "SFMLInputs.h"
#include "SFMLSystemFactory.h"


// Constructor destructor
SFMLSystemFactory::SFMLSystemFactory():CSystemFactory(){
}

SFMLSystemFactory::~SFMLSystemFactory(){
}

// Specific system
Loader*
SFMLSystemFactory::createLoader( EntityManager &em, const std::string &name, const std::string &res, const std::string &ent){
  SFMLLoader *loader = new SFMLLoader( name, em, res);
  assert(loader );
  loader->setEntitiesDesc( ent);
  return loader; 
}

Render* 
SFMLSystemFactory::createRender( EntityManager &em, const std::string &name, const unsigned int w, const unsigned int h){
  return new SFMLRender( name, em, w, h);
}

Inputs*
SFMLSystemFactory::createInputs( EntityManager &em, const std::string &name){
  return new SFMLInputs( name, em);
}
