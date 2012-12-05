/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../tinyxml/tinyxml.h"

#include "../log.h"
#include "../Utils.h"
#include "../Animated.h"
#include "../Input.h"
#include "../Resources.h"
#include "../Scriptable.h"
#include "../Transform.h"
#include "SFMLLoader.h"
#include "SFMLResources.h"
#include "SFMLVisualContext.h"
#include "SFMLVisualImage.h"
#include "SFMLVisualText.h"

static void
splitXY(string const &str, int *res) {
  size_t pos = str.find(",");
  res[0] = atoi(str.substr(0, pos).c_str());
  res[1] = atoi(str.substr(pos + 1).c_str());
}

static string YES = "yes";
SFMLLoader::SFMLLoader( string const &name):
  Loader(name) {
}

SFMLLoader::~SFMLLoader() {
  if (doc) {
    delete doc;
  }
}

// void 
// SFMLLoader::prepareXml(){
//   doc = new TiXmlDocument( resourceFile);
//   assert( doc);
//   doc->LoadFile();
//   if (doc->Error()) {
//     LOG2ERR << "Error parsing file: " << resourceFile << ", " << doc->ErrorDesc() << "\n";
//   }
// }


// // Resources parsers
// // -----------------------------------------

// // !!! Code a factoriser peut etre !!!

// // Image from XML
// void 
// SFMLLoader::addImage( Resources *resources){
//   const TiXmlElement *pNode    = doc->FirstChildElement("resources");
//   const TiXmlElement *pImgNode = findChild(pNode, "images");
//   // loop on image
//   for ( pImgNode = pImgNode->FirstChildElement("image");
//         pImgNode;
//         pImgNode = pImgNode->NextSiblingElement())
//   {
//     // Name
//     std::string name;
//     pImgNode->QueryValueAttribute( "name", &name);
//     // File
//     std::string file, anti_alias;
//     const TiXmlElement *pImgFileNode = pImgNode->FirstChildElement("image");
//     if ( pImgFileNode) {
//       pImgFileNode->QueryValueAttribute( "file", &file);
//     }
    
//     if ( !name.empty() && !file.empty()){ 
//       addImage(  "resources/" + file, resources, name); 
//     }
//     else {
//       LOG2ERR<<"Mismatch attribute when creating image resources\n";
//     }
//   }
// }

// // Font from XML
// void 
// SFMLLoader::addFont( Resources *resources){
//   const TiXmlElement *pNode    = doc->FirstChildElement("resources");
//   const TiXmlElement *pImgNode = findChild(pNode, "fonts");
//   // loop on font
//   for ( pImgNode = pImgNode->FirstChildElement("font");
//         pImgNode;
//         pImgNode = pImgNode->NextSiblingElement())
//   {
//     // Name
//     std::string name;
//     pImgNode->QueryValueAttribute( "name", &name);
//     // Style
//     std::string file;
//     int         height(0);
//     const TiXmlElement *pImgFileNode = pImgNode->FirstChildElement("freetype");
//     if ( pImgFileNode) {
//       pImgFileNode->QueryValueAttribute( "file", &file);
//       pImgFileNode->QueryValueAttribute( "height", &height);
//     }
    
//     if ( !name.empty() && !file.empty()){ 
//       addFont( "resources/" + file, height, resources, name); 
//     }
//     else {
//       LOG2ERR<<"Mismatch attribute when creating font resources\n";
//     }
//   }
// }

// // Sprite from XML
// void 
// SFMLLoader::addSprites( Resources *resources){
//   const TiXmlElement *pNode    = doc->FirstChildElement("resources");
//   const TiXmlElement *pImgNode = findChild(pNode, "sprites");
//   // loop on font
//   for ( pImgNode = pImgNode->FirstChildElement("sprite");
//         pImgNode;
//         pImgNode = pImgNode->NextSiblingElement())
//   {
//     // Name
//     std::string name;
//     pImgNode->QueryValueAttribute( "name", &name);
//     if ( !name.empty()){ 
//       addSprite( "sprites/" + name, resources, name); 
//     }
//     else {
//       LOG2ERR<<"Mismatch attribute when creating font resources\n";
//     }
//   }
// }

// // Audio from XML
// void 
// SFMLLoader::addAudio( Resources *resources){
//   const TiXmlElement *pNode    = doc->FirstChildElement("resources");
//   const TiXmlElement *pImgNode = findChild(pNode, "samples");
//   // loop on font
//   for ( pImgNode = pImgNode->FirstChildElement("sample");
//         pImgNode;
//         pImgNode = pImgNode->NextSiblingElement())
//   {
//     // Name
//     std::string name;
//     pImgNode->QueryValueAttribute( "name", &name);
//     // Style
//     std::string file, anti_alias;
//     const TiXmlElement *pImgFileNode = pImgNode->FirstChildElement("sample");
//     if ( pImgFileNode) {
//       pImgFileNode->QueryValueAttribute( "file", &file);
//     }
    
//     if ( !name.empty() && !file.empty()){ 
//       addAudio( "resources/" + file, resources, name); 
//     }
//     else {
//       LOG2ERR<<"Mismatch attribute when creating font resources\n";
//     }
//   }
  
// }

