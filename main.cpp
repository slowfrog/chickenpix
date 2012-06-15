#include <iostream>
#include "Entity.h"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "Starting centity" << endl;
  Entity e(143);
  cout << "Entity id: " << e.getId() << endl;
  Component c1(4);
  cout << "Component type: " << c1.getType() << endl;
  
  e.addComponent(c1);
  Component c2(5);
  e.addComponent(c2);

  cout << "Entity: " << e.toString() << endl;

  cout << "Ending centity" << endl;
  return 0;
}
