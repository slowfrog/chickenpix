#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../tinyxml/tinyxml.h"

#include "SFMLLoader.h"
#include "../Animated.h"
#include "../Input.h"
#include "../Resources.h"
#include "../Scriptable.h"
#include "../Transform.h"
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

static string
getDirectory(string const &str) {
  size_t pos = str.rfind("/");
  if (pos == string::npos) {
    return str;
  } else {
    return str.substr(0, pos);
  }
}

static string YES = "yes";
SFMLLoader::SFMLLoader(string const &name, EntityManager &em, string const &resourceFile):
  Loader(name, em, resourceFile), doc(NULL) {
}

SFMLLoader::~SFMLLoader() {
  if (doc) {
    delete doc;
  }
}

void
SFMLLoader::initResources() {
  doc = new TiXmlDocument( resourceFile);
  doc->LoadFile();
  if (doc->Error()) {
    cerr << "Error parsing file: " << resourceFile << ", " << doc->ErrorDesc() << endl;
  }
}

void
SFMLLoader::addImage(string const &path, Resources *resources, string const &alias) {
  sf::Image *img = new sf::Image();
  if (!img->LoadFromFile(path)) {
    cerr << "Error loading image: " << path << endl;
    return;
  }
  img->SetSmooth(false);
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

const TiXmlElement *
findChild(const TiXmlElement *parent, string const &name) {
  for (const TiXmlElement *elem = parent->FirstChildElement();
       elem != NULL;
       elem = elem->NextSiblingElement()) {
    if (elem && elem->Attribute("name") && (name == elem->Attribute("name"))) {
      return elem;
    }
  }
  return NULL;
}

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
        frames[i].part.x = pos[0] + size[0] * x;
        frames[i].part.y = pos[1] + size[1] * y;
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

string
SFMLLoader::toString() const {
  ostringstream out;
  out << "{SFMLLoader-system name=" << getName() << "}" << ends;
  return out.str();
}
