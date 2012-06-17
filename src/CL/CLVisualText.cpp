#include <sstream>

#include "CLVisualText.h"

CLVisualText::CLVisualText(string const &text, CL_Font &font, CL_Colorf const &color):
  text(text), font(font), color(color) {
}

CLVisualText::~CLVisualText() {
}

void
CLVisualText::render(CL_GraphicContext &gc, float x, float y) {
  font.draw_text(gc, x, y, text, color);
}

string
CLVisualText::toString() const {
  ostringstream out;
  out << "{CLVisualText text=" << text << "}" << ends;
  return out.str();
}
