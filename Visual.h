#include "Component.h"
#include "Image.h"

class Visual: public Component {
  
private:
  ImagePart part;
  
public:
  static const Type TYPE = VISUAL_TYPE;
  
  Visual(ImgId img);
  Visual(ImgId img, int x, int y, int w, int h);
  virtual ~Visual();

  virtual string toString() const;
};
