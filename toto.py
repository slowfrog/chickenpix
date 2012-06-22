import cp

# Nothing
def run(self, manager):
    entities = manager.getEntities()
    print("TOTO: My id is %d and I have %d components: %s" %
          (self.id(),
           len(self.getComponents()),
           ", ".join(c.typeName() for c in self.getComponents())))
    return "5"
