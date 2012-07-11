#include <cassert>
#include <iostream>
#include <sstream>
#include <map>
#include "TmxParser/Tmx.h"
#include "EntityBuilder.h"
#include "Utils.h"
#include "Loader.h"
#include "Transform.h"
#include "Animated.h"
#include "Camera.h"
#include "Input.h"
#include "Mobile.h"
#include "Resources.h"
#include "Scriptable.h"
#include "Collider.h"
#include "log.h"

static const int BASE_MAP_ZORDER = -10;

Loader::Loader( string const &name):
  System( name), resourceFile( ""), meFile( ""), mLevel( ""), doc(NULL) {
}

Loader::~Loader() {
}

// Setter(s)
void 
Loader::setResources( const std::string &aFile){
  resourceFile = aFile;
}

void 
Loader::setEntities ( const std::string &aFile){
  meFile = aFile;
}

void 
Loader::setLevel( const std::string &alevel){
  mLevel = alevel;
}

// System Interface(s)
void
Loader::init( EntityManager &em) {
  // Create resources
    initResources ( em);
  // Load entities and level
  loadEntities  ( em);
  loadLevel     ( em);
}

void
Loader::update( EntityManager&, int) {
}

void
Loader::exit( EntityManager&) {
}

// Build and init resources/entities
void 
Loader::initResources( EntityManager &em){
  if ( !resourceFile.empty()) {
    // get resources
    Resources *resources = em.getComponent<Resources>();
    assert( resources);
    // Add resources
    addImage  ( resources);
    addFont   ( resources);
    addSprites( resources);
    addAudio  ( resources);
  }
}

Entity *
Loader::createImage(EntityManager     &em,
                    ImagePart const   &part, 
                    float             x, 
                    float             y, 
                    int               zOrder,
                    Resources         *resources
                    ) const 
{
  // Create entity
  Entity *img = em.createEntity();
  // Set properties
  img->addComponent(new Transform(x, y));
  BVisual *image = resources->makeImage(part);
  image->setZOrder(zOrder);
  img->addComponent(image);
  return img;
}

void
Loader::loadLevel( EntityManager &em) {
  if ( !mLevel.empty() ) {
    // Load map
    loadTmxMap(em, string("resources/maps/") + mLevel + ".tmx");
  }
}

void 
Loader::loadEntities( EntityManager &em){

  if ( !meFile.empty()){
    // Get resources
    Resources *resources = em.getComponent<Resources>();
    assert( resources);
    // Use Builder to create resources
    CEntityBuilder eb( meFile);
    // Use builder to create entities
    eb.parseEntity   ( em, resources);
  }
  else {
    LOG2ERR<< "Cannot access xml file for entities description\n";
  }
}

void
Loader::loadTmxMap( EntityManager &em, string const &name) const {
  Resources *resources = em.getComponent<Resources>();
  
  // Tmx Parser
  Tmx::Map map;
  map.ParseFile(name);
  if (map.HasError()) {
    LOG2 << "Map has error: " << map.GetErrorText() << "\n";
  } else {
    LOG2 << "Map: " << map.GetWidth() << "x" << map.GetTileWidth() << "px - " <<
    map.GetHeight() << "x" << map.GetTileHeight() << "px\n";
    
    // Load tilesets
    std::map<int, ImagePart> tilesetImages;
    std::map<int, bool> tileCollider;
    for (int i = 0; i < map.GetNumTilesets(); ++i) {
      Tmx::Tileset const *tileset = map.GetTileset(i);
      string imageFile;
      if (tileset->GetSource().length() == 0) {
        imageFile = joinPaths(getDirectory(name), tileset->GetImage()->GetSource());
      } else {
        string tsxFile = joinPaths(getDirectory(name), tileset->GetSource());
        imageFile = joinPaths(getDirectory(tsxFile), tileset->GetImage()->GetSource());
      }
      addImage(imageFile, resources); // Make sure to load the tileset image
      //tilesetImages[i] = imageFile;
      LOG2DBG << "Tileset #" << i << " name='" << tileset->GetName() << "' " <<
        imageFile << " " << tileset->GetTileWidth() << "x" << tileset->GetTileHeight() << "\n";
      
      int j = 0;
      for (int y = tileset->GetMargin(); y < tileset->GetImage()->GetHeight();
           y += tileset->GetTileHeight() + tileset->GetSpacing()) {
        for (int x = tileset->GetMargin(); x < tileset->GetImage()->GetWidth();
             x += tileset->GetTileWidth() + tileset->GetSpacing()) {
          
          int gid = tileset->GetFirstGid() + j;
          tilesetImages[gid] = ImagePart(imageFile, x, y,
                                         tileset->GetTileWidth(),
                                         tileset->GetTileHeight());

          bool collide = false;
          const Tmx::Tile *tile = tileset->GetTile(j);
          if (tile != NULL) {
            const Tmx::PropertySet &tileProps = tile->GetProperties();
            collide = (tileProps.GetList()["wall"] != "");
          }
          tileCollider[gid] = collide;
          //cout << gid << " ";
          // cout << "Tile #" << (tileset->GetFirstGid() + j) << ": " <<
          //   x << "," << y << "-" << (x + tileset->GetTileWidth()) << "," <<
          //   (y + tileset->GetTileHeight()) << endl;
          ++j;
        }
      }
      //cout << endl;
    }
    
    // Load layers
    const int maxLayer = map.GetNumLayers();
    for (int i = 0; i < maxLayer; ++i) {
      Tmx::Layer const *layer = map.GetLayer(i);
      // cout << "Layer #" << i << ": " << layer->GetName() << " " <<
      //   (layer->IsVisible() ? "visible" : "hidden") << " " <<
      //   layer->GetWidth() << "x" << layer->GetHeight() << endl;
      if (layer->IsVisible()) {
        for (int y = 0; y < layer->GetHeight(); ++y) {
          // cout << "[ ";
          for (int x = 0; x < layer->GetWidth(); ++x) {
            const Tmx::MapTile &tile = layer->GetTile(x, y);
            if (tile.tilesetId < 0) {
              // cout << "? ";
              continue;
            }
            const Tmx::Tileset *tileset = map.GetTileset(tile.tilesetId);
            // cout << tile.tilesetId << "|" << tileset->GetFirstGid() + tile.id << " ";
            int gid = tileset->GetFirstGid() + tile.id;
            Entity *img = createImage(em, tilesetImages[gid],
                                      (float) x * map.GetTileWidth(),
                                      (float) y * map.GetTileHeight(),
                                      BASE_MAP_ZORDER + i, resources);
            if (tileCollider[gid]) {
              float w = map.GetTileWidth() / 2.0f;
              float h = map.GetTileHeight() / 2.0f;
              img->addComponent(new Collider(true, w, h, w, h));
            }
          }
          // cout << "]" << endl;
        }
      }
    }
  }
}

