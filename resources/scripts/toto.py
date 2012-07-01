import random
import cp

def init(self, manager):
    """This method is called on an entity only once, before any call to update"""
    self.times = -1

def update(self, manager):
    """This method is called for each engine update"""
    self.x = 666
    self.times += 1
    if self.times == 0:
        print("TOTO: My id is %d and I have %d components: %s" %
              (self.id(),
               len(self.getComponents()),
               ", ".join(c.typeName() for c in self.getComponents())))
        entities = manager.getEntities(cp.Transform.TYPE) #, cp.Visual)
        print("My tags are [%s]" % ", ".join(self.getTags()))
        print("There are %d Transform entities" % len(entities))
        print("x=%s" % self.getDict()["x"])
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
    if self.times > 60 and self.times < 180:
        t = self.getComponent(cp.Transform.TYPE)
        t.moveBy(5, 5)
        c = self.getComponent(cp.Camera.TYPE)
        c.offsetX = random.randint(-20, 20)
        c.offsetY = random.randint(-20, 20)
    if self.times == 180:
        t = self.getComponent(cp.Transform.TYPE)
        t.moveTo(0, 0)
