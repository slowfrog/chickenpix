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

// List ofsystem Tags
#define RENDER    "Render"
#define LOADER    "Loader"
#define INPUTS    "Inputs"
#define SCRIPTING "Scripting"
#define MOVEMENT  "Movement"
#define ANIMATION "Animation"
#define SOUNDS    "Sounds"
#define FIGHT     "Fight"

// List of system available
// Add here new system
typedef enum {
  LOADER_TYPE     =0,
  RENDER_TYPE,
  INPUTS_TYPE,
  SCRIPTING_TYPE,
  MOVEMENT_TYPE,
  ANIMATION_TYPE,
  SOUNDS_TYPE,
  FIGHT_TYPE,
  // - Do not add anything after this line!! (just before)
  END_OF_LIST,
  MAX_SYSTEM = END_OF_LIST
} SystemType;

// Some ways to parse systems
extern SystemType in_ex_itPath[];
extern SystemType updatePath[];
