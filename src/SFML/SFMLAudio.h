#pragma once

#include "SFML.h"
#include "../Audio.h"

namespace sf {
  class Sound;
};

class SFMLAudio: public Audio {
private:
  sf::SoundBuffer &buffer_;
  sf::Sound sound_;

public:
  SFMLAudio(sf::SoundBuffer &buffer);
  virtual ~SFMLAudio();

  virtual void play();
  virtual bool isPlaying();
  virtual void stop();
  
  
  virtual string toString() const;
};
