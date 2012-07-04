#pragma once

#include "Component.h"

class Audio: public Component {
private:
  string name_;
  bool   looping_;
  bool   played_;
  // ? Volume
public:
  static const Type TYPE = AUDIO_TYPE;

  Audio(const string &name, bool looping = false);
  virtual ~Audio();

  inline
  virtual bool isConcrete() {
    return false;
  }
  inline
  const string &getName() const {
    return name_;
  }
  inline
  void setName(const string &name) {
    name_ = name; // Should stop playing...
  }
  inline
  bool isLooping() const {
    return looping_;
  }
  inline
  void setLooping(bool looping) {
    looping_ = looping;
  }
  inline
  bool hasPlayed() const {
    return played_;
  }

  inline virtual void play() {
    played_ = true;
  };
  inline virtual bool isPlaying() {
    return false;
  };
  inline virtual void stop() {};
  
  virtual string toString() const;
};
