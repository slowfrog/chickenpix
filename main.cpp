#include <iostream>
#include <vector>

#include "EntityManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Mobile.h"
#include "Visual.h"
#include "Animated.h"
#include "Input.h"
#include "Resource.h"
#include "System.h"
#include "Loader.h"
#include "Render.h"

using namespace std;

int main(int argc, char const *argv[]) {
  try{
    cout << "Starting centity" << endl;
    EntityManager em("main");
    Entity *pe = em.createEntity();
    Entity &e = *pe;
    cout << "Entity id: " << e.getId() << endl;
    Transform *c1 = new Transform(1.3f, 4.6f);
    cout << "Component type: " << c1->getType() << endl;
    e.addComponent(c1);
    cout << "Entity has Transform: " << e.hasComponent(Transform::TYPE) << endl;
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
    
    e.removeComponent(Visual::TYPE);
    cout << "Entity with n-1 component: " << e.toString() << endl;
    
    cout << em.toString() << endl;
    Entity *e2 = em.createEntity();
    e2->addComponent(new Input());
    cout << "e2=" << e2->toString() << endl;
    cout << em.createEntity()->toString() << endl;
    cout << em.createEntity()->toString() << endl;
    cout << em.toString() << endl;
    vector<Entity *>inputs = em.getEntities(Input::TYPE);
    cout << "Found entities (1): " << inputs.size() << endl;

    cout << e.hasComponent(Input::TYPE) << "|" <<  e.hasComponent(Transform::TYPE) << "|" <<
      e.hasComponents(Input::TYPE, Transform::TYPE) << endl;
    inputs = em.getEntities(Input::TYPE, Transform::TYPE);
    cout << "Found entities (2): " << inputs.size() << endl;
    cout << "Transform entity: " << em.getEntity(Transform::TYPE)->toString() << endl;

    em.destroyEntity(e2);
    cout << em.toString() << endl;

    Loader loader("load", em);
    cout << loader.toString() << endl;

    Render render("render", em);
    cout << render.toString() << endl;

    cout << "Ending centity" << endl;
  } catch (string const &exc) {
    cout << "ERROR: " << exc << endl;
  }
  return 0;
}
