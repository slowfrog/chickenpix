import cp

SELECTED_COLOR = (255, 255, 255, 255)
NORMAL_COLOR = (255, 255, 0, 128)

ITEM_START = 0
ITEM_QUIT = 1
ITEM_CREDITS = 2
ITEM_TAGS = ["START", "QUIT", "CREDITS"]


def init(entity, manager):
    entity.items = [ manager.getByTag(tag)[0] for tag in ITEM_TAGS ]
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

def trigger_menu(entity, manager):
    if entity.sel == ITEM_START:
        manager.setSwitch("Main")
        print("Starting...")
    elif entity.sel == ITEM_QUIT:
        manager.setSwitch("EXIT")
        print("Quitting...")
    elif entity.sel == ITEM_CREDITS:
        print("Showing credits")
    else:
        raise Exception("Unknown selection %d" % entity.sel)
    
def handle_keys(entity, manager):
    input = entity.getComponent(cp.Input.TYPE)
    if (input.state.isKeyDown(cp.InputState.SPACE) or
        input.state.isKeyDown(cp.InputState.ENTER)):
        trigger_menu(entity, manager)
        
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

def handle_controllers(entity, manager):
    for actent in manager.getEntities(cp.Actionable.TYPE):
        next = entity.items.index(actent)
        if next < 0:
            continue
        act = actent.getComponent(cp.Actionable.TYPE)
        if act.action == "ButtonJustDown":
            change_selection(manager, entity, next)
        elif act.action == "ButtonClicked":
            trigger_menu(entity, manager)
        
# Main entry point
def update(entity, manager):
    handle_keys(entity, manager)
    handle_controllers(entity, manager)

def exit(entity, manager):
    pass
