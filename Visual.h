#include "Component.h"

class Visual: public Component {
public:
  typedef unsigned int ImgId;
  
private:
  ImgId img;
  int x;
  int y;
  int w;
  int h;
  
public:
  static const Type TYPE = VISUAL_TYPE;
  
  Visual(ImgId img);
  Visual(ImgId img, int x, int y, int w, int h);
  virtual ~Visual();

  virtual string toString() const;
};
