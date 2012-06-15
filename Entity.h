#include <string>
#include <vector>
#include "Component.h"

using namespace std;

class Entity {
public:
  typedef unsigned int Id;
  
private:
  Id id;
  vector<Component> comp;
  
public:
  explicit Entity(Id id);
  
  ~Entity();

  inline Id getId() const {
    return id;
  }
  
  void addComponent(Component const &c);

  void removeComponent(Component::Type t);

  string toString() const;
};

  
