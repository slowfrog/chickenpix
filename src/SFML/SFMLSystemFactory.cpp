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
SFMLSystemFactory::createLoader( 
                                const std::string &sysName,
                                const std::string &resName,
                                const std::string &entName,
                                const std::string &lvlName)
{
  SFMLLoader *loader = new SFMLLoader( sysName);
  assert(loader );
  // Set members 
  loader->setResources( resName);
  loader->setEntities ( entName);
  loader->setLevel    ( lvlName);
  // Check and init Xml
  loader->prepareXml();
  // loader well done
  return loader;
}

Render* 
SFMLSystemFactory::createRender( const std::string &name, const unsigned int w, const unsigned int h){
  return new SFMLRender( name, w, h);
}

Inputs*
SFMLSystemFactory::createInputs( const std::string &name){
  return new SFMLInputs( name);
}
