#include "SFMLVisualImage.h"
#include "SFMLVisualContext.h"

SFMLVisualImage::SFMLVisualImage(sf::Image const &image):
  sprite_(image), rect_() {
}

SFMLVisualImage::SFMLVisualImage(sf::Image const &image, ImageRect rect):
  sprite_(image), rect_(rect) {
}

SFMLVisualImage::~SFMLVisualImage() {
}

void
SFMLVisualImage::draw(VisualContext &vc, float x, float y, int delta) {
  sf::RenderTarget &rt = ((SFMLVisualContext &)vc).getRenderTarget();
  sprite_.SetPosition(x, y);
  if (rect_.isValid()) {
    sprite_.SetSubRect(sf::IntRect(rect_.x, rect_.y, rect_.x + rect_.w, rect_.y + rect_.h));
  }
  rt.Draw(sprite_);
}

void
SFMLVisualImage::debugDraw(VisualContext &vc, float x, float y, int delta,
                           float left, float top, float right, float bottom) {
  // Draw base visual
  draw(vc, x, y, delta);
  
  // For debugging: show a red outline
  sf::RenderTarget &rt = ((SFMLVisualContext &)vc).getRenderTarget();
  float cx = x + getWidth(vc) / 2;
  float cy = y + getHeight(vc) / 2;
  rt.Draw(sf::Shape::Rectangle(cx - left, cy - top, cx + right, cy + bottom,
                               sf::Color(0, 0, 0, 0), 1,
                               sf::Color(255, 0, 0, 80)));
}

int
SFMLVisualImage::getWidth(VisualContext &) const {
  return rect_.isValid() ? rect_.w : sprite_.GetSubRect().GetWidth();
}

int
SFMLVisualImage::getHeight(VisualContext &) const {
  return rect_.isValid() ? rect_.h : sprite_.GetSubRect().GetHeight();
}

string
SFMLVisualImage::toString() const {
  return "{SFMLVisualImage}";
}
