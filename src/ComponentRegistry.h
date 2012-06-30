#pragma once

enum ComponentType {
  TRANSFORM_TYPE  = 1,
  MOBILE_TYPE     = 2,
  VISUAL_TYPE     = 3,
  ANIMATED_TYPE   = 4,
  INPUT_TYPE      = 5,
  RESOURCE_TYPE   = 6,
  RESOURCES_TYPE  = 7,
  SCRIPTABLE_TYPE = 8,
  CAMERA_TYPE     = 9
  // !!! Don't forget to update ComponentName values when adding a component type !!!
};

extern const char *ComponentName[];
