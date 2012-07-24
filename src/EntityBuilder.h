#pragma once

#include "tinyxml/tinyxml.h"
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
extern void clbTransform      ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbMobile         ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbVisual         ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbAnimated       ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbInput          ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbController     ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbResources      ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbScriptable     ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbCamera         ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbCharacter      ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbController     ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbAudio          ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbCollider       ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);
extern void clbActionable     ( CEntityBuilder*, TiXmlElement*, Entity*, Resources*);

/*
*/
class CEntityBuilder
{
public:
  // Constructor/destructor
  CEntityBuilder( const std::string&);
  ~CEntityBuilder(){}
  
  // API
  void parseEntity    ( EntityManager&, Resources*);
  
  // link to Callbacks
  void buildTransform      ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildMobile         ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildVisual         ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildAnimated       ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildInput          ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildResources      ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildScriptable     ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildCamera         ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildCharacter      ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildController     ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildAudio          ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildCollider       ( TiXmlElement*, Entity*, Resources* = NULL);
  void buildActionable     ( TiXmlElement*, Entity*, Resources* = NULL);
  
protected:
  void init();
  
  void BuildEntity    ( TiXmlElement*, EntityManager&, Resources* );
  
  void buildComponents( TiXmlElement*, const std::string&, Entity*, Resources* );
  static void buildTags      ( TiXmlElement*, Entity*);
  
  static void buildComponentResourcesByKind( const std::string&, TiXmlElement*,
                                      Entity*, Resources*);
  static void addCommonAttributes(TiXmlElement *pNode, Resources *pResources,
                                  BVisual *visual);
  static void buildComponentResourcesImage ( TiXmlElement*,  Entity*, Resources* );
  static void buildComponentResourcesText  ( TiXmlElement*,  Entity*, Resources*);
  static void buildComponentResourcesAudio ( TiXmlElement*,  Entity*, Resources*);
  
  static void buildStats( Character*, const std::string&, const CVariant&);
  
private:
  // not allowed
  CEntityBuilder operator=(const CEntityBuilder&){return *this;}
  
private:
  //EntityManager &mEM;
  std::string   mPathFileName;
  TiXmlDocument mDoc;
  TiXmlHandle   mhDoc;
  TiXmlHandle   mhRoot;
};
