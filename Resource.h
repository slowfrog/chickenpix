#include <map>
#include <vector>
#include "Component.h"
#include "Image.h"

class Resource : public Component {
private:
  map<string, vector<Frame> > framesMap;
public:
  static const Type TYPE = RESOURCE_TYPE;

  Resource();
  virtual ~Resource();
  void addFrames(string const &name, vector<Frame> const &frames);
  
  virtual string toString() const;
};
