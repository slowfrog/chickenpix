#include "Component.h"

class Mobile: public Component {
private:
  float dx;
  float dy;
  
public:
  static const Type TYPE = MOBILE_TYPE;
  
  Mobile(float dx, float dy);
  virtual ~Mobile();

  virtual string toString() const;
};
