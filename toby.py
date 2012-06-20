import cp

# Nothing
def run():
    if "ss" in dir(cp):
        print "ss found in cp"
    if "em" in dir(cp):
        print "em found in cp"
    em = cp.em
    if em is None:
        print "em is None"
    else:
        print "em is not None"
    if cp.ss(cp.em) is None:
        print "=",
    else:
        print "askfhasklfhasklfhda"
    
    return "5"
