#pragma once

#include "Component.h"

class Audio: public Component {
private:
  string name_;
  // ? Volume
  // ? Loop
public:
  static const Type TYPE = AUDIO_TYPE;

  Audio(const string &name);
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
  virtual void setName(const string &name) {
    name_ = name; // Should stop playing...
  }

  // Virtual methods with dummy implementation to allow instanciation 
  inline virtual void play() {};
  inline virtual bool isPlaying() { return false; };
  inline virtual void stop() {};
  
  virtual string toString() const;
};
