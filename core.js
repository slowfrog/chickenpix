"use strict";

//========================================================
// An entity, is basically just a container of components
//========================================================
var Entity = function(id) {
  this.id = id;
};

Entity.prototype.addComponent = function(c) {
  if (!this.comp) {
    this.comp = [];
  }
  this.comp.push(c); // Does not even check if it's already there
};

Entity.prototype.removeComponent = function(compType) {
  var i;
  if (this.comp) {
    for (i = 0; i < this.comp.length; ++i) {
      if (this.comp[i] instanceof compType) {
        this.comp.splice(i, 1);
        return;
      }
    }
  }
};

Entity.prototype.getComponent = function(compType) {
  var i;
  if (this.comp) {
    for (i = 0; i < this.comp.length; ++i) {
      if (this.comp[i] instanceof compType) {
        return this.comp[i];
      }
    }
  }
  return null;
};

Entity.prototype.hasComponent = function(compTypes) {
  var j, compType;
  for (j = 0; j < compTypes.length; ++j) {
    compType = compTypes[j]
    if (this.getComponent(compType) == null) {
      return false;
    }
  }
  return true;
};

//============================================================
// A component contains data specific to an individual aspect
//============================================================
var Component = function() {};


// For instance, the Transform component contains spatial coordinates
//====================================================================
var Transform = function() {};
Transform.prototype = new Component();
Transform.create = function(x, y) {
  var ret = new Transform();
  ret.x = x;
  ret.y = y;
  return ret;
};

// Other example, the Mobile component contains velocity information
//===================================================================
var Mobile = function() {};
Mobile.prototype = new Component();
Mobile.create = function(dx, dy) {
  var ret = new Mobile();
  ret.dx = dx;
  ret.dy = dy;
  return ret;
}

// The Visual component contains information to display the entity
//=================================================================
var Visual = function() {};
Visual.prototype = new Component();
Visual.create = function(img, x, y, w, h) {
  var ret = new Visual();
  ret.img = img;
  ret.x = x;
  ret.y = y;
  ret.w = w;
  ret.h = h;
  return ret;
};

// The Animated component contains information about animations...
//=================================================================
var Animated = function() {};
Animated.prototype = new Component();
Animated.create = function(frames, index) {
  var ret = new Animated();
  ret.index = index || 0;
  ret.frames = frames;
  return ret;
};


// The Input component receives user input
//=========================================
var Input = function() {};
Input.prototype = new Component();
Input.create = function() {
  var ret = new Input();
  return ret;
};



//===========================================
// An entity manager keeps track of entities 
//===========================================
var EntityManager = function(name) {
  this.name = name;
  this.entities = [ null ];
};

EntityManager.prototype.createEntity = function() {
  var i;
  for (i = 1; i < this.entities.length; ++i) {
    if (!this.entities[i]) {
      break;
    }
  }
  var entity = new Entity(i);
  this.entities[i] = entity;
  return entity;
};

EntityManager.prototype.destroyEntity = function(entity) {
  this.entities[entity.id] = null;
};

EntityManager.prototype.getEntities = function(compType) {
  var ret = [];
  var entity;
  var i;
  var compTypes = (compType instanceof Array) ? compType : [ compType ];
  for (i = 1; i < this.entities.length; ++i) {
    entity = this.entities[i];
    if (entity && entity.hasComponent(compTypes)) {
      ret.push(entity);
    }
  }
  return ret;
};

//======================================================
// A System contains all the logic for a certain aspect
//======================================================
var System = function() {};
System.prototype._init_ = function(em) {
  this.em = em;
};

System.prototype.destroy = function() {
};

// The Loader system is responsible for loading all 'static' objects for a scene
//===============================================================================
var Loader = function() {};
Loader.prototype = new System();
Loader.create = function(em) {
  var ret = new Loader();
  ret._init_(em);

  var i, e, img;
  
  img = document.getElementById("man");
  e = em.createEntity();
  e.addComponent(Transform.create(320, 300));
  e.addComponent(Visual.create(img, 0, 128, 64, 64));
  e.addComponent(Input.create());

  for (i = 0; i < 20; ++i) {
    Loader.createRandomBat(em);
  }

  return ret;
};

