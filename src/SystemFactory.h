#pragma once

#include "System.h"
#include "Loader.h"
#include "Render.h"
#include "Inputs.h"
#include "Scripting.h"
#include "Movement.h"
#include "Animation.h"

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
  virtual Loader *createLoader( EntityManager&, const std::string&, const std::string&, const std::string&) =0;
  virtual Render *createRender( EntityManager&, const std::string&, const unsigned int, const unsigned int) =0;
  virtual Inputs *createInputs( EntityManager&, const std::string&) =0;
  
  // Common
  Scripting *createScripting( EntityManager&, const std::string&);
  Movement  *createMovement ( EntityManager&, const std::string&);
  Animation *createAnimation( EntityManager&, const std::string&);
};
