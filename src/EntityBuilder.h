#pragma once

#include "tinyxml.h"
#include "Resources.h"
#include "EntityManager.h"

// Constants

// Forward
class CEntityBuilder;
class Loader;
class Character;
class CVariant;

// Types
typedef void (*callbacks)( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);

// Callbacks def
extern void clbTransform( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbMobile   ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbVisual   ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbAnimated ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbInput    ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbResources( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbScriptable( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbCamera   ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbCharacter( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);

/*
*/
class CEntityBuilder
{
public:
  // Constructor/destructor
  CEntityBuilder( const std::string&);
  ~CEntityBuilder(){}
  
  // API
  void parseResources ( Loader*, Resources*);
  void parseEntity    ( EntityManager&, Resources*);
  
  // link to Callbacks
  void buildTransform ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildMobile    ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildVisual    ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildAnimated  ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildInput     ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildResources ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildScriptable( TiXmlElement*, Entity*, Resources* = NULL);
  void buildCamera    ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildCharacter ( TiXmlElement*, Entity*, Resources* = NULL);
  
protected:
  void init();
  
  void buildResourcesByType( const std::string&, TiXmlElement*, Loader*, Resources*);
  
  void BuildEntity    ( TiXmlElement*, EntityManager&, Resources* );
  
  void buildComponents( TiXmlElement*, const std::string&, Entity*, Resources* );
  void buildTags      ( TiXmlElement*, Entity*);
  
  void buildResourcesImage ( TiXmlElement*, Loader*, Resources*);
  void buildResourcesFont  ( TiXmlElement*, Loader*, Resources*);
  void buildResourcesSprite( TiXmlElement*, Loader*, Resources*);
  
  void buildComponentResourcesByType( const std::string&, TiXmlElement*,  Entity*, Resources*);
  void buildComponentResourcesImage ( TiXmlElement*,  Entity*, Resources* );
  void buildComponentResourcesText  ( TiXmlElement*,  Entity*, Resources*);
  
  void buildStats( Character*, const std::string&, const CVariant&);
  
private:
  // not allowed
  CEntityBuilder operator=(const CEntityBuilder&){}
  
private:
  //EntityManager &mEM;
  std::string   mPathFileName;
  TiXmlDocument mDoc;
  TiXmlHandle   mhDoc;
  TiXmlHandle   mhRoot;
};