Loader.createRandomBat = function(em) {
  var img = document.getElementById("bat");
  var e = em.createEntity();
  e.addComponent(Transform.create(20 + Math.random() * 580, 20 + Math.random() * 340));
  e.addComponent(Mobile.create(Math.random() * 6 - 3, Math.random() * 6 - 3));
  e.addComponent(Animated.create([{img: img, x: 0, y: 64, w: 32, h: 32, duration: 100},
                                  {img: img, x: 32, y: 64, w: 32, h: 32, duration: 100},
                                  {img: img, x: 64, y: 64, w: 32, h: 32, duration: 100},
                                  {img: img, x: 32, y: 64, w: 32, h: 32, duration: 100}],
                                 Math.floor(Math.random() * 4)));
};


// The Inputs system gathers user input and dispatches it
//========================================================
var Inputs = function() {};
Inputs.prototype = new System();
Inputs.create = function(em) {
  var ret = new Inputs();
  ret._init_(em);
  ret.keydownHandler = function(ev) { ret.handleKeyDown(ev); };
  ret.keyupHandler = function(ev) { ret.handleKeyUp(ev); };
  document.body.addEventListener("keydown", ret.keydownHandler, true);
  document.body.addEventListener("keyup", ret.keyupHandler, true);

  ret.exitRequired = false;
  ret.keys = [];
  ret.justDown = [];
  return ret;
};

Inputs.prototype.handleKeyDown = function(ev) {
  if (!this.isKeyDown(ev.keyCode)) {
    this.keys[ev.keyCode] = true;
    this.justDown.push(ev.keyCode);
  }
  ev.preventDefault();
  ev.stopImmediatePropagation();
};

Inputs.prototype.handleKeyUp = function(ev) {
  this.keys[ev.keyCode] = false;
  // Should add justUp...
};

Inputs.prototype.isKeyDown = function(k) {
  return this.keys.hasOwnProperty(k) && this.keys[k];
};

Inputs.prototype.isKeyJustDown = function(k) {
  var i;
  for (i = 0; i < this.justDown.length; ++i) {
    if (this.justDown[i] === k) {
      return true;
    }
  }
  return false;
};

var ENTER = 13;
var ESCAPE = 27;
var SPACE = 32;
var UP = 38;
var DOWN = 40;
var LEFT = 37;
var RIGHT = 39;
var PAGE_UP = 33;
var PAGE_DOWN = 34;
var NUM_PLUS = 107;
var NUM_MINUS = 109;

Inputs.prototype.update = function(now) {
  var ents;
  // Escape: exit
  if (this.isKeyDown(ESCAPE)) {
    this.exitRequired = true;
  }
  // Space: stop one entity from moving
  if (this.isKeyJustDown(SPACE)) {
    ents = this.em.getEntities(Mobile);
    if (ents.length > 0) {
      ents[0].removeComponent(Mobile);
    }
  }
  // Numpad plus: create a new bat
  if (this.isKeyJustDown(NUM_PLUS)) {
    Loader.createRandomBat(this.em);
  }
  // Numpad minus: destroy a bat
  if (this.isKeyJustDown(NUM_MINUS)) {
    ents = this.em.getEntities(Mobile);
    if (ents.length > 0) {
      this.em.destroyEntity(ents[0]);
    }
  }

  var dx = 0;
  var dy = 0;
  var i, t;
  if (this.isKeyDown(UP)) {
    dy -= 1;
  }
  if (this.isKeyDown(DOWN)) {
    dy += 1;
  }
  if (this.isKeyDown(LEFT)) {
    dx -= 1;
  }
  if (this.isKeyDown(RIGHT)) {
    dx += 1;
  }
  if ((dx !== 0) || (dy !== 0)) {
    ents = this.em.getEntities([Input, Transform]);
    for (i = 0; i < ents.length; ++i) {
      t = ents[i].getComponent(Transform);
      t.x += dx;
      t.y += dy;
    }
  }
  this.justDown = [];
};

Inputs.prototype.destroy = function() {
  document.body.removeEventListener("keyup", this.keyupHandler, true);
  document.body.removeEventListener("keydown", this.keydownHandler, true);
};

// The Physics system moves objects using physics laws... almost
//===============================================================
var Physics = function() {};
Physics.prototype = new System();
Physics.create = function(em) {
  var ret = new Physics();
  ret._init_(em);
  return ret;
};

