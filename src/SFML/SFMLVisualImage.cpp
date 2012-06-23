#include "SFMLVisualImage.h"
#include "SFMLVisualContext.h"

SFMLVisualImage::SFMLVisualImage(sf::Image const &image):
  sprite(image) {
}

SFMLVisualImage::~SFMLVisualImage() {
}

void
SFMLVisualImage::draw(VisualContext &vc, float x, float y, int delta) {
  sf::RenderTarget &rt = ((SFMLVisualContext &)vc).getRenderTarget();
  sprite.SetPosition(x, y);
  rt.Draw(sprite);
}

string
SFMLVisualImage::toString() const {
  return "{SFMLVisualImage}";
}
