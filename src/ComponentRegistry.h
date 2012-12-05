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

enum ComponentType {
  TRANSFORM_TYPE  =  1,
  MOBILE_TYPE     =  2,
  VISUAL_TYPE     =  3,
  ANIMATED_TYPE   =  4,
  INPUT_TYPE      =  5,
  RESOURCES_TYPE  =  6,
  SCRIPTABLE_TYPE =  7,
  CAMERA_TYPE     =  8,
  CHARACTER_TYPE  =  9,
  CONTROLLER_TYPE = 10,
  AUDIO_TYPE      = 11,
  COLLIDER_TYPE   = 12,
  ACTIONABLE_TYPE = 13,
  MAPINFO_TYPE    = 14,
  GUI_TYPE        = 15,
  // !!! Don't forget to update ComponentName values when adding a new type !!!
};

extern const char *ComponentName[];
