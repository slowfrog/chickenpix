// Headers
#include "log.h"
#include "ComponentRegistry.h"
#include "TagEntityManager.h"
#include "Loader.h"
// Components
#include "Transform.h"
#include "Mobile.h"
#include "Animated.h"
#include "Input.h"
#include "Resources.h"
#include "Scriptable.h"
#include "Camera.h"
#include "Stats.h"
// owner
#include "EntityBuilder.h"

// *** Order is important => the same than ComponentRegistry.cpp
// function is mapped to component
static callbacks callers[]={
  0,  // index 0 is unused
  clbTransform,
  clbMobile,
  clbVisual,
  clbAnimated,
  clbInput,
  clbResources,
  clbScriptable,
  clbCamera,
  clbCharacter,
  0 // last index marker
};

/****************************************************************/
/* Callbacks                                                    */
/****************************************************************/
void clbTransform( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildTransform( node, e, pResource);
}

void clbMobile( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildMobile( node, e, pResource);
}

void clbVisual( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildVisual( node, e, pResource);
}

void clbAnimated( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildAnimated( node, e, pResource);
}

void clbInput( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildInput( node, e, pResource);
}

void clbResources( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildResources( node, e, pResource);
}

void clbScriptable( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildScriptable( node, e, pResource);
}

void clbCamera( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildCamera( node, e, pResource);
}

void clbCharacter( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildCharacter( node, e, pResource);
}

/****************************************************************/
/* class : CEntityBuilder                                       */
/****************************************************************/
/*
*/
CEntityBuilder::CEntityBuilder( const std::string& pathfile): mPathFileName(pathfile), mhRoot(0), mhDoc(0){
  // Check file
  if ( mPathFileName.empty() ){
    LOG2ERR<<"Bad file\n";
    throw "Bad file";
  }
  // Initialize parser
  init();
}

/**
 * Init builders
 */
void
CEntityBuilder::init(){
  // Load xml
  mDoc = mPathFileName;
	if (!mDoc.LoadFile()) {
    LOG2ERR<<"Could not load file "<< mPathFileName<<"\n";
    throw "File error";
  };
  
  // Initialize
  mhDoc = &mDoc;
	TiXmlElement * pRoot = mhDoc.FirstChildElement().Element();
  if ( !pRoot){
    LOG2ERR << "Reading file...error\n";
    throw "File error";
  }
  
  // Set start node as root
  mhRoot=TiXmlHandle( pRoot);
}

/*
 * Parse all resources and build them
 */
void
CEntityBuilder::parseResources( Loader *pLoader, Resources *pResource){
  // Loop on <resources>
  TiXmlElement *pElem = mhRoot.FirstChildElement().Element();
  if ( pElem){
    pElem = pElem->FirstChildElement( "resource");
    for (pElem; pElem; pElem = pElem->NextSiblingElement() ){
      std::string type = pElem->Attribute( "type");
      if ( !type.empty()) {
        buildResourcesByType(type, pElem, pLoader, pResource);
      }
    }
  }
  else{
    LOG2ERR<<"Bad xml description for [Resources] component\n";
    throw "Bad xml description for [Resources] component";
  }
}

void
CEntityBuilder::buildResourcesByType( const std::string &type, TiXmlElement *pElem, Loader *pLoader, Resources *pResource){
  if ( "image" == type){
    buildResourcesImage(pElem, pLoader, pResource);
  }
  
  if ( "font" == type) {
    buildResourcesFont(pElem, pLoader, pResource);
  }
  
  if ( "sprite" == type) {
    buildResourcesSprite(pElem, pLoader, pResource);
  }
}

/*
 * Build resources with Loader
 */
void 
CEntityBuilder::buildResourcesImage( TiXmlElement *pNode, Loader *pLoader, Resources *pResource){
  TiXmlElement *pChar = pNode->FirstChildElement( "image");
  if ( pChar ){
    std::string path  = pChar->Attribute( "path");
    std::string alias = pChar->Attribute( "alias");
    if ( !path.empty() && !alias.empty() ){
      pLoader->addImage(path, pResource, alias);
      return;
    }
  }
  LOG2ERR<<"Bad xml description for [Image] Resources\n";
  throw "Bad xml description for [Image] Resources";
}

void 
CEntityBuilder::buildResourcesFont( TiXmlElement *pNode, Loader *pLoader, Resources *pResource){
  TiXmlElement *pChar = pNode->FirstChildElement( "image");
  if ( pChar ){
    std::string path  = pChar->Attribute( "path");
    std::string alias = pChar->Attribute( "alias"); 
    int         size  (8);
    pChar->QueryIntAttribute( "size", &size);
    if ( !path.empty() && !alias.empty() ){
      pLoader->addFont(path, size, pResource, alias);
      return;
    }
  }
  LOG2ERR<<"Bad xml description for [Font] Resources\n";
  throw "Bad xml description for [Font] Resources";
}

