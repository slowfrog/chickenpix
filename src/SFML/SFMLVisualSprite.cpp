/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "SFMLVisualContext.h"
#include "SFMLVisualSprite.h"

SFMLVisualSprite::SFMLVisualSprite(sf::Image &image, vector<Frame> const &frames, bool pingpong):
  sprite_(image), frames_(frames), pingpong_(pingpong), frame_(0),
  dir_(frames.size() > 1 ? 1 : 0),
  timeLeft_(frames[0].duration) {
}

SFMLVisualSprite::~SFMLVisualSprite() {
}

void
SFMLVisualSprite::draw(VisualContext &vc, float x, float y, int delta) {
  sf::RenderTarget &rt = ((SFMLVisualContext &)vc).getRenderTarget();
  sprite_.SetPosition(x, y);
  Frame &f = frames_[frame_];
  ImageRect &p = f.rect;
  sprite_.SetSubRect(sf::IntRect(p.x, p.y, p.x + p.w, p.y + p.h));
  rt.Draw(sprite_);

  int realDelta = (delta > 0) ? delta : 15;
  timeLeft_ -= realDelta;
  while (timeLeft_ < 0) {
    if (!pingpong_) {
      frame_ = (frame_ + 1) % frames_.size();
    } else {
      if ((frame_ + dir_ < 0) || (frame_ + dir_ >= (int) frames_.size())) {
        dir_ = -dir_;
      }
      frame_ = frame_ + dir_;
    }

    timeLeft_ += frames_[frame_].duration;
  }
}

void
SFMLVisualSprite::debugDraw(VisualContext &vc, float x, float y, int delta,
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
SFMLVisualSprite::getWidth(VisualContext &) const {
  return frames_[frame_].rect.w;
}

int
SFMLVisualSprite::getHeight(VisualContext &)const {
  return frames_[frame_].rect.h;
}


string
SFMLVisualSprite::toString() const {
  return "{SFMLVisualSprite";
}
