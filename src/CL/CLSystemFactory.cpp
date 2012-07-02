#include <cassert>
#include "CLLoader.h"
#include "CLRender.h"
#include "CLInputs.h"
#include "CLSystemFactory.h"


// Constructor destructor
CLSystemFactory::CLSystemFactory():CSystemFactory(){
}

CLSystemFactory::CLSystemFactory(){
}

// Specific system
Loader*
CLSystemFactory::createLoader( EntityManager &em, const std::string &name, const std::string &res, const std::string &ent){
  CLLoader *loader = new CLLoader( name, em, res);
  assert(loader );
  loader->setEntitiesDesc( ent);
  return loader; 
}

Render* 
CLSystemFactory::createRender( EntityManager &em, const std::string &name, const unsigned int w, const unsigned int h){
  return new CLRender( name, em, w, h);
}

Inputs*
CLSystemFactory::createInputs( EntityManager &em, const std::string &name){
  return new CLInputs( name, em);
}

