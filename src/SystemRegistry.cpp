#include "SystemRegistry.h"

// Useful way to call system methods in wanted order
// to discuss !!!!!
SystemType in_ex_itPath[]={
  RENDER_TYPE,
  ANIMATION_TYPE,
  LOADER_TYPE,
  INPUTS_TYPE,
  SCRIPTING_TYPE,
  MOVEMENT_TYPE,
  END_OF_LIST
};

SystemType updatePath[]={
  INPUTS_TYPE,
  SCRIPTING_TYPE,
  MOVEMENT_TYPE,
  ANIMATION_TYPE,
  RENDER_TYPE,
  END_OF_LIST
};