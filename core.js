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
Animated.create = function(name, frames, index, pingpong) {
  var ret = new Animated();
  ret.index = index || 0;
  ret.name = name;
  ret.frames = frames;
  ret.pingpong = pingpong || false;
  ret.dir = 1;
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

// The Resource component stores loaded resources
//================================================
var Resource = function() {};
Resource.prototype = new Component();
Resource.create = function() {
  var ret = new Resource();
  ret.resources = {};
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
  // scanning the whole array is not great
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

// Returns all entities containing all the requested types of components
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

// Returns the first entity containing all the requested types of components
EntityManager.prototype.getEntity = function(compType) {
  var entity;
  var i;
  var compTypes = (compType instanceof Array) ? compType : [ compType ];
  for (i = 1; i < this.entities.length; ++i) {
    entity = this.entities[i];
    if (entity && entity.hasComponent(compTypes)) {
      return entity;
    }
  }
  return null;
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

// Utility function to cut an image into animation frames
Loader.getFrames = function(img, startx, starty, width, height, cols, rows, duration) {
  var ret = [];
  var i, j;
  for (i = 0; i < cols; ++i) {
    for (j = 0; j < rows; ++j) {
      ret.push({img: img, x: startx + i * width, y: starty + j * height,
                w: width, h: height, duration: duration});
    }
  }
  return ret;
};

Loader.createAnimated = function(em, name, index, pingpong) {
  return Animated.create(name,
                         em.getEntity(Resource).getComponent(Resource).resources[name],
                         index,
                         pingpong)
};

Loader.create = function(em) {
  var ret = new Loader();
  ret._init_(em);



  var i, e, img, res;
  e = em.createEntity();
  res = Resource.create();
  e.addComponent(res);

  img = document.getElementById("bat");
  res.resources["bat_flap"] = Loader.getFrames(img, 0, 64, 32, 32, 3, 1, 100);
  
  img = document.getElementById("man");
  res.resources["man_still"] = Loader.getFrames(img, 0, 128, 64, 64, 1, 1, 10000);
  res.resources["man_walk_up"] = Loader.getFrames(img, 0, 0, 64, 64, 9, 1, 100);
  res.resources["man_walk_left"] = Loader.getFrames(img, 0, 64, 64, 64, 9, 1, 100);
  res.resources["man_walk_down"] = Loader.getFrames(img, 0, 128, 64, 64, 9, 1, 100);
  res.resources["man_walk_right"] = Loader.getFrames(img, 0, 192, 64, 64, 9, 1, 100);

  
  e = em.createEntity();
  e.addComponent(Transform.create(320, 300));
  e.addComponent(Loader.createAnimated(em, "man_still"));
  e.addComponent(Input.create());

  for (i = 0; i < 20; ++i) {
    Loader.createRandomBat(em);
  }

  return ret;
};

Loader.createRandomBat = function(em) {
  var e = em.createEntity();
  e.addComponent(Transform.create(20 + Math.random() * 580, 20 + Math.random() * 340));
  e.addComponent(Mobile.create(Math.random() * 6 - 3, Math.random() * 6 - 3));
  e.addComponent(Loader.createAnimated(em, "bat_flap", Math.floor(Math.random() * 3), true));
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

// Constants for key codes
var Key = {
  ENTER: 13,
  ESCAPE: 27,
  SPACE: 32,
  UP: 38,
  DOWN: 40,
  LEFT: 37,
  RIGHT: 39,
  PAGE_UP: 33,
  PAGE_DOWN: 34,
  NUM_PLUS: 107,
  NUM_MINUS: 109
};

Inputs.prototype.update = function(now) {
  var ents;
  // Escape: exit
  if (this.isKeyDown(Key.ESCAPE)) {
    this.exitRequired = true;
  }
  // Space: stop one entity from moving
  if (this.isKeyJustDown(Key.SPACE)) {
    ents = this.em.getEntities(Mobile);
    if (ents.length > 0) {
      ents[0].removeComponent(Mobile);
    }
  }
  // Numpad plus: create a new bat
  if (this.isKeyJustDown(Key.NUM_PLUS)) {
    Loader.createRandomBat(this.em);
  }
  // Numpad minus: destroy a bat
  if (this.isKeyJustDown(Key.NUM_MINUS)) {
    ents = this.em.getEntities(Mobile);
    if (ents.length > 0) {
      this.em.destroyEntity(ents[0]);
    }
  }

  this.moveHero();
  this.justDown = [];
};

Inputs.prototype.moveHero = function() {
  var ents, ent;
  var dx = 0;
  var dy = 0;
  var i, t, a;
  var anim = "man_still";
  if (this.isKeyDown(Key.UP)) {
    dy -= 1;
    anim = "man_walk_up";
  }
  if (this.isKeyDown(Key.DOWN)) {
    dy += 1;
    anim = "man_walk_down";
  }
  if (this.isKeyDown(Key.LEFT)) {
    dx -= 1;
    anim = "man_walk_left";
  }
  if (this.isKeyDown(Key.RIGHT)) {
    dx += 1;
    anim = "man_walk_right";
  }
  
  ents = this.em.getEntities([Input, Transform]);
  for (i = 0; i < ents.length; ++i) {
    ent = ents[i];
    if ((dx !== 0) || (dy !== 0)) {
      t = ent.getComponent(Transform);
      t.x += dx;
      t.y += dy;
    }
    
    a = ent.getComponent(Animated);
    if (a && a.name !== anim) {
      ent.removeComponent(Animated);
      ent.addComponent(Loader.createAnimated(this.em, anim));
    }
  }
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
      
      a.index += a.dir;
      if (a.index >= a.frames.length) {
        if (a.pingpong) {
          a.dir = -1;
          a.index = Math.max(0, a.frames.length - 2);
        } else {
          a.index = 0;
        }
      } else if (a.index < 0) {
        if (a.pingpong) {
          a.dir = 1;
          a.index = Math.min(1, a.frames.length - 1);
        } else {
          a.index = a.frames.length - 1;
        }
      }
      
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