void 
Loader::prepareXml(){
  doc = new TiXmlDocument( resourceFile);
  assert( doc);
  doc->LoadFile();
  if (doc->Error()) {
    LOG2ERR << "Error parsing file: " << resourceFile << ", " << doc->ErrorDesc() << "\n";
  }
}


// Resources parsers
// -----------------------------------------

// !!! Code a factoriser peut etre !!!

// Image from XML
void 
Loader::addImage( Resources *resources){
  const TiXmlElement *pNode    = doc->FirstChildElement("resources");
  const TiXmlElement *pImgNode = findChild(pNode, "images");
  // loop on image
  for ( pImgNode = pImgNode->FirstChildElement("image");
        pImgNode;
        pImgNode = pImgNode->NextSiblingElement())
  {
    // Name
    std::string name;
    pImgNode->QueryValueAttribute( "name", &name);
    // File
    std::string file, anti_alias;
    const TiXmlElement *pImgFileNode = pImgNode->FirstChildElement("image");
    if ( pImgFileNode) {
      pImgFileNode->QueryValueAttribute( "file", &file);
    }
    
    if ( !name.empty() && !file.empty()){ 
      addImage(  "resources/" + file, resources, name); 
    }
    else {
      LOG2ERR<<"Mismatch attribute when creating image resources\n";
    }
  }
}

// Font from XML
void 
Loader::addFont( Resources *resources){
  const TiXmlElement *pNode    = doc->FirstChildElement("resources");
  const TiXmlElement *pImgNode = findChild(pNode, "fonts");
  // loop on font
  for ( pImgNode = pImgNode->FirstChildElement("font");
        pImgNode;
        pImgNode = pImgNode->NextSiblingElement())
  {
    // Name
    std::string name;
    pImgNode->QueryValueAttribute( "name", &name);
    // Style
    std::string file;
    int         height(0);
    const TiXmlElement *pImgFileNode = pImgNode->FirstChildElement("freetype");
    if ( pImgFileNode) {
      pImgFileNode->QueryValueAttribute( "file", &file);
      pImgFileNode->QueryValueAttribute( "height", &height);
    }
    
    if ( !name.empty() && !file.empty()){ 
      addFont( "resources/" + file, height, resources, name); 
    }
    else {
      LOG2ERR<<"Mismatch attribute when creating font resources\n";
    }
  }
}

// Sprite from XML
void 
Loader::addSprites( Resources *resources){
  const TiXmlElement *pNode    = doc->FirstChildElement("resources");
  const TiXmlElement *pImgNode = findChild(pNode, "sprites");
  // loop on font
  for ( pImgNode = pImgNode->FirstChildElement("sprite");
        pImgNode;
        pImgNode = pImgNode->NextSiblingElement())
  {
    // Name
    std::string name;
    pImgNode->QueryValueAttribute( "name", &name);
    if ( !name.empty()){ 
      addSprite( "sprites/" + name, resources, name); 
    }
    else {
      LOG2ERR<<"Mismatch attribute when creating font resources\n";
    }
  }
}

// Audio from XML
void 
Loader::addAudio( Resources *resources){
  const TiXmlElement *pNode    = doc->FirstChildElement("resources");
  const TiXmlElement *pImgNode = findChild(pNode, "samples");
  // loop on font
  for ( pImgNode = pImgNode->FirstChildElement("sample");
        pImgNode;
        pImgNode = pImgNode->NextSiblingElement())
  {
    // Name
    std::string name;
    pImgNode->QueryValueAttribute( "name", &name);
    // Style
    std::string file, anti_alias;
    const TiXmlElement *pImgFileNode = pImgNode->FirstChildElement("sample");
    if ( pImgFileNode) {
      pImgFileNode->QueryValueAttribute( "file", &file);
    }
    
    if ( !name.empty() && !file.empty()){ 
      addAudio( "resources/" + file, resources, name); 
    }
    else {
      LOG2ERR<<"Mismatch attribute when creating font resources\n";
    }
  }
  
}

const TiXmlElement *
Loader::findChild(const TiXmlElement *parent, string const &name) {
  for (const TiXmlElement *elem = parent->FirstChildElement();
       elem != NULL;
       elem = elem->NextSiblingElement()) {
    if (elem && elem->Attribute("name") && (name == elem->Attribute("name"))) {
      return elem;
    }
  }
  return NULL;
}

string
Loader::toString() const {
  ostringstream out;
  out << "{Loader-system name=" << getName() << "}" << ends;
  return out.str();
}