void 
CEntityBuilder::buildResourcesSprite( TiXmlElement *pNode, Loader *pLoader, Resources *pResource){
  TiXmlElement *pChar = pNode->FirstChildElement( "image");
  if ( pChar ){
    std::string path  = pChar->Attribute( "path");
    std::string alias = pChar->Attribute( "alias");
    if ( !path.empty() && !alias.empty() ){
      pLoader->addSprite(path, pResource, alias);
      return;
    }
  }
  LOG2ERR<<"Bad xml description for [Sprite] Resources\n";
  throw "Bad xml description for [Sprite] Resources";
}

/*
 * Parse all entities and build them
*/
void 
CEntityBuilder::parseEntity( EntityManager &em, Resources *pResource){
  // Loop on <entity>
  TiXmlElement *pElem=mhRoot.FirstChild( "entity").Element();
  for (pElem; pElem; pElem = pElem->NextSiblingElement() ){
    BuildEntity( pElem, em, pResource);
  }
}

void 
CEntityBuilder::BuildEntity( TiXmlElement *pParent, EntityManager &em, Resources *pResources){
  // Create entity (new id)
  Entity *ent = em.createEntity();
  if ( !ent){
    LOG2ERR<<"Could not create entity\n";
    throw "Could not create entity";
  }
  TiXmlElement* pChilds = pParent->FirstChildElement( "tags");
  if ( pChilds ){
    pChilds=pChilds->FirstChildElement( "tag" );
    // Add tags
    for( pChilds; pChilds; pChilds = pChilds->NextSiblingElement() ){
      std::string name;
      if ( TIXML_SUCCESS == pChilds->QueryValueAttribute( "name", &name))
      {
        std::string unique;
        bool        isUnique(false);
        if ( TIXML_SUCCESS == pChilds->QueryValueAttribute( "unique", &unique) ){
          isUnique = ( unique=="true");
        }
        em.tagEntity( ent, name, isUnique);
      }
    }
  }
  
  // Add components
  pChilds = pParent->FirstChildElement( "components");
  if ( pChilds ){
    pChilds=pChilds->FirstChildElement( "component" );
    for( pChilds; pChilds; pChilds = pChilds->NextSiblingElement() ){
      std::string name; 
      if ( TIXML_SUCCESS == pChilds->QueryValueAttribute( "name", &name)){
        LOG2 <<name<<"\n";
        buildComponents(pChilds, name, ent, pResources);
      }
      else {
        LOG2ERR<<"Attribute [name] not found\n";
      }
    }
  }
}

/**
 * Dispatch to specific component builder
 */
void 
CEntityBuilder::buildComponents( TiXmlElement *pParent, const std::string& name, Entity *e, Resources *pResources ){
  int i =1;
  while ( ComponentName[i]) {
    if ( ComponentName[i] == name){
      if ( callers[i]) {
        callers[i]( this, pParent, e, pResources);
        break;
      }
    }
    i++;
  }
}

// Component transform
void 
CEntityBuilder::buildTransform (TiXmlElement *pNode, Entity* e, Resources *pResource){
  TiXmlElement *pChar = pNode->FirstChildElement("position");
  if ( pChar) {
    int x(0), y(0);
    if ( TIXML_SUCCESS == pChar->QueryValueAttribute( "x", &x) && 
        TIXML_SUCCESS == pChar->QueryValueAttribute( "y", &y) ) {
      e->addComponent(new Transform(x, y));
      return;
    }
  }
  LOG2ERR<<"Bad xml description for [Tranform] component\n";
  throw "Bad xml description for [Tranform] component";
}


// Component Mobile
void 
CEntityBuilder::buildMobile(TiXmlElement *pNode, Entity *e, Resources*){
  // Build Mobile with arguments
  TiXmlElement *pChar = pNode->FirstChildElement("position");
  if ( pChar ){
    float x(0.f), y(0.f);
    if ( TIXML_SUCCESS == pChar->QueryValueAttribute( "x", &x) && 
         TIXML_SUCCESS == pChar->QueryValueAttribute( "y", &y) ) {
      e->addComponent( new Mobile(x, y));
      return;
    }
  }
  // Else, build Mobile without argument
  e->addComponent( new Mobile);
}

// Component BVisual
void 
CEntityBuilder::buildVisual(TiXmlElement *pNode, Entity *e, Resources*){
  // ???
}

// Component Animated
void 
CEntityBuilder::buildAnimated(TiXmlElement *pNode, Entity *e, Resources*){
  TiXmlElement *pChar = pNode->FirstChildElement("image");
  if ( pChar ){
    std::string name; 
    if ( TIXML_SUCCESS == pChar->QueryValueAttribute( "name", &name)){
      e->addComponent( new Animated( name));
      return;
    }
  }
  LOG2ERR<<"Bad xml description for [Animated] component\n";
  throw "Bad xml description for [Animated] component";
}

