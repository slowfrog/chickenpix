import cp

# Nothing
def run(self, manager):
    print("My id is %d" % self.id())
    print("EntityManager is called %s and has %d entities" % (manager.name(), manager.size()))
    return "5"