Physics.prototype.update = function(now) {
  var ents = this.em.getEntities([Transform, Mobile]);
  var ent, i, t, m;
  for (i = 0; i < ents.length; ++i) {
    ent = ents[i];
    t = ent.getComponent(Transform);
    m = ent.getComponent(Mobile);
    t.x += m.dx;
    t.y += m.dy;
    if ((t.x < 20) || (t.x > 600)) {
      m.dx = -m.dx;
    }
    if ((t.y < 20) || (t.y > 360)) {
      m.dy = -m.dy;
    }
  }
};

// The Animator system runs animations
//=====================================
var Animator = function() {};
Animator.prototype = new System();
Animator.create = function(em) {
  var ret = new Animator();
  ret._init_(em);
  return ret;
};

Animator.prototype.update = function(now) {
  var ents = this.em.getEntities([Animated]);
  var ent, i, a, frame;
  for (i = 0; i < ents.length; ++i) {
    ent = ents[i];
    a = ent.getComponent(Animated);
    frame = a.frames[a.index];
    if ((!a.start) || (now > a.start + frame.duration)) {
      a.start = now;
      a.index = (a.index + 1) % a.frames.length;
      ent.removeComponent(Visual);
      ent.addComponent(Visual.create(frame.img, frame.x, frame.y, frame.w, frame.h));
    }
  }
};

// The Render system displays Visuals on the screen
//==================================================
var Render = function() {};
Render.prototype = new System();
Render.create = function(em) {
  var ret = new Render();
  ret._init_(em);
  // Create the HTML canvas to render
  var canvas = document.createElement("canvas");
  canvas.width = 640;
  canvas.height = 400;
  canvas.style.border = "1px solid grey";
  document.body.appendChild(canvas);
  ret.canvas = canvas;
  ret.ctx = canvas.getContext("2d");

  return ret;
};

Render.prototype.update = function(now) {
  var ctx = this.ctx;
  ctx.save();
  ctx.fillStyle = "#333";
  ctx.fillRect(0, 0, 640, 400);

  var ents = this.em.getEntities([Transform, Visual]);
  var ent, i, t, v;
  for (i = 0; i < ents.length; ++i) {
    ent = ents[i];
    t = ent.getComponent(Transform);
    v = ent.getComponent(Visual);
    if (v.x !== undefined) {
      ctx.drawImage(v.img, v.x, v.y, v.w, v.h, t.x, t.y, v.w, v.h);
    } else {
      ctx.drawImage(v.img, t.x, t.y);
    }
  }
  
  ctx.restore();
};

Render.prototype.destroy = function() {
  this.canvas.parentNode.removeChild(this.canvas);
};


//=================
// The game object
//=================
var Game = function() {
};

Game.prototype.init = function() {
  this.em = new EntityManager("main");
  this.loader = Loader.create(this.em);
  this.inputs = Inputs.create(this.em);
  this.physics = Physics.create(this.em);
  this.animator = Animator.create(this.em);
  this.render = Render.create(this.em);
};

Game.prototype.loop = function() {
  this.init();
  this.start = new Date().getTime();
  var that = this;
  this.oneStepBound = function() {
    that.oneStep();
  }
  this.oneStep();
};

Game.prototype.oneStep = function() {
  var now = new Date().getTime();
  // handle input
  this.inputs.update(now);
  this.exitRequired = this.inputs.exitRequired;
  if (this.exitRequired) {
    this.exit();
    return;
  }

  // Requests the display of the next frame
  var raf = (window.requestAnimationFrame ||
             window.webkitRequestAnimationFrame ||
             window.mozRequestAnimationFrame ||
             window.msRequestAnimationFrame ||
             function(callback) {
                window.setTimeout(callback, 1000 / 60);
             });
  
  // apply logic
  raf(this.oneStepBound);
  this.physics.update(now);


  // do output
  this.animator.update(now);
  this.render.update(now);
};

Game.prototype.exit = function() {
  this.render.destroy();
  this.animator.destroy();
  this.physics.destroy();
  this.inputs.destroy();
  this.loader.destroy();
};


Game.run = function() {
  var game = new Game();
  game.loop();
};
