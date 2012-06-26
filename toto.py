import cp

times = 0

# Nothing
def run(self, manager):
    global times
    if times == 0:
        print("TOTO: My id is %d and I have %d components: %s" %
              (self.id(),
               len(self.getComponents()),
               ", ".join(c.typeName() for c in self.getComponents())))
        entities = manager.getEntities(cp.Transform, cp.Visual)
        print("My tags are [%s]" % ", ".join(self.getTags()))
        print("There are %d Transform entities" % len(entities))
    if times < 3:
        labels = manager.getByTag("LABEL")
        print("There are %d entities tagged LABEL" % len(labels))
        manager.tagEntity(self, "LABEL")
        if times == 1:
            for ntt in labels:
                manager.untagEntity(ntt, "LABEL")

    times += 1

    return "1"
    
