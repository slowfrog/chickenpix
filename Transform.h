#include "Component.h"

class Transform: public Component {
private:
  float x;
  float y;
  
public:
  static const Type TYPE = 1;
  
  Transform(float x, float y);
  virtual ~Transform();

  virtual string toString() const;
};
