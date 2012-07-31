#include <Python.h>
#include "log.h"
#include "PythonComponents.h"
#include "ComponentRegistry.h"
#include "WrappedEntity.h"
#include "Animated.h"
#include "VisualText.h"
#include "Audio.h"
#include "Camera.h"
#include "Input.h"
#include "InputState.h"
#include "Mobile.h"
#include "Transform.h"
#include "Collider.h"
#include "Actionable.h"


//
static PyObject *NO_ARGS = PyTuple_New(0);
static PyObject *NO_KWDS = PyDict_New();

static
int Component_init(PyObject *self, Component *compo) {
  if (PyComponentType.tp_init(self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  ((PyComponent *) self)->component = compo;
  return 0;
}

// Transform type and methods ---------------------------------------------------
static PyTypeObject PyTransformType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Transform",
  sizeof(PyComponent),
};

static
int Transform_init(PyObject *self, PyObject *args, PyObject *kwds) {
  float x, y;
  if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
    return -1;
  }
  return Component_init(self, new Transform(x, y));
}

static
PyObject *Transform_getx(PyObject *self, void *) {
  Transform *t = (Transform *) ((PyComponent *) self)->component;
  return PyFloat_FromDouble(t->getX());
}

static
int Transform_setx(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Transform.x must be a number");
    return -1;
  }
  Transform *t = (Transform *) ((PyComponent *) self)->component;
  t->setX((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Transform_gety(PyObject *self, void *) {
  Transform *t = (Transform *) ((PyComponent *) self)->component;
  return PyFloat_FromDouble(t->getY());
}

static
int Transform_sety(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Transform.y must be a number");
    return -1;
  }
  Transform *t = (Transform *) ((PyComponent *) self)->component;
  t->setY((float) PyFloat_AsDouble(val));
  return 0;
}

static PyGetSetDef Transform_getset[] = {
  { (char *) "x", Transform_getx, Transform_setx,
    (char *) "The x coordinate", NULL },
  { (char *) "y", Transform_gety, Transform_sety,
    (char *) "The y coordinate", NULL },
  { NULL, NULL }
};

static
PyObject *Transform_moveTo(PyComponent *self, PyObject *args) {
  Transform *t = (Transform *) self->component;
  float x, y;
  if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
  } else {
    t->moveTo(x, y);
  }
  Py_RETURN_NONE;
}

static
PyObject *Transform_moveBy(PyComponent *self, PyObject *args) {
  Transform *t = (Transform *) self->component;
  float x, y;
  if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
  } else {
    t->moveBy(x, y);
  }
  Py_RETURN_NONE;
}

static PyMethodDef Transform_methods[] = {
  {"moveTo", (PyCFunction) Transform_moveTo, METH_VARARGS,
   "Move to a defined position"},
  {"moveBy", (PyCFunction) Transform_moveBy, METH_VARARGS,
   "Move by a defined displacement"},
  {NULL} /* End of list */
};

// Resources methods ---------------------------------------------------
static PyTypeObject PyResourcesType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Resources",
  sizeof(PyComponent),
};

static
int Resources_init(PyObject *self, PyObject *args, PyObject *kwds) {
  // Should not be called...
  return Component_init(self, NULL);
}

static
PyObject *Resources_makeImage(PyComponent *self, PyObject *args) {
  Resources *r = (Resources *) self->component;
  PyObject *name;
  if (!PyArg_ParseTuple(args, "S", &name)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
    return NULL;
  }

  BVisual *img = r->makeImage(PyString_AsString(name));
  return wrapRealComponent(img);
}

static
PyObject *Resources_makeText(PyComponent *self, PyObject *args) {
  Resources *r = (Resources *) self->component;
  PyObject *text;
  PyObject *font;
  PyObject *color;
  
  if (!PyArg_ParseTuple(args, "SS|O", &text, &font, &color)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
    return NULL;
  }
  CPColor cpcolor = CPColor::White;

  BVisual *txt = r->makeText(PyString_AsString(text),
                             PyString_AsString(font),
                             cpcolor);
  return wrapRealComponent(txt);
}

