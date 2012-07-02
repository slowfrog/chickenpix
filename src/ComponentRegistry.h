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
  CONTROLLER_TYPE = 10
  // !!! Don't forget to update ComponentName values when adding a component type !!!
};

extern const char *ComponentName[];
