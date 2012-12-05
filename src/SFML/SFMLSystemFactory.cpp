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