// Component Input
void 
CEntityBuilder::buildInput(TiXmlElement *pNode, Entity *e, Resources*){
  // No elements, no attributes
  e->addComponent( new Input);
}

// Component Resources
void 
CEntityBuilder::buildResources(TiXmlElement *pNode, Entity *e, Resources *pResource){
  // Different kind of resource
  if ( pNode ){
    std::string type;
    if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "type", &type)){
      buildComponentResourcesByType( type, pNode,  e, pResource);
      return;
    }
  }
  LOG2ERR<<"Bad type for  [Resources] component\n";
  throw "Bad type for  [Resources] component";
}

void 
CEntityBuilder::buildComponentResourcesByType( const std::string &type, TiXmlElement *pNode,  Entity *e, Resources *pResource){
  if ( "image" == type) {
    buildComponentResourcesImage( pNode,  e, pResource);
    return;
  }
  
  if ( "font" == type){
    buildComponentResourcesText( pNode, e, pResource);
    return;
  }
}

void 
CEntityBuilder::buildComponentResourcesImage( TiXmlElement *pNode,  Entity *e, Resources *pResource ){
  TiXmlElement *pChar = pNode->FirstChildElement("image");
  if ( pChar) {
    std::string alias;
    if ( TIXML_SUCCESS == pChar->QueryValueAttribute( "alias", &alias)){
      e->addComponent( pResource->makeImage( alias));
      return;
    }
  }
  LOG2ERR<<"Bad type for  [Resources/Image] component\n";
  throw "Bad type for  [Resources/Image] component";
}

void 
CEntityBuilder::buildComponentResourcesText( TiXmlElement *pNode,  Entity *e, Resources *pResource){
  std::string   text, police;
  int           r(0), g(0), b(0), a(0);
  TiXmlElement  *pFontAttr = pNode->FirstChildElement( "text");
  if ( pFontAttr){
    // Warning : only text is accepted here! no formatted text like <b>hello</b>
    text = pFontAttr->GetText();
  }
  
  pFontAttr = pNode->FirstChildElement( "police");
  if( pFontAttr){
    pFontAttr->QueryValueAttribute( "name", &police);
  }
  
  pFontAttr = pNode->FirstChildElement( "color");
  if ( pFontAttr){
    pFontAttr->QueryValueAttribute( "r", &r);
    pFontAttr->QueryValueAttribute( "g", &g);
    pFontAttr->QueryValueAttribute( "b", &b);
    pFontAttr->QueryValueAttribute( "a", &a);
  }
  
  
  if ( !text.empty() && !police.empty()){
    // Color is defined
    if ( pFontAttr) {
      e->addComponent(pResource->makeText( text, police, CPColor(r, g, b, a)));
    }
    else {
      e->addComponent(pResource->makeText( text, police));
    }
  }
}

// Component Scriptable
void 
CEntityBuilder::buildScriptable( TiXmlElement *pNode, Entity *e, Resources*){
  TiXmlElement *pChar = pNode->FirstChildElement("script");
  std::string script;
  if ( TIXML_SUCCESS == pChar->QueryValueAttribute( "name", &script)){
    e->addComponent( new Scriptable( script));
    return;
  }
  LOG2ERR<<"Bad xml description for [Scriptable] component\n";
  throw "Bad xml description for [Scriptable] component";
}

// Component Camera
void 
CEntityBuilder::buildCamera( TiXmlElement *pNode, Entity *e, Resources*){
  // No elements, no attributes
  e->addComponent( new Camera);
}

// Component Character
void 
CEntityBuilder::buildCharacter ( TiXmlElement *pNode, Entity *e, Resources*){
  TiXmlElement *pChar = pNode->FirstChildElement("stats");
  if ( pChar ){
    Character *character = new Character;
    for( pChar; pChar; pChar= pChar->NextSiblingElement()){
      std::string name;
      long        value(0);
      if ( TIXML_SUCCESS == pChar->QueryValueAttribute( "name", &name) &&
           TIXML_SUCCESS == pChar->QueryValueAttribute( "value", &value)){
        buildStats( character, name, CVariant( value));
      }
    }
    e->addComponent( character);
  }
}

void 
CEntityBuilder::buildStats( Character *c, const std::string &name, const CVariant &v)
{
  // Ok, not very generic !! must be enhanced later
  if ( name == "initiative"){
    c->addStats( INITIATIVE, v);
    return;
  }
  
  if ( name == "health"){
    c->addStats( HEALTH, v);
    return;
  }
  
  if ( name == "ca"){
    c->addStats( ARMOR_CLASS, v);
    return;
  }
  
  if ( name == "damage"){
    c->addStats( DAMAGE, v);
    return;
  }

}
