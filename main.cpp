#include <iostream>
#include "Entity.h"
#include "Transform.h"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "Starting centity" << endl;
  Entity e(143);
  cout << "Entity id: " << e.getId() << endl;
  Transform *c1 = new Transform(1.3f, 4.6f);
  cout << "Component type: " << c1->getType() << endl;
  
  e.addComponent(c1);
  Component *c2 = new Component(5);
  e.addComponent(c2);
  cout << "Entity with 2 components: " << e.toString() << endl;
  Component *c3 = e.getComponent(5);
  cout << "Found component: " << c3->toString() << endl;
  try {
    cout << "Trying to get an absent component" << endl;
    e.getComponent(44);
    cout << "Huho, should not be here!" << endl;
  } catch (int e) {
    cout << "Expected exception thrown" << endl;
  }

  e.removeComponent(c1->getType());
  cout << "Entity with 1 component: " << e.toString() << endl;

  cout << "Ending centity" << endl;
  return 0;
}
