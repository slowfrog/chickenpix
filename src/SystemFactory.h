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


