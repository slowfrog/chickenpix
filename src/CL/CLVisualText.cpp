#include <sstream>

#include "CLVisualContext.h"
#include "CLVisualText.h"

CLVisualText::CLVisualText(string const &text, CL_Font &font, CL_Colorf const &color):
  text(text), font(font), color(color) {
}

CLVisualText::~CLVisualText() {
}

void
CLVisualText::draw(VisualContext &vc, float x, float y, int delta) {
  CL_GraphicContext &gc = ((CLVisualContext &)vc).getGraphicContext();
  CL_FontMetrics fm = font.get_font_metrics();
  float dy = fm.get_ascent();
  font.draw_text(gc, x, y + dy, text, color);
}

string
CLVisualText::toString() const {
  ostringstream out;
  out << "{CLVisualText text=" << text << "}" << ends;
  return out.str();
}
