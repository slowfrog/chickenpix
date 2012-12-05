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
 
#pragma once

#include "System.h"
#include "Loader.h"
#include "Render.h"
#include "Inputs.h"
#include "Scripting.h"
#include "Movement.h"
#include "Animation.h"
#include "Sounds.h"
#include "FightSystem.h"

/*
 System Factory interface
 */
class CSystemFactory
{
public:
  // Constructor / destructor
  CSystemFactory(){}
  virtual ~CSystemFactory(){}
  
  // Specific
  virtual Loader *createLoader( const std::string&, const std::string&,
                                const std::string&, const std::string&) =0;
  virtual Render *createRender( const std::string&, const unsigned int, const unsigned int) =0;
  virtual Inputs *createInputs( const std::string&) =0;
  
  // Common
  Scripting     *createScripting  ( const std::string&);
  Movement      *createMovement   ( const std::string&);
  Animation     *createAnimation  ( const std::string&);
  Sounds        *createSounds     ( const std::string&);
  CFightSystem  *createFightSystem( const std::string&);
};


