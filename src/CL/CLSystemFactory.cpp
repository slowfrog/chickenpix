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

