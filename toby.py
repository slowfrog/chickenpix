import cp

# Nothing
def run(self, manager):
    entities = manager.getEntities()
    print("Got list of %d objects: %s" % (len(entities), ", ".join(str(e.id()) for e in entities)))
    print("My id is %d and I have %d components: %s" %
          (self.id(),
           len(self.getComponents()),
           ", ".join(c.typeName() for c in self.getComponents())))
    return "5"
