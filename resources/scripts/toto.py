import random
import time
import cp

def init(self, manager):
    """This method is called on an entity only once, before any call to update"""
    self.times = -1
    self.start = time.time()
    print("start=%f" % time.time())

def update(self, manager):
    """This method is called for each engine update"""
    self.times += 1
    input = self.getComponent(cp.Input.TYPE)
    if input is not None:
        if input.state.isKeyDown(cp.InputState.DOWN):
            print("The down arrow is pressed")
        if input.state.isKeyDown(cp.InputState.UP):
            print("The up arrow is pressed")
        if input.state.isKeyDown(cp.InputState.LEFT):
            print("The left arrow is pressed")
        if input.state.isKeyDown(cp.InputState.RIGHT):
            print("The right arrow is pressed")
        if input.state.isButtonDown(cp.InputState.LEFT_BUTTON):
            print("The left button is pressed at %d,%d" % input.state.getMousePosition())
        if input.state.isButtonDown(cp.InputState.RIGHT_BUTTON):
            print("The right button is pressed at %d,%d" % input.state.getMousePosition())
        if input.state.isButtonDown(cp.InputState.MIDDLE_BUTTON):
            print("The middle button is pressed at %d,%d" % input.state.getMousePosition())
    if self.times == 0:
        print("TOTO: My id is %d and I have %d components: %s" %
              (self.id(),
               len(self.getComponents()),
               ", ".join(c.typeName() for c in self.getComponents())))
        entities = manager.getEntities(cp.Transform.TYPE) #, cp.Visual)
        print("My tags are [%s]" % ", ".join(self.getTags()))
        print("There are %d Transform entities" % len(entities))
        print("dict=%s" % self.getDict())
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
    if self.times > 60 and self.times < 180:
        #t = self.getComponent(cp.Transform.TYPE)
        #t.moveBy(5, 5)
        m = self.getComponent(cp.Mobile.TYPE)
        m.speed = (5, 5)
        c = self.getComponent(cp.Camera.TYPE)
        c.offsetX = random.randint(-20, 20)
        c.offsetY = random.randint(-20, 20)
    if self.times == 180:
        t = self.getComponent(cp.Transform.TYPE)
        t.moveTo(0, 0)
    if self.times == 240:
        self.removeComponent(cp.Transform.TYPE)
        self.addComponent(cp.Transform(100, 100))
        diffclock = time.time() - self.start
        print("240 frames in %f sec: %f FPS" % (diffclock, 240 / diffclock))
