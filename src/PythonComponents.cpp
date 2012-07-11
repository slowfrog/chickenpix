#include <Python.h>
#include "log.h"
#include "PythonComponents.h"
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


//
static PyObject *NO_ARGS = PyTuple_New(0);
static PyObject *NO_KWDS = PyDict_New();

// Transform wrapper
typedef PyComponent PyTransform;
typedef PyComponent PyMobile;
typedef PyComponent PyAnimated;
typedef PyComponent PyVisual;
typedef PyComponent PyAudio;
typedef PyComponent PyInput;
typedef PyComponent PyCamera;
typedef PyComponent PyCollider;

// Transform type and methods ---------------------------------------------------
static PyTypeObject PyTransformType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Transform",
  sizeof(PyTransform),
};

static
int Transform_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  float x, y;
  if (!PyArg_ParseTuple(args, "ff", &x, &y)) {
    return -1;
  }
  self->component = new Transform(x, y);
  return 0;
}

static
PyObject *Transform_getx(PyObject *self, void *) {
  Transform *t = (Transform *) ((PyTransform *) self)->component;
  return PyFloat_FromDouble(t->getX());
}

static
int Transform_setx(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Transform.x must be a number");
    return -1;
  }
  Transform *t = (Transform *) ((PyTransform *) self)->component;
  t->setX((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Transform_gety(PyObject *self, void *) {
  Transform *t = (Transform *) ((PyTransform *) self)->component;
  return PyFloat_FromDouble(t->getY());
}

static
int Transform_sety(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Transform.y must be a number");
    return -1;
  }
  Transform *t = (Transform *) ((PyTransform *) self)->component;
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
PyObject *Transform_moveTo(PyTransform *self, PyObject *args) {
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
PyObject *Transform_moveBy(PyTransform *self, PyObject *args) {
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

// Mobile type and methods -----------------------------------------------------
static PyTypeObject PyMobileType = {
  PyObject_HEAD_INIT(NULL)
  0,
  "cp.Mobile",
  sizeof(PyMobile),
};

static
int Mobile_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  float speedX, speedY;
  if (!PyArg_ParseTuple(args, "ff", &speedX, &speedY)) {
    return -1;
  }
  self->component = new Mobile(speedX, speedY);
  return 0;
}

static
PyObject *Mobile_getSpeedX(PyObject *self, void *) {
  Mobile *m = (Mobile *) ((PyMobile *) self)->component;
  return PyFloat_FromDouble(m->getSpeedX());
}

static
int Mobile_setSpeedX(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speedX must be a number");
    return -1;
  }
  Mobile *m = (Mobile *) ((PyMobile *) self)->component;
  m->setSpeedX((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Mobile_getSpeedY(PyObject *self, void *) {
  Mobile *m = (Mobile *) ((PyMobile *) self)->component;
  return PyFloat_FromDouble(m->getSpeedY());
}

static
int Mobile_setSpeedY(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Mobile.speedY must be a number");
    return -1;
  }
  Mobile *m = (Mobile *) ((PyMobile *) self)->component;
  m->setSpeedY((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Mobile_getSpeed(PyObject *self, void *) {
  Mobile *m = (Mobile *) ((PyMobile *) self)->component;
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
  
  Mobile *m = (Mobile *) ((PyMobile *) self)->component;
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
  sizeof(PyVisual),
};

static
int Visual_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  // Should not be called...
  
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  //self->component = new Mobile(speedX, speedY);
  return 0;
}


static
PyObject *Visual_getText(PyObject *self, void *) {
  BVisual *visual = (BVisual *) ((PyVisual *) self)->component;
  if (!visual->isText()) {
    PyErr_SetString(PyExc_TypeError, "Visual is not a text");
    return NULL;
  }
  VisualText *vtext = (VisualText *) visual;
  return PyString_FromString(vtext->getText().c_str());
}

static
int Visual_setText(PyObject *self, PyObject *val, void *) {
  BVisual *visual = (BVisual *) ((PyVisual *) self)->component;
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
  BVisual *visual = (BVisual *) ((PyVisual *) self)->component;
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
  BVisual *visual = (BVisual *) ((PyVisual *) self)->component;
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
Visual_isText(PyVisual *self) {
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
  sizeof(PyAnimated),
};

static
int Animated_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  PyObject *name;
  if (!PyArg_ParseTuple(args, "S", &name)) {
    return -1;
  }
  self->component = new Animated(PyString_AsString(name));
  return 0;
}

static
PyObject *Animated_getAnimation(PyObject *self, void *) {
  Animated *a = (Animated *) ((PyAnimated *) self)->component;
  return PyString_FromString(a->getAnimation().c_str());
}

static
int Animated_setAnimation(PyObject *self, PyObject *val, void *) {
  if (!PyString_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Animated.animation must be a string");
    return -1;
  }
  Animated *a = (Animated *) ((PyAnimated *) self)->component;
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
  sizeof(PyAudio),
};

static
int Audio_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
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
  self->component = new Audio(PyString_AsString(name), looping);
  return 0;
}

static
PyObject *Audio_getName(PyObject *self, void *) {
  Audio *a = (Audio *) ((PyAudio *) self)->component;
  return PyString_FromString(a->getName().c_str());
}

static
int Audio_setName(PyObject *self, PyObject *val, void *) {
  if (!PyString_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Audio.name must be a string");
    return -1;
  }
  Audio *a = (Audio *) ((PyAudio *) self)->component;
  a->setName(PyString_AsString(val));
  return 0;
}

static
PyObject *Audio_getLoop(PyObject *self, void *) {
  Audio *a = (Audio *) ((PyAudio *) self)->component;
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
  Audio *a = (Audio *) ((PyAudio *) self)->component;
  a->setLooping(PyObject_IsTrue(val) != 0);
  return 0;
}

static
PyObject *Audio_getPlaying(PyObject *self, void *) {
  Audio *a = (Audio *) ((PyAudio *) self)->component;
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
PyObject *Audio_stop(PyAudio *audio) {
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
  sizeof(PyInput),
};

static
int Input_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  self->component = new Input();
  return 0;
}

static
PyObject *Input_getState(PyObject *self, void *) {
  Input *input = (Input *) ((PyInput *) self)->component;
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
  sizeof(PyCamera),
};

static
int Camera_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  float offsetX, offsetY;
  unsigned int width, height;
  if (!PyArg_ParseTuple(args, "ffII", &offsetX, &offsetY, &width, &height)) {
    return -1;
  }
  self->component = new Camera(offsetX, offsetY, width, height);
  return 0;
}

static
PyObject *Camera_getOffsetX(PyObject *self, void *) {
  Camera *c = (Camera *) ((PyCamera *) self)->component;
  return PyFloat_FromDouble(c->getOffsetX());
}

static
int Camera_setOffsetX(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Camera.offsetX must be a number");
    return -1;
  }
  Camera *c = (Camera *) ((PyCamera *) self)->component;
  c->setOffsetX((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Camera_getOffsetY(PyObject *self, void *) {
  Camera *c = (Camera *) ((PyCamera *) self)->component;
  return PyFloat_FromDouble(c->getOffsetY());
}

static
int Camera_setOffsetY(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Camera.offsetY must be a number");
    return -1;
  }
  Camera *c = (Camera *) ((PyCamera *) self)->component;
  c->setOffsetY((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Camera_getWidth(PyObject *self, void *) {
  Camera *c = (Camera *) ((PyCamera *) self)->component;
  return PyInt_FromLong(c->getWidth());
}

static
int Camera_setWidth(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Camera.width must be a number");
    return -1;
  }
  Camera *c = (Camera *) ((PyCamera *) self)->component;
  c->setWidth((unsigned int) PyInt_AsLong(val));
  return 0;
}

static
PyObject *Camera_getHeight(PyObject *self, void *) {
  Camera *c = (Camera *) ((PyCamera *) self)->component;
  return PyInt_FromLong(c->getHeight());
}

static
int Camera_setHeight(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Camera.height must be a number");
    return -1;
  }
  Camera *c = (Camera *) ((PyCamera *) self)->component;
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
  sizeof(PyCollider),
};

static
int Collider_init(PyTransform *self, PyObject *args, PyObject *kwds) {
  if (PyComponentType.tp_init((PyObject *) self, NO_ARGS, NO_KWDS) < 0) {
    return -1;
  }
  if (PyErr_Occurred()) {
    PyErr_Clear();
  }
  
  PyObject *solidObj;
  PyObject *size;
  if (!PyArg_ParseTuple(args, "Of", &solidObj, &size)) {
    return -1;
  }

  bool solid = (PyObject_IsTrue(solidObj) != 0);
  self->component = new Collider(solid, (float) PyFloat_AsDouble(size));
  return 0;
}

static
PyObject *Collider_getSolid(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  if (a->isSolid()) {
    Py_RETURN_TRUE;
  } else {
    Py_RETURN_FALSE;
  }
}

static
int Collider_setSolid(PyObject *self, PyObject *val, void *) {
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  a->setSolid(PyObject_IsTrue(val) != 0);
  return 0;
}

static
int Collider_setSize(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Collider.size must be a number");
    return -1;
  }
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  a->setSize((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Collider_getLeft(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  return PyFloat_FromDouble(a->getLeft());
}

static
int Collider_setLeft(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Collider.left must be a number");
    return -1;
  }
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  a->setLeft((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Collider_getTop(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  return PyFloat_FromDouble(a->getTop());
}

static
int Collider_setTop(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Collider.top must be a number");
    return -1;
  }
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  a->setTop((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Collider_getRight(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  return PyFloat_FromDouble(a->getRight());
}

static
int Collider_setRight(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Collider.right must be a number");
    return -1;
  }
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  a->setRight((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Collider_getBottom(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  return PyFloat_FromDouble(a->getBottom());
}

static
int Collider_setBottom(PyObject *self, PyObject *val, void *) {
  if (!PyNumber_Check(val)) {
    PyErr_SetString(PyExc_TypeError, "Collider.bottom must be a number");
    return -1;
  }
  Collider *a = (Collider *) ((PyCollider *) self)->component;
  a->setBottom((float) PyFloat_AsDouble(val));
  return 0;
}

static
PyObject *Collider_getCollisions(PyObject *self, void *) {
  Collider *a = (Collider *) ((PyCollider *) self)->component;
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

// Real initialization ----------------------------------------------------------
void
initComponents(PyObject *module) {
  PyObject *type;
  
  // Transform
  PyTransformType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyTransformType.tp_doc = "Type of Transform components";
  PyTransformType.tp_methods = Transform_methods;
  PyTransformType.tp_base = &PyComponentType;
  PyTransformType.tp_init = (initproc) Transform_init;
  PyTransformType.tp_getset = Transform_getset;
  if (PyType_Ready(&PyTransformType) < 0) {
    LOG2 << "Cannot create Transform type\n";
    return;
  }
  Py_INCREF(&PyTransformType);
  PyModule_AddObject(module, "Transform", (PyObject *) &PyTransformType);
  type = PyInt_FromLong(Transform::TYPE);
  PyDict_SetItemString(PyTransformType.tp_dict, "TYPE", type);
  Py_DECREF(type);

  // Mobile
  PyMobileType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyMobileType.tp_doc = "Type of Mobile components";
  //PyMobileType.tp_methods = XXX
  PyMobileType.tp_base = &PyComponentType;
  PyMobileType.tp_init = (initproc) Mobile_init;
  PyMobileType.tp_getset = Mobile_getset;
  if (PyType_Ready(&PyMobileType) < 0) {
    LOG2 << "Cannot create Mobile type\n";
    return;
  }
  Py_INCREF(&PyMobileType);
  PyModule_AddObject(module, "Mobile", (PyObject *) &PyMobileType);
  type = PyInt_FromLong(Mobile::TYPE);
  PyDict_SetItemString(PyMobileType.tp_dict, "TYPE", type);
  Py_DECREF(type);

  // Visual
  PyVisualType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyVisualType.tp_doc = "Type of Visual components";
  //PyVisualType.tp_methods = XXX
  PyVisualType.tp_base = &PyComponentType;
  PyVisualType.tp_init = (initproc) Visual_init;
  PyVisualType.tp_getset = Visual_getset;
  PyVisualType.tp_methods = Visual_methods;
  if (PyType_Ready(&PyVisualType) < 0) {
    LOG2 << "Cannot create Visual type\n";
    return;
  }
  Py_INCREF(&PyVisualType);
  PyModule_AddObject(module, "Visual", (PyObject *) &PyVisualType);
  type = PyInt_FromLong(BVisual::TYPE);
  PyDict_SetItemString(PyVisualType.tp_dict, "TYPE", type);
  Py_DECREF(type);

  // Animated
  PyAnimatedType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyAnimatedType.tp_doc = "Type of Animated components";
  //PyAnimatedType.tp_methods = XXX
  PyAnimatedType.tp_base = &PyComponentType;
  PyAnimatedType.tp_init = (initproc) Animated_init;
  PyAnimatedType.tp_getset = Animated_getset;
  if (PyType_Ready(&PyAnimatedType) < 0) {
    LOG2 << "Cannot create Animated type\n";
    return;
  }
  Py_INCREF(&PyAnimatedType);
  PyModule_AddObject(module, "Animated", (PyObject *) &PyAnimatedType);
  type = PyInt_FromLong(Animated::TYPE);
  PyDict_SetItemString(PyAnimatedType.tp_dict, "TYPE", type);
  Py_DECREF(type);

  // Audio
  PyAudioType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyAudioType.tp_doc = "Type of Audio components";
  PyAudioType.tp_methods = Audio_methods;
  PyAudioType.tp_base = &PyComponentType;
  PyAudioType.tp_init = (initproc) Audio_init;
  PyAudioType.tp_getset = Audio_getset;
  if (PyType_Ready(&PyAudioType) < 0) {
    LOG2 << "Cannot create Audio type\n";
    return;
  }
  Py_INCREF(&PyAudioType);
  PyModule_AddObject(module, "Audio", (PyObject *) &PyAudioType);
  type = PyInt_FromLong(Audio::TYPE);
  PyDict_SetItemString(PyAudioType.tp_dict, "TYPE", type);
  Py_DECREF(type);

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
  Py_DECREF(type);
  
  // Input
  PyInputType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyInputType.tp_doc = "Type of Input components";
  //PyInputType.tp_methods = XXX
  PyInputType.tp_base = &PyComponentType;
  PyInputType.tp_init = (initproc) Input_init;
  PyInputType.tp_getset = Input_getset;
  if (PyType_Ready(&PyInputType) < 0) {
    LOG2 << "Cannot create Input type\n";
    return;
  }
  Py_INCREF(&PyInputType);
  PyModule_AddObject(module, "Input", (PyObject *) &PyInputType);
  type = PyInt_FromLong(Input::TYPE);
  PyDict_SetItemString(PyInputType.tp_dict, "TYPE", type);
  Py_DECREF(type);
  
  // Camera
  PyCameraType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyCameraType.tp_doc = "Type of Camera components";
  //PyCameraType.tp_methods = XXX
  PyCameraType.tp_base = &PyComponentType;
  PyCameraType.tp_init = (initproc) Camera_init;
  PyCameraType.tp_getset = Camera_getset;
  if (PyType_Ready(&PyCameraType) < 0) {
    LOG2 << "Cannot create Camera type\n";
    return;
  }
  Py_INCREF(&PyCameraType);
  PyModule_AddObject(module, "Camera", (PyObject *) &PyCameraType);
  type = PyInt_FromLong(Camera::TYPE);
  PyDict_SetItemString(PyCameraType.tp_dict, "TYPE", type);
  Py_DECREF(type);
  
  // Collider
  PyColliderType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  PyColliderType.tp_doc = "Type of Collider components";
  //PyColliderType.tp_methods = XXX
  PyColliderType.tp_base = &PyComponentType;
  PyColliderType.tp_init = (initproc) Collider_init;
  PyColliderType.tp_getset = Collider_getset;
  if (PyType_Ready(&PyColliderType) < 0) {
    LOG2 << "Cannot create Collider type\n";
    return;
  }
  Py_INCREF(&PyColliderType);
  PyModule_AddObject(module, "Collider", (PyObject *) &PyColliderType);
  type = PyInt_FromLong(Collider::TYPE);
  PyDict_SetItemString(PyColliderType.tp_dict, "TYPE", type);
  Py_DECREF(type);
}

PyObject *
wrapTransform(Transform *t) {
  PyTransform *pyt = (PyTransform *) PyTransformType.tp_alloc(&PyTransformType, 0);
  pyt->component = t;
  return (PyObject *) pyt;
}

PyObject *
wrapMobile(Mobile *c) {
  PyMobile *pyc = (PyMobile *) PyMobileType.tp_alloc(&PyMobileType, 0);
  pyc->component = c;
  return (PyObject *) pyc;
}

PyObject *
wrapVisual(BVisual *v) {
  PyVisual *pyv = (PyVisual *) PyVisualType.tp_alloc(&PyVisualType, 0);
  pyv->component = v;
  return (PyObject *) pyv;
}

PyObject *
wrapAnimated(Animated *a) {
  PyAnimated *pya = (PyAnimated *) PyAnimatedType.tp_alloc(&PyAnimatedType, 0);
  pya->component = a;
  return (PyObject *) pya;
}

PyObject *
wrapAudio(Audio *a) {
  PyAudio *pya = (PyAudio *) PyAudioType.tp_alloc(&PyAudioType, 0);
  pya->component = a;
  return (PyObject *) pya;
}

PyObject *
wrapInput(Input *i) {
  PyInput *pyi = (PyInput *) PyInputType.tp_alloc(&PyInputType, 0);
  pyi->component = i;
  return (PyObject *) pyi;
}

PyObject *
wrapCamera(Camera *c) {
  PyCamera *pyc = (PyCamera *) PyCameraType.tp_alloc(&PyCameraType, 0);
  pyc->component = c;
  return (PyObject *) pyc;
}

PyObject *
wrapCollider(Collider *c) {
  PyCollider *pyc = (PyCollider *) PyColliderType.tp_alloc(&PyColliderType, 0);
  pyc->component = c;
  return (PyObject *) pyc;
}


PyObject *
wrapRealComponent(Component *c) {
  switch (c->getType()) {
  case Transform::TYPE:
    return wrapTransform((Transform *) c);
  case Mobile::TYPE:
    return wrapMobile((Mobile *) c);
  case BVisual::TYPE:
    return wrapVisual((BVisual *) c);
  case Animated::TYPE:
    return wrapAnimated((Animated *) c);
  case Audio::TYPE:
    return wrapAudio((Audio *) c);
  case Input::TYPE:
    return wrapInput((Input *) c);
  case Camera::TYPE:
    return wrapCamera((Camera *) c);
  case Collider::TYPE:
    return wrapCollider((Collider *) c);
  default:
    return NULL;
  }
}
