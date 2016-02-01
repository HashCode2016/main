
#convert a string into a int or a float
def aformat(s):
    try:
        s = int(s)
        return s
    except ValueError:
        pass

    try:
        s = float(s)
    except ValueError:
        pass
    return s