static PyMethodDef Resources_methods[] = {
  {"makeImage", (PyCFunction) Resources_makeImage, METH_VARARGS,
   "Makes a Visual of type image from the name of a resource"},
  {"makeText", (PyCFunction) Resources_makeText, METH_VARARGS,
   "Makes a Visual of type text from some text, a font and possibly a color"},
  {NULL} /* End of list */
};

// Mobile type and methods -----------------------------------------------------
static PyTypeObject PyMobileType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Mobile",
  sizeof(PyComponent),
};

static
int Mobile_init(PyObject *self, PyObject *args, PyObject *kwds) {
  float speedX, speedY;
  if (!PyArg_ParseTuple(args, "ff", &speedX, &speedY)) {
    return -1;
  }
  return Component_init(self, new Mobile(speedX, speedY));
}

static
PyObject *Mobile_getSpeedX(PyObject *self, void *) {
  Mobile *m = (Mobile *) ((PyComponent *) self)->component;
  return PyFloat_FromDouble(m->getSpeedX());
}

static
int Mobile_setSpeedX(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speedX must be a number");
    return -1;
  }
  Mobile *m = (Mobile *) ((PyComponent *) self)->component;
  m->setSpeedX((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Mobile_getSpeedY(PyObject *self, void *) {
  Mobile *m = (Mobile *) ((PyComponent *) self)->component;
  return PyFloat_FromDouble(m->getSpeedY());
}

static
int Mobile_setSpeedY(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speedY must be a number");
    return -1;
  }
  Mobile *m = (Mobile *) ((PyComponent *) self)->component;
  m->setSpeedY((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Mobile_getSpeed(PyObject *self, void *) {
  Mobile *m = (Mobile *) ((PyComponent *) self)->component;
  return PyTuple_Pack(2,
                      PyFloat_FromDouble(m->getSpeedX()),
                      PyFloat_FromDouble(m->getSpeedY()));
}

static
int Mobile_setSpeed(PyObject *self, PyObject *val, void *) {
  if (!PyTuple_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speed must be a tuple");
    return -1;
  }
  if (PyTuple_Size(val) != 2) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speed must be a two-value tuple");
    return -1;
  }
  PyObject *psx = PyTuple_GetItem(val, 0);
  PyObject *psy = PyTuple_GetItem(val, 1);
  if (!PyNumber_Check(psx)) {
    PyErr_SetString(PyExc_TypeError,
                    "Mobile.speed first element must be a number");
    return -1;
  }
  if (!PyNumber_Check(psy)) {
    PyErr_SetString(PyExc_TypeError,
                    "Mobile.speed second element must be a number");
    return -1;
  }
  
  Mobile *m = (Mobile *) ((PyComponent *) self)->component;
  float sx = (float) PyFloat_AsDouble(psx);
  float sy = (float) PyFloat_AsDouble(psy);
  m->setSpeed(sx, sy);
  return 0;
}

static PyGetSetDef Mobile_getset[] = {
  { (char *) "speedX", Mobile_getSpeedX, Mobile_setSpeedX,
    (char *) "The x speed", NULL },
  { (char *) "speedY", Mobile_getSpeedY, Mobile_setSpeedY,
    (char *) "The y speed", NULL },
  { (char *) "speed", Mobile_getSpeed, Mobile_setSpeed,
    (char *) "The speed as a tuple of two numbers", NULL },
  { NULL, NULL }
};

// Visual type and methods ----------------------------------------------------
static PyTypeObject PyVisualType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Visual",
  sizeof(PyComponent),
};

static
int Visual_init(PyObject *self, PyObject *args, PyObject *kwds) {
  // Should not be called...
  return Component_init(self, NULL);
}


static
PyObject *Visual_getText(PyObject *self, void *) {
  BVisual *visual = (BVisual *) ((PyComponent *) self)->component;
  if (!visual->isText()) {
    PyErr_SetString(PyExc_TypeError, "Visual is not a text");
    return NULL;
  }
  VisualText *vtext = (VisualText *) visual;
  return PyString_FromString(vtext->getText().c_str());
}

static
int Visual_setText(PyObject *self, PyObject *val, void *) {
  BVisual *visual = (BVisual *) ((PyComponent *) self)->component;
  if (!visual->isText()) {
    PyErr_SetString(PyExc_TypeError, "Visual is not a text");
    return -1;
  }
  if (!PyString_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "text must be a string");
    return -1;
  }
  VisualText *vtext = (VisualText *) visual;
  vtext->setText(PyString_AsString(val));
  return 0;
}

static
PyObject *Visual_getColor(PyObject *self, void *) {
  BVisual *visual = (BVisual *) ((PyComponent *) self)->component;
  if (!visual->isText()) {
    PyErr_SetString(PyExc_TypeError, "Visual is not a text");
    return NULL;
  }
  VisualText *vtext = (VisualText *) visual;
  const CPColor &color = vtext->getColor();
  PyObject *ret = PyTuple_Pack(4,
                               PyInt_FromLong(color.r),
                               PyInt_FromLong(color.g),
                               PyInt_FromLong(color.b),
                               PyInt_FromLong(color.a));
  return ret;
}

static
int Visual_setColor(PyObject *self, PyObject *val, void *) {
  BVisual *visual = (BVisual *) ((PyComponent *) self)->component;
  if (!visual->isText()) {
    PyErr_SetString(PyExc_TypeError, "Visual is not a text");
    return -1;
  }
  if (!PyTuple_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "color must be a tuple");
    return -1;
  }
  // TODO: also accept 3-tuple
  if (PyTuple_Size(val) != 4) {
    PyErr_SetString(PyExc_TypeError, "color must be a 4-value tuple");
    return -1;
  }
  
  VisualText *vtext = (VisualText *) visual;
  CPColor color((int) PyInt_AsLong(PyTuple_GetItem(val, 0)),
                (int) PyInt_AsLong(PyTuple_GetItem(val, 1)),
                (int) PyInt_AsLong(PyTuple_GetItem(val, 2)),
                (int) PyInt_AsLong(PyTuple_GetItem(val, 3)));
  vtext->setColor(color);
  return 0;
}


