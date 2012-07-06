import random
import time
import cp

def init(self, manager):
    """This method is called on an entity only once, before any call to update"""
    self.times = -1
    self.gold = 0
    self.start = time.time()
    print("start=%f" % time.time())

def update(self, manager):
    """This method is called for each engine update"""
    self.times += 1
    input = self.getComponent(cp.Input.TYPE)
    if input is not None:
        if input.state.isButtonDown(cp.InputState.LEFT_BUTTON):
            print("The left button is pressed at %d,%d" %
                  input.state.getMousePosition())
            anim = self.getComponent(cp.Animated.TYPE)
            print("Current anim is %s" % anim.animation)
            anim.animation = "man_still"
        if input.state.isKeyDown(cp.InputState.NUM0):
            print("You are pressing 0")
            cam = self.getComponent(cp.Camera.TYPE)
            print("Current camera at %f,%f size %dx%d" %
                  (cam.offsetX, cam.offsetY, cam.width, cam.height))
            cam.width = 100
            cam.height = 100
        if input.state.isKeyDown(cp.InputState.NUM1):
            print("You are pressing 1")
            cam = self.getComponent(cp.Camera.TYPE)
            print("Current camera at %f,%f size %dx%d" %
                  (cam.offsetX, cam.offsetY, cam.width, cam.height))
            cam.width = 600
            cam.height = 600
        if input.state.isButtonDown(cp.InputState.RIGHT_BUTTON):
            print("The right button is pressed at %d,%d" %
                  input.state.getMousePosition())
        if input.state.isButtonDown(cp.InputState.MIDDLE_BUTTON):
            print("The middle button is pressed at %d,%d" %
                  input.state.getMousePosition())

    collider = self.getComponent(cp.Collider.TYPE)
    for coll in collider.collisions:
        collentity = manager.getById(coll)
        if "GOLD" in collentity.getTags():
            manager.destroyEntity(collentity)
            self.gold += 10
            self.addComponent(cp.Audio("coin", False))
            
    if self.times == 0:
        print("TOTO: My id is %d and I have %d components: %s" %
              (self.id(),
               len(self.getComponents()),
               ", ".join(c.typeName() for c in self.getComponents())))
        print("My tags are [%s]" % ", ".join(self.getTags()))
        entities = manager.getEntities(cp.Transform.TYPE) #, cp.Visual)
        print("There are %d Transform entities" % len(entities))
        print("dict=%s" % self.getDict())
        coll = self.getComponent(cp.Collider.TYPE)
        print("My collider box is (%.1f, %.1f, %.1f, %.1f). Am I solid? %s" %
              (coll.left, coll.top, coll.right, coll.bottom, coll.solid))
        
    if self.times < 3:
        labels = manager.getByTag("LABEL")
        print("There are %d entities tagged LABEL" % len(labels))
        manager.tagEntity(self, "LABEL")
        if self.times == 1:
            for ntt in labels:
                manager.untagEntity(ntt, "LABEL")
    if self.times == 3:
        print("Trying to create a Transform component")
        t = cp.Transform(2, 4)
        print("t={%f,%f}" % (t.x, t.y))
        t.x = 3.2
        t.y = -3
        print("t={%f,%f}" % (t.x, t.y))
        m = self.getComponent(cp.Mobile.TYPE)
        print("Current speed: (%f, %f)" % m.speed)
        for entity in manager.getEntities(cp.Audio.TYPE):
            audio = entity.getComponent(cp.Audio.TYPE)
            print("%s is %splaying %sin loop" %
                  (audio.name,
                   "not " if not audio.playing else "",
                   "not " if not audio.loop else ""))
                  
    # if self.times > 60 and self.times < 180:
    #     #t = self.getComponent(cp.Transform.TYPE)
    #     #t.moveBy(5, 5)
    #     m = self.getComponent(cp.Mobile.TYPE)
    #     m.speed = (5, 5)
    #     c = self.getComponent(cp.Camera.TYPE)
    #     c.offsetX = random.randint(-20, 20)
    #     c.offsetY = random.randint(-20, 20)
    # if self.times == 180:
    #     t = self.getComponent(cp.Transform.TYPE)
    #     t.moveTo(0, 0)
    #     c = self.getComponent(cp.Camera.TYPE)
    #     c.offsetX = 0
    #     c.offsetY = 0
    if self.times == 240:
        #self.removeComponent(cp.Transform.TYPE)
        #self.addComponent(cp.Transform(100, 100))
        diffclock = time.time() - self.start
        print("240 frames in %f sec: %f FPS" % (diffclock, 240 / diffclock))

    audio = self.getComponent(cp.Audio.TYPE)
