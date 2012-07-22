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
  MAPINFO_TYPE    = 14
  // !!! Don't forget to update ComponentName values when adding a new type !!!
};

extern const char *ComponentName[];
