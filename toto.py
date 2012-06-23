import cp

once = False

# Nothing
def run(self, manager):
    global once
    if not once:
        print("TOTO: My id is %d and I have %d components: %s" %
              (self.id(),
               len(self.getComponents()),
               ", ".join(c.typeName() for c in self.getComponents())))
        entities = manager.getEntities(1, 2, 3)
        print("There are %d Transform entities" % len(entities))
        once = True

    return "1"
    
