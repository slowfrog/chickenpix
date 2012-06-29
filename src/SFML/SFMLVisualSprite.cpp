#include "SFMLVisualContext.h"
#include "SFMLVisualSprite.h"

SFMLVisualSprite::SFMLVisualSprite(sf::Image &image, vector<Frame> const &frames, bool pingpong):
  sprite(image), frames(frames), pingpong(pingpong), frame(0),
  dir(frames.size() > 1 ? 1 : 0),
  timeLeft(frames[0].duration) {
}

SFMLVisualSprite::~SFMLVisualSprite() {
}

void
SFMLVisualSprite::draw(VisualContext &vc, float x, float y, int delta) {
  sf::RenderTarget &rt = ((SFMLVisualContext &)vc).getRenderTarget();
  sprite.SetPosition(x, y);
  Frame &f = frames[frame];
  ImageRect &p = f.rect;
  sprite.SetSubRect(sf::IntRect(p.x, p.y, p.x + p.w, p.y + p.h));
  rt.Draw(sprite);

  int realDelta = (delta > 0) ? delta : 15;
  timeLeft -= realDelta;
  while (timeLeft < 0) {
    if (!pingpong) {
      frame = (frame + 1) % frames.size();
    } else {
      if ((frame + dir < 0) || (frame + dir >= (int) frames.size())) {
        dir = -dir;
      }
      frame = frame + dir;
    }

    timeLeft += frames[frame].duration;
  }
}


string
SFMLVisualSprite::toString() const {
  return "{SFMLVisualSprite";
}
