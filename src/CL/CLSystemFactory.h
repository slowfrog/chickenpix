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
  virtual
  Loader *createLoader( const std::string &sysName, const std::string &resName,
                        const std::string &entName, const std::string &lvlName);
  virtual
  Render *createRender( const std::string &name, const unsigned int w,
                        const unsigned int h);
  virtual
  Inputs *createInputs( const std::string &name);
};

