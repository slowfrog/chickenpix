#pragma once

#include "../SystemFactory.h"

/*
 */
class CLSystemFactory : public CSystemFactory
{
public:
  // Constructor destructor
  CLSystemFactory();
  virtual ~CLSystemFactory();
  
  // Specific system
  virtual Loader *createLoader( EntityManager&, const std::string&, const std::string&, const std::string&);
  virtual Render *createRender( EntityManager&, const std::string&, const unsigned int, const unsigned int);
  virtual Inputs *createInputs( EntityManager&, const std::string&);
};