// Resources builders
// -----------------------------------------
void
SFMLLoader::addImage(string const &path, Resources *resources, string const &alias) const {
  sf::Image *img = new sf::Image();
  if (!img->LoadFromFile(path)) {
    cerr << "Error loading image: " << path << endl;
    return;
  }
  img->SetSmooth( false);
  resources->setImage(path, new SFMLResImage(img));
  if (alias.length() > 0) {
    resources->setImage(alias, new SFMLResImage(img));
  }
}

void
SFMLLoader::addFont(string const &path, int size, Resources *resources, string const &alias) {
  sf::Font *font = new sf::Font();
  if (!font->LoadFromFile("resources/fonts/BerkshireSwash-Regular.ttf", size)) {
    cerr << "Error loading font: " << path << endl;
    *font = sf::Font::GetDefaultFont();
  }
  ((sf::Image &)(font->GetImage())).SetSmooth(false);
  resources->setFont(path, new SFMLResFont(font));
  if (alias.length() > 0) {
    resources->setFont(alias, new SFMLResFont(font));
  }
}

// const TiXmlElement *
// SFMLLoader::findChild(const TiXmlElement *parent, string const &name) {
//   for (const TiXmlElement *elem = parent->FirstChildElement();
//        elem != NULL;
//        elem = elem->NextSiblingElement()) {
//     if (elem && elem->Attribute("name") && (name == elem->Attribute("name"))) {
//       return elem;
//     }
//   }
//   return NULL;
// }

void
SFMLLoader::loadSpriteFromXML(string const &directory, TiXmlDocument *doc, string const &path,
                              Resources *resources, string const &name) {
  
  const TiXmlElement *curElem = doc->FirstChildElement("resources");
  size_t prev = 0;
  while(true) {
    size_t pos = path.find("/", prev);
    string part = path.substr(prev, pos);
    curElem = findChild(curElem, part);
    if (!curElem) {
      cerr << "No matching node found for: " << part << endl;
      return;
    }

    if (pos == string::npos) {
      break;
    }
    prev = pos + 1;
  }
  if (curElem->ValueStr() == "sprite") {
    // Look for whole animation parameters
    bool pingpong = false;
    bool loop = true;
    int speed = 100;
    const TiXmlElement *anim = curElem->FirstChildElement("animation");
    if (anim) {
      if (anim->Attribute("loop") && (YES == anim->Attribute("loop"))) {
        loop = true;
      }
      if (anim->Attribute("pingpong") && (YES == anim->Attribute("pingpong"))) {
        pingpong = true;
      }
      if (anim->Attribute("speed")) {
        anim->Attribute("speed", &speed);
      }
    }

    // Find the image and the grid to cut the pieces
    const TiXmlElement *image = curElem->FirstChildElement("image");
    string imageFile = directory + "/" + image->Attribute("file");
    const TiXmlElement *grid = image->FirstChildElement("grid");
    string const &posStr = grid->Attribute("pos");
    string const &sizeStr = grid->Attribute("size");
    string const &arrayStr = grid->Attribute("array");
    int pos[2], size[2], array[2];
    splitXY(posStr, pos);
    splitXY(sizeStr, size);
    splitXY(arrayStr, array);
    int count = array[0] * array[1];
    vector<Frame> frames(count, Frame(0, 0, size[0], size[1], speed));
    int i = 0;
    for (int y = 0; y < array[1]; ++y) {
      for (int x = 0; x < array[0]; ++x) {
        frames[i].rect.x = pos[0] + size[0] * x;
        frames[i].rect.y = pos[1] + size[1] * y;
        ++i;
      }
    }

    // Look for specific frame instructions
    for (const TiXmlElement *frame = curElem->FirstChildElement("frame");
         frame != NULL; frame = frame->NextSiblingElement("frame")) {
      int findex = -1;
      int fspeed = -1;
      frame->Attribute("nr", &findex);
      frame->Attribute("speed", &fspeed);
      if ((findex >= 0) && (findex < (int) frames.size()) && (fspeed > 0)) {
        frames[findex].duration = fspeed;
      }
    }

    // Look for the image in image resources to avoid allocating several times
    ResImage *cached = resources->getImage(imageFile);
    if (!cached) {
      addImage(imageFile, resources);
      cached = resources->getImage(imageFile);
    }
    resources->setSprite(name, new SFMLResSprite(&((SFMLResImage *) cached)->get(),
                                                 frames, pingpong));
  }
}

void
SFMLLoader::addSprite(string const &path, Resources *resources, string const &name) {
  if (doc == NULL) {
    cerr << "Resource file not loaded: " << resourceFile << endl;
    assert(!(doc == NULL));
  }
  // Load and parse
  loadSpriteFromXML(getDirectory(doc->Value()), doc, path, resources, name);
}

void
SFMLLoader::addAudio(string const &path, Resources *resources,
                     string const &alias) {
  sf::SoundBuffer *buffer = new sf::SoundBuffer();
  if (!buffer->LoadFromFile(path)) {
    cerr << "Error loading audio: " << path << endl;
    return;
  }
  resources->setAudio(path, new SFMLResAudio(buffer));
  if (alias.length() > 0) {
    resources->setAudio(alias, new SFMLResAudio(buffer));
  }
}

string
SFMLLoader::toString() const {
  ostringstream out;
  out << "{SFMLLoader-system name=" << getName() << "}" << ends;
  return out.str();
}
