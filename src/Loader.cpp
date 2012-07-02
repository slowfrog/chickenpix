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
#include "log.h"

static const int BASE_MAP_ZORDER = -5;

Loader::Loader(string const &name, EntityManager &em, string const &resourceFile):
System(name, em), resourceFile(resourceFile) {
}

Loader::~Loader() {
}

void
Loader::init() {
  // Load resources
  initResources();
  // Add resources
  //Resources *resources = _em.getComponent<Resources>();
  
  /*
  addImage("resources/img/map.png", resources, "map");
  addImage("resources/img/cochon.png", resources, "pig");
  addImage("resources/img/garcon_des_rues.png", resources, "streetboy");
  addImage("resources/img/magicien.png", resources, "wizard");
  addImage("resources/img/maire.png", resources, "mayor");
  addImage("resources/img/princesse.png", resources, "princess");
  addImage("resources/img/richard.png", resources, "richard");
  
  addFont("resources/fonts/BerkshireSwash-Regular.ttf", 30, resources, "sans_big");
  addFont("resources/fonts/BerkshireSwash-Regular.ttf", 8, resources, "sans_small");
  
  addSprite("sprites/walk_up", resources, "man_walk_up");
  addSprite("sprites/walk_left", resources, "man_walk_left");
  addSprite("sprites/walk_down", resources, "man_walk_down");
  addSprite("sprites/walk_right", resources, "man_walk_right");
  addSprite("sprites/stand_up", resources, "man_stand_up");
  addSprite("sprites/stand_left", resources, "man_stand_left");
  addSprite("sprites/stand_down", resources, "man_stand_down");
  addSprite("sprites/stand_right", resources, "man_stand_right");
  addSprite("sprites/wait", resources, "man_still");
   */
  
  // Load start level
  loadLevel("beach");
}

void
Loader::update(int now) {
}

void
Loader::exit() {
}

void
Loader::createImage(ImagePart const &part, float x, float y, int zOrder,
                    Resources *resources) const {
  Entity *img = _em.createEntity();
  img->addComponent(new Transform(x, y));
  BVisual *image = resources->makeImage(part);
  image->setZOrder(zOrder);
  img->addComponent(image);
}

void
Loader::loadLevel(string const &name) {
  // Get resources
  Resources *resources = _em.getComponent<Resources>();
  if ( !resFile.empty() ){
    // Use Builder to create resources
    CEntityBuilder eb( resFile); // File is hardcoded but this should be change
    eb.parseResources( this, resources);
    // Load map (tmx)
    loadTmxMap(string("resources/maps/") + name + ".tmx");
    // Use builder to create entities
    eb.parseEntity   ( _em, resources);
  }else {
    throw "xml desc file for entities is missing";
  }

  
  
  // Hard coded start level
  //createImage("map", -150, -250, resources);
  
  //createImage("pig", 210, 635, resources);
  
  // createImage("streetboy", 50, 350, resources);
  // createImage("mayor", 90, 350, resources);
  // createImage("princess", 130, 350, resources);
  // createImage("wizard", 170, 350, resources);
  // createImage("richard", 210, 350, resources);
  
  /*
  Entity *hero = _em.createEntity();
  hero->addComponent(new Transform(410, 620));
  hero->addComponent(new Animated("man_stand_down"));
  hero->addComponent(new Input());
  hero->addComponent(new Scriptable("toto"));
  hero->addComponent(new Mobile());
  hero->addComponent(new Camera());
  _em.tagEntity(hero, "HERO", true);
  _em.tagEntity(hero, "DummyTag");
  
  Entity *text = _em.createEntity();
  text->addComponent(new Transform(290, 475));
  text->addComponent(resources->makeText("Chickenpix!", "sans_big", CPColor(255, 255, 0, 128)));
  _em.tagEntity(text, "LABEL");
  text = _em.createEntity();
  text->addComponent(new Transform(235, 365));
  text->addComponent(resources->makeText("Press [ESC] to quit...", "sans_small"));
  _em.tagEntity(text, "LABEL");
  */
}

void
Loader::loadTmxMap(string const &name) const {
  Resources *resources = _em.getComponent<Resources>();
  
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
                                         tileset->GetTileWidth(), tileset->GetTileHeight());
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
            createImage(tilesetImages[tileset->GetFirstGid() + tile.id],
                        (float) x * map.GetTileWidth(), (float) y * map.GetTileHeight(),
                        BASE_MAP_ZORDER + i, resources);
          }
          // cout << "]" << endl;
        }
      }
    }
  }
}

void 
Loader::setEntitiesDesc( const std::string& file){
  resFile = file;
}

string
Loader::toString() const {
  ostringstream out;
  out << "{Loader-system name=" << getName() << "}" << ends;
  return out.str();
}
