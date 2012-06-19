#pragma once
#include "Component.h"
#include "Image.h"
#include "VisualContext.h"

class BVisual: public Component {
  
private:
  ImagePart part;
  
public:
  static const Type TYPE = VISUAL_TYPE;
  
  BVisual(ImgId img);
  BVisual(ImgId img, int x, int y, int w, int h);
  virtual ~BVisual();

  virtual void draw(VisualContext &vc, float x, float y) = 0;

  virtual string toString() const;
};
