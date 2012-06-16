#include <sstream>

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/swrender.h>
//#include <ClanLib/application.h>

#include "ClanLib.h"

ClanLib::ClanLib(string const &name, EntityManager &em):
  System(name, em), setupCore(NULL), setupDisplay(NULL), setupSWRender(NULL) {
}

ClanLib::~ClanLib() {
  delete setupSWRender;
  setupSWRender = NULL;
  delete setupDisplay;
  setupDisplay = NULL;
  delete setupCore;
  setupCore = NULL;
}

void
ClanLib::init() {
  setupCore = new CL_SetupCore();
  setupDisplay = new CL_SetupDisplay();
  setupSWRender = new CL_SetupSWRender();
    //CL_DisplayWindow window("Hello World", 640, 480);
}

void
ClanLib::update(int now) {
}

void
ClanLib::exit() {
}

string
ClanLib::toString() const {
  ostringstream out;
  out << "{Clanlib-System name=" << getName() << "}" << ends;
  return out.str();
}
