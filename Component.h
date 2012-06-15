#include <string>

using namespace std;

class Component {
public:
  typedef unsigned short Type;
  
private:
  Type type;

public:
  explicit Component(Type type);
  virtual ~Component();

  inline Type getType() const {
    return type;
  }

  virtual string toString() const;
};
