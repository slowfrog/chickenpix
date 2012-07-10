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
  virtual Loader *createLoader( const std::string&, const std::string&,
                                const std::string&, const std::string&);
  virtual Render *createRender( const std::string&, const unsigned int, const unsigned int);
  virtual Inputs *createInputs( const std::string&);
};

