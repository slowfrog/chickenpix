#include <sstream>
#include "CLRender.h"
#include "CLState.h"
#include "Transform.h"
#include "CLVisual.h"
#include "CLVisualText.h"

CLRender::CLRender(string const &name, EntityManager &em):
  System(name, em), window(NULL) {
}

CLRender::~CLRender() {
  delete window;
  window = NULL;
}

void
CLRender::init() {
  window = new CL_DisplayWindow("Hello World", 640, 480);
  Entity *clstate = em.createEntity();
  clstate->addComponent(new CLState(*window));
}

void
CLRender::update(int now) {
  CLState *clstate = em.getComponent<CLState>();
  CL_GraphicContext &gc = clstate->getGC();

  // Background -> Might be later represented as a CLShape, or something like that, with its own render function
  CL_Rect ground(0, 280, 640, 480);
  gc.clear(CL_Colorf::cadetblue);
  gc.push_cliprect(ground);
  gc.clear(CL_Colorf(0.1f, 0.4f, 0.1f));
  gc.pop_cliprect();

  // CLVisual
  vector<Entity *> visuals = em.getEntities(CLVisual::TYPE, Transform::TYPE);
  for (vector<Entity *>::iterator it = visuals.begin(); it < visuals.end(); it++) {
    Entity *entity = *it;
    Transform *t = entity->getComponent<Transform>();
    CLVisual *v = entity->getComponent<CLVisual>();

    v->render(gc, t->getX(), t->getY());
  }

  // Make the stuff visible:
  clstate->getWindow().flip();
}

void
CLRender::exit() {
}

string
CLRender::toString() const {
  ostringstream out;
  out << "{CLRender-System name=" << getName() << "}" << ends;
  return out.str();
}
