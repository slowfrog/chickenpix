#pragma once
#include "../Resources.h"
#include "../Loader.h"

class SFMLLoader: public Loader {
private:
  void loadImage(string const &name, string const &path, Resources *resources);

public:
  SFMLLoader(string const &name, EntityManager &em);
  virtual ~SFMLLoader();

  virtual void init();
  virtual void update(int now);
  virtual void exit();

  virtual string toString() const;
};
