#include "SystemRegistry.h"

// Useful way to call system methods in wanted order
// to discuss !!!!!
SystemType in_ex_itPath[]={
  RENDER_TYPE,
  SOUNDS_TYPE,
  ANIMATION_TYPE,
  LOADER_TYPE,
  INPUTS_TYPE,
  SCRIPTING_TYPE,
  MOVEMENT_TYPE,
  FIGHT_TYPE,
  END_OF_LIST
};

SystemType updatePath[]={
  INPUTS_TYPE,
  MOVEMENT_TYPE,
  SCRIPTING_TYPE,
  ANIMATION_TYPE,
  SOUNDS_TYPE,
  RENDER_TYPE,
  FIGHT_TYPE,
  END_OF_LIST
};
