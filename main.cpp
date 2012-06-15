#include <iostream>
#include <vector>

#include "Entity.h"
#include "Transform.h"
#include "Mobile.h"
#include "Visual.h"
#include "Animated.h"
#include "Input.h"
#include "Resource.h"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "Starting centity" << endl;
  Entity e(143);
  cout << "Entity id: " << e.getId() << endl;
  Transform *c1 = new Transform(1.3f, 4.6f);
  cout << "Component type: " << c1->getType() << endl;
  e.addComponent(c1);
  e.addComponent(new Mobile(-1, -3));
  e.addComponent(new Visual(35));
  e.addComponent(new Visual(12, 1, 2, 3, 4));
  vector<Frame> frames;
  frames.push_back(Frame(0, 1, 2, 3, 4, 5));
  frames.push_back(Frame(12, 0, 0, 32, 32, 100));
  e.addComponent(new Animated("anim", frames));
  e.addComponent(new Input());
  Resource *res = new Resource();
  res->addFrames("dummy", frames);
  e.addComponent(res);
  Component *c2 = new Component(15);
  e.addComponent(c2);
  cout << "Entity with n components: " << e.toString() << endl;
  Component *c3 = e.getComponent(15);
  cout << "Found component: " << c3->toString() << endl;
  try {
    cout << "Trying to get an absent component" << endl;
    e.getComponent(44);
    cout << "Huho, should not be here!" << endl;
  } catch (int e) {
    cout << "Expected exception thrown" << endl;
  }

  e.removeComponent(c1->getType());
  cout << "Entity with n-1 component: " << e.toString() << endl;

  cout << "Ending centity" << endl;
  return 0;
}
