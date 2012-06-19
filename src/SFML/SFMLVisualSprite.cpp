#include "SFMLVisualContext.h"
#include "SFMLVisualSprite.h"

SFMLVisualSprite::SFMLVisualSprite(sf::Image &image, vector<Frame> const &frames):
  sprite(image), frames(frames), frame(0) {
}

SFMLVisualSprite::~SFMLVisualSprite() {
}

void
SFMLVisualSprite::draw(VisualContext &vc, float x, float y) {
  sf::RenderTarget &rt = ((SFMLVisualContext &)vc).getRenderTarget();
  sprite.SetPosition(x, y);
  Frame &f = frames[frame];
  ImagePart &p = f.part;
  sprite.SetSubRect(sf::IntRect(p.x, p.y, p.x + p.w, p.y + p.h));
  rt.Draw(sprite);
  frame = (frame + 1) % frames.size();
}


string
SFMLVisualSprite::toString() const {
  return "{SFMLVisualSprite";
}
