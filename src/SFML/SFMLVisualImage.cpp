#include "SFMLVisualImage.h"

SFMLVisualImage::SFMLVisualImage(sf::Sprite const &sprite):
  sprite(sprite) {
}

SFMLVisualImage::~SFMLVisualImage() {
}

void
SFMLVisualImage::render(sf::RenderTarget &rt, float x, float y) {
  sprite.SetPosition(x, y);
  rt.Draw(sprite);
}

string
SFMLVisualImage::toString() const {
  return "{SFMLVisualImage}";
}
