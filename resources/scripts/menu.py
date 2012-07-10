import cp

def init(entity, manager):
    entity.items = [ manager.getByTag("START")[0],
                     manager.getByTag("QUIT")[0],
                     manager.getByTag("CREDITS")[0],
                     ]
    selection = manager.getByTag("SELECTED")[0]
    for i in xrange(len(entity.items)):
        if selection == entity.items[i]:
            entity.sel = i
            trans = entity.items[i].getComponent(cp.Transform.TYPE)
            trans.x = 350
            break
    else:
        entity.sel = -1
    entity.downdown = False
    entity.updown = False

def change_selection(entity, next):
    prev = entity.sel
    previtem = entity.items[prev]
    nextitem = entity.items[next]
    prevtrans = previtem.getComponent(cp.Transform.TYPE)
    nexttrans = nextitem.getComponent(cp.Transform.TYPE)
    prevtrans.x = 300
    nexttrans.x = 350
    entity.sel = next
    
def update(entity, manager):
    input = entity.getComponent(cp.Input.TYPE)
    if input.state.isKeyDown(cp.InputState.SPACE):
        print ("Current selection %s" % entity.sel)
        
    if input.state.isKeyDown(cp.InputState.DOWN):
        if not entity.downdown:
            change_selection(entity,
                             (entity.sel + 1) % len(entity.items))
            entity.downdown = True
    else:
        entity.downdown = False
        
    if input.state.isKeyDown(cp.InputState.UP):
        if not entity.updown:
            change_selection(entity,
                             (entity.sel + len(entity.items) - 1) % len(entity.items))
            entity.updown = True
    else:
        entity.updown = False

def exit(entity, manager):
    pass
