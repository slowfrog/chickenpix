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

// Fight System
CFightSystem*
CSystemFactory::createFightSystem( const std::string &name){
  return new CFightSystem( name);
}