static PyGetSetDef Visual_getset[] = {
  { (char *) "text", Visual_getText, Visual_setText,
    (char *) "The text of a 'textual' visual" },
  { (char *) "color", Visual_getColor, Visual_setColor,
    (char *) "The color of a 'textual' visual" },
  {NULL}
};

static PyObject *
Visual_isText(PyComponent *self) {
  BVisual *visual = (BVisual *) self->component;
  if (visual->isText()) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
};

static PyMethodDef Visual_methods[] = {
  {"isText", (PyCFunction) Visual_isText, METH_NOARGS,
   "Checks if a Visual is a 'textual' one"},
  {NULL}
};

// Animated type and methods ----------------------------------------------------
static PyTypeObject PyAnimatedType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Animated",
  sizeof(PyComponent),
};

static
int Animated_init(PyObject *self, PyObject *args, PyObject *kwds) {
  PyObject *name;
  if (!PyArg_ParseTuple(args, "S", &name)) {
    return -1;
  }
  return Component_init(self, new Animated(PyString_AsString(name)));
}

static
PyObject *Animated_getAnimation(PyObject *self, void *) {
  Animated *a = (Animated *) ((PyComponent *) self)->component;
  return PyString_FromString(a->getAnimation().c_str());
}

static
int Animated_setAnimation(PyObject *self, PyObject *val, void *) {
  if (!PyString_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Animated.animation must be a string");
    return -1;
  }
  Animated *a = (Animated *) ((PyComponent *) self)->component;
  a->setAnimation(PyString_AsString(val));
  return 0;
}

static PyGetSetDef Animated_getset[] = {
  { (char *) "animation", Animated_getAnimation, Animated_setAnimation,
    (char *) "The current animation", NULL },
  { NULL, NULL }
};

// Audio type and methods ----------------------------------------------------
static PyTypeObject PyAudioType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Audio",
  sizeof(PyComponent),
};

