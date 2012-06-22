import cp

once = False

# Nothing
def run(self, manager):
    global once
    if not once:
        entities = manager.getEntities()
        print("TOTO: My id is %d and I have %d components: %s" %
              (self.id(),
               len(self.getComponents()),
               ", ".join(c.typeName() for c in self.getComponents())))
        once = True

    return "1"
    
