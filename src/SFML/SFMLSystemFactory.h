#pragma once

#include "../SystemFactory.h"

/*
*/
class SFMLSystemFactory : public CSystemFactory
{
public:
  // Constructor destructor
  SFMLSystemFactory();
  virtual ~SFMLSystemFactory();
  
  // Specific system
  virtual Loader *createLoader( EntityManager&, const std::string&, const std::string&, const std::string&);
  virtual Render *createRender( EntityManager&, const std::string&, const unsigned int, const unsigned int);
  virtual Inputs *createInputs( EntityManager&, const std::string&);
};