static
int Audio_init(PyObject *self, PyObject *args, PyObject *kwds) {
  PyObject *name;
  PyObject *loop;
  if (!PyArg_ParseTuple(args, "S|O", &name, &loop)) {
    return -1;
  }
  bool looping = false;
  if (loop) {
    if (!PyBool_Check(loop)) {
      PyErr_SetString(PyExc_TypeError,
                      "Second argument 'loop' must be a boolean");
      return -1;
    } else {
      looping = (PyObject_IsTrue(loop) != 0);
    }
  }
  return Component_init(self, new Audio(PyString_AsString(name), looping));
}

static
PyObject *Audio_getName(PyObject *self, void *) {
  Audio *a = (Audio *) ((PyComponent *) self)->component;
  return PyString_FromString(a->getName().c_str());
}

static
int Audio_setName(PyObject *self, PyObject *val, void *) {
  if (!PyString_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Audio.name must be a string");
    return -1;
  }
  Audio *a = (Audio *) ((PyComponent *) self)->component;
  a->setName(PyString_AsString(val));
  return 0;
}

static
PyObject *Audio_getLoop(PyObject *self, void *) {
  Audio *a = (Audio *) ((PyComponent *) self)->component;
  if (a->isLooping()) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static
int Audio_setLoop(PyObject *self, PyObject *val, void *) {
  if (!PyBool_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Audio.loop must be a boolean");
    return -1;
  }
  Audio *a = (Audio *) ((PyComponent *) self)->component;
  a->setLooping(PyObject_IsTrue(val) != 0);
  return 0;
}

static
PyObject *Audio_getPlaying(PyObject *self, void *) {
  Audio *a = (Audio *) ((PyComponent *) self)->component;
  if (a->isPlaying()) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static PyGetSetDef Audio_getset[] = {
  { (char *) "name", Audio_getName, Audio_setName,
    (char *) "The current 'sound' name", NULL },
  { (char *) "loop", Audio_getLoop, Audio_setLoop,
    (char *) "Is the sound looping or playing only once", NULL },
  { (char *) "playing", Audio_getPlaying, NULL,
    (char *) "Is the sound currently playing", NULL },
  { NULL, NULL }
};

static
PyObject *Audio_stop(PyComponent *audio) {
  Audio *a = (Audio *) audio->component;
  a->stop();
  Py_RETURN_NONE;
}

static PyMethodDef Audio_methods[] = {
  { "stop", (PyCFunction) Audio_stop, METH_NOARGS,
    "Stop a sound that is currently playing" },
  { NULL }
};

// Input state type and methods ------------------------------------------------
typedef struct {
  PyObject_HEAD
  InputState const *state;
} PyInputState;

static PyTypeObject PyInputStateType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.InputState",
  sizeof(PyInputState),
};

static
PyObject *InputState_isKeyDown(PyInputState *self, PyObject *args) {
  int key;
  if (!PyArg_ParseTuple(args, "i", &key)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
    Py_RETURN_NONE;
  }
  if (self->state->isKeyDown((InputState::Key) key)) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static
PyObject *InputState_isButtonDown(PyInputState *self, PyObject *args) {
  int button;
  if (!PyArg_ParseTuple(args, "i", &button)) {
    if (PyErr_Occurred()) {
      PyErr_Print();
    }
    Py_RETURN_NONE;
  }
  if (self->state->isButtonDown((InputState::MouseButton) button)) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static
PyObject *InputState_getMousePosition(PyInputState *self) {
  InputState::MousePos pos = self->state->getMousePosition();
  return PyTuple_Pack(2, PyInt_FromLong(pos.x), PyInt_FromLong(pos.y));
}

static PyMethodDef InputState_methods[] = {
  { "isKeyDown", (PyCFunction) InputState_isKeyDown, METH_VARARGS,
    "Check if a key is pressed" },
  { "isButtonDown", (PyCFunction) InputState_isButtonDown, METH_VARARGS,
    "Check if a mouse button is pressed" },
  { "getMousePosition", (PyCFunction) InputState_getMousePosition, METH_NOARGS,
    "Get the current mouse position as a tuple" },
  { NULL }
};

static
void
exposeInputStateConstants() {
  PyObject *val;
  for (int i = 0; InputState::KEY_NAMES[i] != ""; ++i) {
    val = PyInt_FromLong(i);
    PyDict_SetItemString(PyInputStateType.tp_dict,
                         InputState::KEY_NAMES[i].c_str(), val);
    Py_DECREF(val);
  }
  //-- Mouse buttons
  val = PyInt_FromLong(InputState::LeftButton);
  PyDict_SetItemString(PyInputStateType.tp_dict, "LEFT_BUTTON", val);
  Py_DECREF(val);
  val = PyInt_FromLong(InputState::RightButton);
  PyDict_SetItemString(PyInputStateType.tp_dict, "RIGHT_BUTTON", val);
  Py_DECREF(val);
  val = PyInt_FromLong(InputState::MiddleButton);
  PyDict_SetItemString(PyInputStateType.tp_dict, "MIDDLE_BUTTON", val);
  Py_DECREF(val);
}

// Input type and methods -------------------------------------------------------
static PyTypeObject PyInputType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Input",
  sizeof(PyComponent),
};

static
int Input_init(PyObject *self, PyObject *args, PyObject *kwds) {
  return Component_init(self, new Input());
}

static
PyObject *Input_getState(PyObject *self, void *) {
  Input *input = (Input *) ((PyComponent *) self)->component;
  PyInputState *state =
    (PyInputState *) PyInputStateType.tp_alloc(&PyInputStateType, 0);
  state->state = input->getInputState();
  Py_INCREF(state);
  return (PyObject *) state;
}

static PyGetSetDef Input_getset[] = {
  { (char *) "state", Input_getState, NULL, (char *) "The input state", NULL },
  { NULL, NULL }
};

// Camera type and methods -----------------------------------------------------
static PyTypeObject PyCameraType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Camera",
  sizeof(PyComponent),
};

static
int Camera_init(PyObject *self, PyObject *args, PyObject *kwds) {
  float offsetX, offsetY;
  unsigned int width, height;
  if (!PyArg_ParseTuple(args, "ffII", &offsetX, &offsetY, &width, &height)) {
    return -1;
  }
  return Component_init(self, new Camera(offsetX, offsetY, width, height));
}

static
PyObject *Camera_getOffsetX(PyObject *self, void *) {
  Camera *c = (Camera *) ((PyComponent *) self)->component;
  return PyFloat_FromDouble(c->getOffsetX());
}

static
int Camera_setOffsetX(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Camera.offsetX must be a number");
    return -1;
  }
  Camera *c = (Camera *) ((PyComponent *) self)->component;
  c->setOffsetX((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Camera_getOffsetY(PyObject *self, void *) {
  Camera *c = (Camera *) ((PyComponent *) self)->component;
  return PyFloat_FromDouble(c->getOffsetY());
}

static
int Camera_setOffsetY(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Camera.offsetY must be a number");
    return -1;
  }
  Camera *c = (Camera *) ((PyComponent *) self)->component;
  c->setOffsetY((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Camera_getWidth(PyObject *self, void *) {
  Camera *c = (Camera *) ((PyComponent *) self)->component;
  return PyInt_FromLong(c->getWidth());
}

static
int Camera_setWidth(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Camera.width must be a number");
    return -1;
  }
  Camera *c = (Camera *) ((PyComponent *) self)->component;
  c->setWidth((unsigned int) PyInt_AsLong(val));
  return 0;
}

static
PyObject *Camera_getHeight(PyObject *self, void *) {
  Camera *c = (Camera *) ((PyComponent *) self)->component;
  return PyInt_FromLong(c->getHeight());
}

static
int Camera_setHeight(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Camera.height must be a number");
    return -1;
  }
  Camera *c = (Camera *) ((PyComponent *) self)->component;
  c->setHeight((unsigned int) PyInt_AsLong(val));
  return 0;
}

static PyGetSetDef Camera_getset[] = {
  { (char *) "offsetX", Camera_getOffsetX, Camera_setOffsetX,
    (char *) "The x offset", NULL },
  { (char *) "offsetY", Camera_getOffsetY, Camera_setOffsetY,
    (char *) "The y offset", NULL },
  { (char *) "width", Camera_getWidth, Camera_setWidth,
    (char *) "The width of the view", NULL },
  { (char *) "height", Camera_getHeight, Camera_setHeight,
    (char *) "The height of the view", NULL },
  { NULL, NULL }
};

// Collider type and methods ----------------------------------------------------
static PyTypeObject PyColliderType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Collider",
  sizeof(PyComponent),
};

static
int Collider_init(PyObject *self, PyObject *args, PyObject *kwds) {
  PyObject *solidObj;
  PyObject *size;
  if (!PyArg_ParseTuple(args, "Of", &solidObj, &size)) {
    return -1;
  }

  bool solid = (PyObject_IsTrue(solidObj) != 0);
  return Component_init(self, new Collider(solid,
                                           (float) PyFloat_AsDouble(size)));
}

static
PyObject *Collider_getSolid(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  if (a->isSolid()) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static
int Collider_setSolid(PyObject *self, PyObject *val, void *) {
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  a->setSolid(PyObject_IsTrue(val) != 0);
  return 0;
}

static
int Collider_setSize(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Collider.size must be a number");
    return -1;
  }
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  a->setSize((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Collider_getLeft(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  return PyFloat_FromDouble(a->getLeft());
}

static
int Collider_setLeft(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Collider.left must be a number");
    return -1;
  }
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  a->setLeft((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Collider_getTop(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  return PyFloat_FromDouble(a->getTop());
}

static
int Collider_setTop(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Collider.top must be a number");
    return -1;
  }
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  a->setTop((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Collider_getRight(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  return PyFloat_FromDouble(a->getRight());
}

static
int Collider_setRight(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Collider.right must be a number");
    return -1;
  }
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  a->setRight((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Collider_getBottom(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  return PyFloat_FromDouble(a->getBottom());
}

static
int Collider_setBottom(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Collider.bottom must be a number");
    return -1;
  }
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  a->setBottom((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Collider_getCollisions(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyComponent *) self)->component;
  const TEntityIdList &entityIds = a->getCollisions();
  int size = entityIds.size();
  PyObject *ret = PyList_New(size);
  for (int i = 0; i < size; ++i) {
    Entity::Id id = entityIds[i];
    PyList_SetItem(ret, i, PyInt_FromLong(id));
  }
  return ret;
}

static PyGetSetDef Collider_getset[] = {
  { (char *) "solid", Collider_getSolid, Collider_setSolid,
    (char *) "Flags indicating if the collider is solid (cannot overlap with "
    "another solid collider)", NULL },
  { (char *) "size", NULL, Collider_setSize,
    (char *) "Size of the collision box (write-only)", NULL },
  { (char *) "left", Collider_getLeft, Collider_setLeft,
    (char *) "Distance between transform and left side of collision box", NULL },
  { (char *) "top", Collider_getTop, Collider_setTop,
    (char *) "Distance between transform and top side of collision box", NULL },
  { (char *) "right", Collider_getRight, Collider_setRight,
    (char *) "Distance between transform and right side of collision box",
    NULL },
  { (char *) "bottom", Collider_getBottom, Collider_setBottom,
    (char *) "Distance between transform and bottom side of collision box",
    NULL },
  { (char *) "collisions", Collider_getCollisions, NULL,
    (char *) "IDs of currently colliding entities", NULL },
  { NULL, NULL }
};

// Actionable type and methods ----------------------------------------------------
static PyTypeObject PyActionableType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Actionable",
  sizeof(PyComponent),
};

static
int Actionable_init(PyObject *self, PyObject *args, PyObject *kwds) {
  return Component_init(self, new Actionable());
}

static
PyObject *Actionable_getAction(PyObject *self, void *) {
  Actionable *a = (Actionable *) ((PyComponent *) self)->component;
  return PyString_FromString(a->getAction().c_str());
}

static
int Actionable_setAction(PyObject *self, PyObject *val, void *) {
  Actionable *a = (Actionable *) ((PyComponent *) self)->component;
  a->setAction(PyString_AsString(val));
  return 0;
}

static PyGetSetDef Actionable_getset[] = {
  { (char *) "action", Actionable_getAction, Actionable_setAction,
    (char *) "Triggered action", NULL },
  { NULL, NULL }
};

static
PyObject *Actionable_clearAction(PyObject *self) {
  Actionable *a = (Actionable *) ((PyComponent *) self)->component;
  a->clearAction();
  Py_RETURN_NONE;
}

static PyMethodDef Actionable_methods[] = {
  { "clearAction", (PyCFunction) Actionable_clearAction, METH_NOARGS,
    "Clear current action" },
  { NULL }
};

// Real initialization ----------------------------------------------------------
static map<Component::Type, PyTypeObject *> PythonComponentTypes;

static void
registerComponentType(PyObject *module,
                      Component::Type type,
                      PyTypeObject *pyType,
                      const char *doc,
                      PyMethodDef *methods,
                      initproc init,
                      PyGetSetDef *getset) {
  pyType->tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  pyType->tp_doc = doc;
  pyType->tp_methods = methods;
  pyType->tp_base = &PyComponentType;
  pyType->tp_init = init;
  pyType->tp_getset = getset;

  if (PyType_Ready(pyType) < 0) {
    LOG2 << "Cannot create " << ComponentName[type] << " type\n";
    return;
  }
  Py_INCREF(pyType);
  PyModule_AddObject(module, ComponentName[type], (PyObject *) pyType);
  PyObject *typeVal = PyInt_FromLong(type);
  PyDict_SetItemString(pyType->tp_dict, "TYPE", typeVal);
  Py_DECREF(typeVal);
  
  PythonComponentTypes[type] = pyType;
}

void
initComponents(PyObject *module) {
  registerComponentType(module, Transform::TYPE, &PyTransformType,
                        "Type of Transform components",
                        Transform_methods, Transform_init, Transform_getset);

  registerComponentType(module, Resources::TYPE, &PyResourcesType,
                        "Type of Resources components",
                        Resources_methods, Resources_init, NULL);
  
  registerComponentType(module, Mobile::TYPE, &PyMobileType,
                        "Type of Mobild components",
                        NULL, Mobile_init, Mobile_getset);

  registerComponentType(module, BVisual::TYPE, &PyVisualType,
                        "Type of Visual components",
                        Visual_methods, Visual_init, Visual_getset);

  registerComponentType(module, Animated::TYPE, &PyAnimatedType,
                        "Type of Animated components",
                        NULL, Animated_init, Animated_getset);

  registerComponentType(module, Audio::TYPE, &PyAudioType,
                        "Type of Audio components",
                        Audio_methods, Audio_init, Audio_getset);

  registerComponentType(module, Input::TYPE, &PyInputType,
                        "Type of Input component",
                        NULL, Input_init, Input_getset);
  
  registerComponentType(module, Camera::TYPE, &PyCameraType,
                        "Type of Camera components",
                        NULL, Camera_init, Camera_getset);
  
  registerComponentType(module, Collider::TYPE, &PyColliderType,
                        "Type of Collider components",
                        NULL, Collider_init, Collider_getset);

  registerComponentType(module, Actionable::TYPE, &PyActionableType,
                        "Type of Actionable components",
                        Actionable_methods, Actionable_init, Actionable_getset);
  
  // InputState
  PyInputStateType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyInputStateType.tp_doc = "Type of the input state";
  PyInputStateType.tp_methods = InputState_methods;
  if (PyType_Ready(&PyInputStateType) < 0) {
    LOG2 << "Cannot create InputState type\n";
    return;
  }
  Py_INCREF(&PyInputStateType);
  PyModule_AddObject(module, "InputState", (PyObject *) &PyInputStateType);
  exposeInputStateConstants();
  
}

PyObject *
wrapRealComponent(Component *c) {
  PyTypeObject *type = PythonComponentTypes[c->getType()];
  if (type == NULL) {
    return NULL;
  }
  PyComponent *pyc = (PyComponent *) type->tp_alloc(type, 0);
  pyc->component = c;
  return (PyObject *) pyc;
}
