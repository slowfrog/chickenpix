#pragma once

// List ofsystem Tags
#define RENDER    "Render"
#define LOADER    "Loader"
#define INPUTS    "Inputs"
#define SCRIPTING "Scripting"
#define MOVEMENT  "Movement"
#define ANIMATION "Animation"
#define SOUNDS    "Sounds"

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
  // - Do not add anything after this line!! (just before)
  END_OF_LIST,
  MAX_SYSTEM = END_OF_LIST
} SystemType;

// Some ways to parse systems
extern SystemType in_ex_itPath[];
extern SystemType updatePath[];
