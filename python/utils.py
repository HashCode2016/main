import os
import sys
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

# ------ CONSTANTES ---------------
#
# chemin absolu vers le dossier contenant le script
SCRIPT_ABS_DIR = os.path.dirname(os.path.realpath(__file__))
INPUT_FILE_DIR = os.path.join(SCRIPT_ABS_DIR, 'input-files')

# récupération des options
OPT_VERBOSE = False
for o in range(1, len(sys.argv)):
    if '-v' in sys.argv[o]:
        OPT_VERBOSE = True


# ------ FONCTIONS -----------------
# print ssi l'option -v existe
def printv(str):
    if OPT_VERBOSE:
        print(str)
