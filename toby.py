import cp

# Nothing
def run(self, manager):
    print("My id is %d" % self.id())
    entities = manager.getEntities()
    print("Got list of %d objects: %s" % (len(entities), ", ".join(str(e.id()) for e in entities)))
    return "5"
