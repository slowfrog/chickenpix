#include <sstream>

#include "CLVisualContext.h"
#include "CLVisualText.h"

CLVisualText::CLVisualText(string const &text, CL_Font &font,
                           CL_Colorf const &color):
  VisualText(text), font_(font), color_(color), width_(-1), height_(-1) {
}

CLVisualText::~CLVisualText() {
}

void
CLVisualText::draw(VisualContext &vc, float x, float y, int delta) {
  CL_GraphicContext &gc = ((CLVisualContext &)vc).getGraphicContext();
  CL_FontMetrics fm = font_.get_font_metrics();
  float dy = fm.get_ascent();
  font_.draw_text(gc, x, y + dy, text_, color_);
}

void
CLVisualText::computeSize(VisualContext &vc) const {
  CL_Size size =
    font_.get_text_size(((CLVisualContext &) vc).getGraphicContext(), text_);
  width_ = size.width;
  height_ = size.height;
}

int
CLVisualText::getWidth(VisualContext &vc) const {
  if (width_ < 0) {
    computeSize(vc);
  }
  return width_;
}

int
CLVisualText::getHeight(VisualContext &vc) const {
  if (height_ < 0) {
    computeSize(vc);
  }
  return height_;
}

CPColor
CLVisualText::getColor() const {
  return CPColor(color_.get_red(), color_.get_green(), color_.get_blue(),
                 color_.get_alpha());
}

void
CLVisualText::setColor(const CPColor &color) {
  color_ = CL_Colorf(color.r, color.g, color.b, color.a);
}

string
CLVisualText::toString() const {
  ostringstream out;
  out << "{CLVisualText text=" << text_ << "}" << ends;
  return out.str();
}
