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
  SFMLAudio(const string &name, sf::SoundBuffer &buffer);
  virtual ~SFMLAudio();

  inline
  virtual bool isConcrete() {
    return true;
  }
  virtual void play();
  virtual bool isPlaying();
  virtual void stop();
  
  virtual string toString() const;
};
