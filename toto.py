import cp

def hasMember(self, name):
    return name in self.getDict()

# Nothing
def run(self, manager):
    self.x = 666
    if not hasMember(self, "times"):
        self.times = 0

    if self.times == 0:
        print("TOTO: My id is %d and I have %d components: %s" %
              (self.id(),
               len(self.getComponents()),
               ", ".join(c.typeName() for c in self.getComponents())))
        entities = manager.getEntities(cp.Transform, cp.Visual)
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
    

    self.times += 1
