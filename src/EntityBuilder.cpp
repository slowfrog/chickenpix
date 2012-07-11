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
#include "Controller.h"
#include "Resources.h"
#include "Scriptable.h"
#include "Camera.h"
#include "Stats.h"
#include "Collider.h"
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
  clbController,
  clbAudio,
  clbCollider,
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

void clbAudio( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildAudio( node, e, pResource);
}

void clbController( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildController( node, e, pResource);
}

void clbCollider( CEntityBuilder* eb, TiXmlElement* node, Entity* e, Resources *pResource){
  eb->buildCollider( node, e, pResource);
}


/****************************************************************/
/* class : CEntityBuilder                                       */
/****************************************************************/
/*
*/
CEntityBuilder::CEntityBuilder( const std::string& pathfile): mPathFileName(pathfile), mhDoc(0), mhRoot(0){
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
    for (pElem = pElem->FirstChildElement( "resource"); pElem; pElem = pElem->NextSiblingElement() ){
      std::string kind = pElem->Attribute( "kind");
      if ( !kind.empty()) {
        buildResourcesByKind(kind, pElem, pLoader, pResource);
      }
    }
  }
  else{
    LOG2ERR<<"Bad xml description for [Resources] component\n";
    throw "Bad xml description for [Resources] component";
  }
}

void
CEntityBuilder::buildResourcesByKind( const std::string &kind, TiXmlElement *pElem, Loader *pLoader, Resources *pResource){
 /* if ( "image" == kind){
    buildResourcesImage(pElem, pLoader, pResource);
  } else if ( "font" == kind) {
    buildResourcesFont(pElem, pLoader, pResource);
  } else if ( "sprite" == kind) {
    buildResourcesSprite(pElem, pLoader, pResource);
  } else if ( "audio" == kind) {
    buildResourcesAudio(pElem, pLoader, pResource);
  }*/
}

/*
 * Build resources with Loader
 */
/*
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

void 
CEntityBuilder::buildResourcesAudio( TiXmlElement *pNode, Loader *pLoader, Resources *pResource){
  TiXmlElement *pChar = pNode->FirstChildElement( "audio");
  if ( pChar ){
    std::string path  = pChar->Attribute( "path");
    std::string alias = pChar->Attribute( "alias");
    if ( !path.empty() && !alias.empty() ){
      pLoader->addAudio(path, pResource, alias);
      return;
    }
  }
  LOG2ERR<<"Bad xml description for [Audio] Resources\n";
  throw "Bad xml description for [Audio] Resources";
}
*/
/*
 * Parse all entities and build them
*/
void 
CEntityBuilder::parseEntity( EntityManager &em, Resources *pResource){
  // Loop on <entity>
  for (TiXmlElement *pElem=mhRoot.FirstChild( "entity").Element();
       pElem; pElem = pElem->NextSiblingElement() ){
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
    // Add tags
    for(pChilds=pChilds->FirstChildElement( "tag" ); pChilds; pChilds = pChilds->NextSiblingElement() ){
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
    for( pChilds=pChilds->FirstChildElement( "component" ); pChilds; pChilds = pChilds->NextSiblingElement() ){
      std::string type; 
      if ( TIXML_SUCCESS == pChilds->QueryValueAttribute( "type", &type)){
        //LOG2 <<name<<"\n";
        buildComponents(pChilds, type, ent, pResources);
      }
      else {
        LOG2ERR<<"Attribute [type] not found\n";
      }
    }
  }
}

/**
 * Dispatch to specific component builder
 */
void 
CEntityBuilder::buildComponents( TiXmlElement *pParent, const std::string& type, Entity *e, Resources *pResources ){
  int i =1;
  while ( ComponentName[i]) {
    if ( ComponentName[i] == type){
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
      e->addComponent(new Transform((float) x, (float) y));
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

// Component Audio: generally managed by Resource
void 
CEntityBuilder::buildAudio(TiXmlElement *pNode, Entity *e, Resources*){
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

// Component Controller
void 
CEntityBuilder::buildController(TiXmlElement *pNode, Entity *e, Resources*){
  std::string name; 
  if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "name", &name)){
    e->addComponent( new Controller(name));
  } else {
    LOG2ERR << "Missing 'name' attribute for [Controller] component\n";
  }
}

// Component Resources
void 
CEntityBuilder::buildResources(TiXmlElement *pNode, Entity *e, Resources *pResource){
  // Different kind of resource
  if ( pNode ){
    std::string kind;
    if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "kind", &kind)){
      buildComponentResourcesByKind( kind, pNode,  e, pResource);
      return;
    }
  }
  LOG2ERR<<"Bad kind for  [Resources] component\n";
  throw "Bad kind for  [Resources] component";
}

void 
CEntityBuilder::buildComponentResourcesByKind( const std::string &kind, TiXmlElement *pNode,  Entity *e, Resources *pResource){
  if ( "image" == kind) {
    buildComponentResourcesImage( pNode,  e, pResource);
    return;
  } else if ( "font" == kind){
    buildComponentResourcesText( pNode, e, pResource);
    return;
  } else if ( "audio" == kind){
    buildComponentResourcesAudio( pNode, e, pResource);
    return;
  }
}

void 
CEntityBuilder::buildComponentResourcesImage( TiXmlElement *pNode,  Entity *e, Resources *pResource ){
  TiXmlElement *pChar = pNode->FirstChildElement("image");
  if ( pChar) {
    std::string alias;
    if ( TIXML_SUCCESS == pChar->QueryValueAttribute( "alias", &alias)){
      BVisual *image = pResource->makeImage( alias);
      std::string gui;
      if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "gui", &gui)) {
        if (gui == "true") {
          image->setGUI(true);
        } else {
          image->setGUI(false);
        }
      }
      std::string center;
      if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "center", &center)) {
        if (center == "false") {
          image->setCenter(0, 0);
        }
      }
      int zOrder;
      if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "z-order", &zOrder)) {
        image->setZOrder(zOrder);
      }
      e->addComponent( image);
      return;
    }
  }
  LOG2ERR<<"Bad kind for  [Resources/Image] component\n";
  throw "Bad kind for  [Resources/Image] component";
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
    BVisual *textVis = NULL;
    // Color is defined
    if ( pFontAttr) {
      textVis = pResource->makeText( text, police, CPColor(r, g, b, a));
    }
    else {
      textVis = pResource->makeText( text, police);
    }
    
    int zOrder;
    if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "z-order", &zOrder)) {
      textVis->setZOrder(zOrder);
    }

    e->addComponent(textVis);
  }
}

