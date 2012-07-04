#pragma once

#include "../Audio.h"

class CL_SoundBuffer;
class CL_SoundBuffer_Session;

class CLAudio: public Audio {
private:
  CL_SoundBuffer &buffer_;
  CL_SoundBuffer_Session session_;

public:
  CLAudio(const string &name, bool looping, CL_SoundBuffer &buffer);
  virtual ~CLAudio();

  inline
  virtual bool isConcrete() {
    return true;
  }
  virtual void play();
  virtual bool isPlaying();
  virtual void stop();
  
  
  virtual string toString() const;
};
