import cp

SELECTED_COLOR = (255, 255, 255, 255)
NORMAL_COLOR = (255, 255, 0, 128)

def init(entity, manager):
    entity.items = [ manager.getByTag(tag)[0]
                     for tag in ["START", "QUIT", "CREDITS"] ]
    selection = manager.getByTag("SELECTED")[0]
    pointer = manager.getByTag("POINTER")[0]
    entity.sel = -1
    for i in xrange(len(entity.items)):
        if selection == entity.items[i]:
            entity.sel = i
            strans = entity.items[i].getComponent(cp.Transform.TYPE)
            ptrans = pointer.getComponent(cp.Transform.TYPE)
            ptrans.y = strans.y
            visual = entity.items[i].getComponent(cp.Visual.TYPE)
            visual.color = SELECTED_COLOR
        else:
            visual = entity.items[i].getComponent(cp.Visual.TYPE)
            visual.color = NORMAL_COLOR

    entity.downdown = False
    entity.updown = False

def change_selection(manager, entity, next):
    previtem = entity.items[entity.sel]
    nextitem = entity.items[next]
    # Move the pointer
    nexttrans = nextitem.getComponent(cp.Transform.TYPE)
    pointer = manager.getByTag("POINTER")[0]
    ptrans = pointer.getComponent(cp.Transform.TYPE)
    ptrans.y = nexttrans.y
    # Change the color of the selection
    prevvis = previtem.getComponent(cp.Visual.TYPE)
    nextvis = nextitem.getComponent(cp.Visual.TYPE)
    prevvis.color = NORMAL_COLOR
    nextvis.color = SELECTED_COLOR
    # Record the new selection
    entity.sel = next
    
def update(entity, manager):
    input = entity.getComponent(cp.Input.TYPE)
    if input.state.isKeyDown(cp.InputState.SPACE):
        print ("Current selection %s" % entity.sel)
        
    if input.state.isKeyDown(cp.InputState.DOWN):
        if not entity.downdown:
            change_selection(manager, entity,
                             (entity.sel + 1) % len(entity.items))
            entity.downdown = True
    else:
        entity.downdown = False
        
    if input.state.isKeyDown(cp.InputState.UP):
        if not entity.updown:
            change_selection(manager, entity,
                             (entity.sel + len(entity.items) - 1) % len(entity.items))
            entity.updown = True
    else:
        entity.updown = False

def exit(entity, manager):
    pass