void 
CEntityBuilder::buildComponentResourcesAudio( TiXmlElement *pNode,  Entity *e, Resources *pResource ){
  TiXmlElement *pChar = pNode->FirstChildElement("audio");
  if ( pChar) {
    std::string alias;
    if ( TIXML_SUCCESS == pChar->QueryValueAttribute( "alias", &alias)){
      bool looping = false;
      std::string loop;
      if ( TIXML_SUCCESS == pChar->QueryValueAttribute( "loop", &loop)) {
        if (loop == "true") {
          looping = true;
        }
      }
      Audio *audio = pResource->makeAudio( alias, looping);
      e->addComponent( audio);
      return;
    }
  }
  LOG2ERR<<"Bad kind for  [Resources/Audio] component\n";
  throw "Bad kind for  [Resources/Audio] component";
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
  float offsetX(0.f), offsetY(0.f);
  unsigned int width(0), height(0);
  if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "offsetX", &offsetX) && 
       TIXML_SUCCESS == pNode->QueryValueAttribute( "offsetY", &offsetY) &&
       TIXML_SUCCESS == pNode->QueryValueAttribute( "width", &width) &&
       TIXML_SUCCESS == pNode->QueryValueAttribute( "height", &height) ) {
    e->addComponent( new Camera(offsetX, offsetY, width, height));
  } else {
    e->addComponent( new Camera);
  }
}

// Component Character
void 
CEntityBuilder::buildCharacter ( TiXmlElement *pNode, Entity *e, Resources*){
  TiXmlElement *pChar = pNode->FirstChildElement("stats");
  if ( pChar ){
    Character *character = new Character;
    for(; pChar; pChar= pChar->NextSiblingElement()){
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

// Component Collider
void 
CEntityBuilder::buildCollider ( TiXmlElement *pNode, Entity *e, Resources*){
  std::string solidStr;
  bool solid = true;
  float size, left, top, right, bottom;
  if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "solid", &solidStr)) {
    solid = (solidStr == "true");
  }
  if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "size", &size) ) {
    Collider *collider = new Collider(solid, size);
    e->addComponent(collider);
    
  } else if ( TIXML_SUCCESS == pNode->QueryValueAttribute( "left", &left) && 
              TIXML_SUCCESS == pNode->QueryValueAttribute( "top", &top) &&
              TIXML_SUCCESS == pNode->QueryValueAttribute( "right", &right) &&
              TIXML_SUCCESS == pNode->QueryValueAttribute( "bottom", &bottom) ) {
    Collider *collider = new Collider(solid, left, top, right, bottom);
    e->addComponent(collider);
    
  } else {
    LOG2ERR << "Bad xml description for [Collider] component, missing size "
      "or box bounds (left, top, right bottom) \n";
    throw "Bad xml description for [Collider] component, missing size size "
      "or box bounds (left, top, right bottom) \n";
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
