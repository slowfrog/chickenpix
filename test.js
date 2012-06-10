// Scene size
var WIDTH = 600;
var HEIGHT = 450;

// Camera attributes
var VIEW_ANGLE = 45;
var ASPECT = WIDTH / HEIGHT;
var NEAR = 25;
var FAR = 10000;

var updater = function(texture) {
  return function() {
    texture.needsUpdate = true;
  };
};

  

var Test3JS = function() {
  var that = this;
  this.renderFunc = function() {
    that.render();
  };

  this.container = document.getElementById("container");
  this.renderer = new THREE.WebGLRenderer();
  this.camera = new THREE.PerspectiveCamera(VIEW_ANGLE, ASPECT, NEAR, FAR);
  this.scene = new THREE.Scene();

  this.scene.add(this.camera);
  this.camera.position.z = 270;
  this.camera.position.y = -65;
  this.renderer.setSize(WIDTH, HEIGHT);
  this.renderer.setClearColorHex(0xd0ffff, 1);
  this.container.appendChild(this.renderer.domElement);

  var radius = 50;
  var segments = 16;
  var rings = 16;
  var sphereMaterial = new THREE.MeshLambertMaterial({ color: 0xCC0000 });
  var sphere = new THREE.Mesh(new THREE.SphereGeometry(radius, segments, rings),
                              sphereMaterial);
  //this.scene.add(sphere);
  
  this.texture2 = THREE.ImageUtils.loadTexture("tree.png", THREE.UVMapping);
  this.texture2.magFilter = THREE.NearestFilter;
  var treeMaterial = new THREE.MeshBasicMaterial({ map: this.texture2, transparent: true });
  var treeGeo = new THREE.PlaneGeometry(90, 140);

  for (var i = 0; i < 10; ++i) {
    var tree = new THREE.Mesh(treeGeo, treeMaterial);
    tree.rotation.x = Math.PI / 2;
    tree.position.set(-50 + 300 * Math.random(), -40, -50 * Math.random());
    this.scene.add(tree);
  }

  var house = Test3JS.makeVertical("house.png", 202, 133, true);
  house.position.x = -150;
  house.position.y = -33;
  house.position.z = -100;
  this.scene.add(house);

  this.texture = THREE.ImageUtils.loadTexture("ground.png", THREE.UVMapping);
  var planeMaterial = new THREE.MeshBasicMaterial({ map: this.texture });
  var plane = new THREE.Mesh(new THREE.PlaneGeometry(800, 400),
                             planeMaterial);
  plane.position.y = -100;
  this.scene.add(plane);

  
                             
  
  var pointLight = new THREE.PointLight(0xFFFFFF);
  pointLight.position.x = 10;
  pointLight.position.y = 50;
  pointLight.position.z = 130;
  this.scene.add(pointLight);

  window.requestAnimationFrame(this.renderFunc);

  // Setting up listeners
  this.keyDownListener =
    document.body.addEventListener("keydown", function(ev) { that.onKeyDown(ev); }, true);
  this.keyUpListener =
    document.body.addEventListener("keyup", function(ev) { that.onKeyUp(ev); }, true);
  this.keys = [];
  

  // Add stats box
  this.stats = new Stats();
  this.stats.domElement.style.position = 'absolute';
  this.stats.domElement.style.top = '0px';
  this.stats.domElement.style.left = '0px';
  document.body.appendChild(this.stats.domElement);

  console.log("Ok");
};

Test3JS.makeVertical = function(image, width, height, transparent) {
  var texture = THREE.ImageUtils.loadTexture(image, THREE.UVMapping);
  texture.magFilter = THREE.NearestFilter;
  var material = new THREE.MeshBasicMaterial({ map: texture, transparent: transparent });
  var geom = new THREE.PlaneGeometry(width, height);
  var mesh = new THREE.Mesh(geom, material);
  mesh.rotation.x = Math.PI / 2;
  return mesh;
};

Test3JS.prototype.onKeyDown = function(ev) {
  //console.log("keydown", ev);
  this.keys[ev.keyCode] = true;
  ev.preventDefault();
};

Test3JS.prototype.onKeyUp = function(ev) {
  //console.log("keyup", ev);
  this.keys[ev.keyCode] = false;
};

var UP = 38;
var DOWN = 40;
var LEFT = 37;
var RIGHT = 39;
var PAGE_UP = 33;
var PAGE_DOWN = 34;

Test3JS.prototype.render = function() {
  
  var speed = 2;
  if (this.keys[DOWN]) {
    this.camera.position.z += speed;
  }
  if (this.keys[UP]) {
    this.camera.position.z -= speed;
  }
  if (this.keys[LEFT]) {
    this.camera.position.x -= speed;
  }
  if (this.keys[RIGHT]) {
    this.camera.position.x += speed;
  }
  if (this.keys[PAGE_DOWN]) {
    this.camera.position.y -= speed;
  }
  if (this.keys[PAGE_UP]) {
    this.camera.position.y += speed;
  }
  window.requestAnimationFrame(this.renderFunc);
  this.renderer.render(this.scene, this.camera);
  this.stats.update();
};

Test3JS.init = function() {
  new Test3JS();
};
