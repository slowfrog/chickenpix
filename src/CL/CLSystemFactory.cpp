#include <cassert>
#include "CLLoader.h"
#include "CLRender.h"
#include "CLInputs.h"
#include "CLSystemFactory.h"


// Constructor destructor
CLSystemFactory::CLSystemFactory():CSystemFactory(){
}

CLSystemFactory::~CLSystemFactory(){
}

// Specific system
Loader*
CLSystemFactory::createLoader(const std::string &sysName,
                              const std::string &resName,
                              const std::string &entName,
                              const std::string &lvlName){
  CLLoader *loader = new CLLoader(sysName);
  assert(loader );
  loader->setResources( resName);
  loader->setEntities( entName);
  loader->setLevel( lvlName);
  
  // Check and init Xml ???
  loader->prepareXml();

  loader->initResources();
  return loader; 
}

Render* 
CLSystemFactory::createRender( const std::string &name,
                               const unsigned int w, const unsigned int h){
  return new CLRender( name, w, h);
}

Inputs*
CLSystemFactory::createInputs( const std::string &name){
  return new CLInputs( name);
}

