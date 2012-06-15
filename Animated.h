#include <vector>
#include "Component.h"
#include "Image.h"

class Animated: public Component {
private:
  string name;
  vector<Frame> frames;
  
public:
  static const Type TYPE = ANIMATED_TYPE;

  Animated(string const &name, vector<Frame> const &frames);
  virtual ~Animated();

  virtual string toString() const;
};
