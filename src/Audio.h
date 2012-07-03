#pragma once

#include "Component.h"

class Audio: public Component {
private:
  // ? Volume
  // ? Loop
public:
  static const Type TYPE = AUDIO_TYPE;

  Audio();
  virtual ~Audio();

  virtual void play() = 0;
  virtual bool isPlaying() = 0;
  virtual void stop() = 0;
  
  virtual string toString() const;
};
