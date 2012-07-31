import cp

SELECTED_COLOR = (255, 255, 255, 255)
NORMAL_COLOR = (255, 255, 0, 128)

ITEM_START = 0
ITEM_QUIT = 1
ITEM_CREDITS = 2
ITEM_TAGS = ["START", "QUIT", "CREDITS"]


def init(entity, manager):
    entity.items = [ manager.getByTag(tag)[0] for tag in ITEM_TAGS ]
    entity.all_menu = [ en.getComponent(cp.Transform.TYPE)
                        for en in manager.getEntities(cp.Visual.TYPE) ]
    entity.credit_objs = []
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
    entity.credits = False

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

def hide_menu(entity, manager):
    for trans in entity.all_menu:
        trans.moveBy(1000, 0)

def hide_credits(entity, manager):
    for en in entity.credit_objs:
        manager.destroyEntity(en)
    entity.credit_objs = []
    for trans in entity.all_menu:
        trans.moveBy(-1000, 0)
    entity.credits = False
    
def create_scrolling_text(entity, manager, res, text, y):
    ent = manager.createEntity()
    ent.addComponent(res.makeText(text, "sans_big", (255, 0, 0, 128)))
    ent.addComponent(cp.Transform(400 - 9 * len(text), y))
    ent.addComponent(cp.Mobile(0, -1))
    entity.credit_objs.append(ent)
    
def create_scrolling_image(entity, manager, res, name, x, y):
    ent = manager.createEntity()
    ent.addComponent(cp.Transform(x, y))
    ent.addComponent(res.makeImage(name))
    ent.addComponent(cp.Mobile(0, -1))
    entity.credit_objs.append(ent)

def show_credits(entity, manager):
    if entity.credits:
        return
    entity.credits = True

    hide_menu(entity, manager)
    
    re = manager.getEntities(cp.Resources.TYPE)[0]
    res = re.getComponent(cp.Resources.TYPE)

    texts = [ "Thank you for playing Chickenpix",
              "",
              "",
              "This is not much of a game...",
              "",
              "... but anyway, it was fun to make.",
              "",
              "",
              "We want to thank all the great",
              "people who organized this contest",
              "and all the artists who built assets.",
              "",
              "",
              "We are also grateful for the",
              "open-source projects and libraries that",
              "made Chickenpix possible.",
              "",
              "",
              "In no particular order:",
              "",
              "ClanLib",
              "SFML",
              "tinyxml",
              "TmxParser",
              "Tiled",
              "The GIMP",
              "gcc",
              "Google Web Fonts",
              "",
              "",
              "",
              "And some not-so-open-source ones too",
              "",
              "VisualStudio Express",
              "XCode",
              "Graphics Gale",
              "",
              "",
              "",
              "See you in the next contest!",
              "",
              "The Chickenpix Team",
              "~~~~~~~~~~~~~~~~~~~",
              "",
              "Coder: David Amar",
              "Artist: Manu Etasse",
              "Scenario: Florian Fourure",
              "Coder: Fred Germonneau",
              "Tester: Nico Peyrin",
              "Coder: Chris Rivier",
              "Coder: Laurent Vaucher",
              "Coder: Nico Verdeille",

              ]
    y = 600
    for t in texts:
        create_scrolling_text(entity, manager, res, t, y)
        y += 50

    create_scrolling_image(entity, manager, res, "richard", 40, 700)
    create_scrolling_image(entity, manager, res, "mayor", 740, 940)
    create_scrolling_image(entity, manager, res, "wizard", 200, 1450)
    create_scrolling_image(entity, manager, res, "streetboy", 600, 2100)
    create_scrolling_image(entity, manager, res, "princess", 400, 2500)
    create_scrolling_image(entity, manager, res, "pig", 400, 3500)


def trigger_menu(entity, manager):
    if entity.sel == ITEM_START:
        print("Starting...")
        manager.setSwitch("Main")
    elif entity.sel == ITEM_QUIT:
        print("Quitting...")
        manager.setSwitch("EXIT")
    elif entity.sel == ITEM_CREDITS:
        print("Showing credits")
        show_credits(entity, manager)
    else:
        raise Exception("Unknown selection %d" % entity.sel)
    
def handle_keys(entity, manager):
    if entity.credits:
        handle_keys_credits(entity, manager)
    else:
        handle_keys_normal(entity, manager)

def handle_keys_credits(entity, manager):
    input = entity.getComponent(cp.Input.TYPE)
    if input.state.isKeyDown(cp.InputState.ESCAPE):
       hide_credits(entity, manager)     
        
def handle_keys_normal(entity, manager):
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
