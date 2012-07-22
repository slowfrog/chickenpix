#include "MapInfo.h"
#include <sstream>

MapInfo::MapInfo(float minx, float miny, float maxx, float maxy):
  Component(TYPE), minx_(minx), miny_(miny), maxx_(maxx), maxy_(maxy) {
}

MapInfo::~MapInfo() {
}

string
MapInfo::toString() const {
  ostringstream out;
  out << "{MapInfo (" << minx_ << "," << miny_ << ")-(" << maxx_ << "," <<
    maxy_ << ")}" << ends;
  return out.str();
}
