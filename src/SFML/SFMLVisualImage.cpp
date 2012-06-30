#include "SFMLVisualImage.h"
#include "SFMLVisualContext.h"

SFMLVisualImage::SFMLVisualImage(sf::Image const &image):
  sprite(image), rect() {
}

SFMLVisualImage::SFMLVisualImage(sf::Image const &image, ImageRect rect):
  sprite(image), rect(rect) {
}

SFMLVisualImage::~SFMLVisualImage() {
}

void
SFMLVisualImage::draw(VisualContext &vc, float x, float y, int delta) {
  sf::RenderTarget &rt = ((SFMLVisualContext &)vc).getRenderTarget();
  sprite.SetPosition(x, y);
  if (rect.isValid()) {
    sprite.SetSubRect(sf::IntRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h));
  }
  rt.Draw(sprite);
}

string
SFMLVisualImage::toString() const {
  return "{SFMLVisualImage}";
}
