#pragma once

// Just an interface
class VisualContext {
public:
  virtual ~VisualContext() {};
  virtual int getWidth() const=0;
  virtual int getHeight() const=0;
};
