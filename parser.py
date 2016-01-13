#/bin/python
#-!- encoding:utf8 -!-

# ------ IMPORTS -----------------------------------------------------------------------------------------

import os, sys

# ------ CONFIGURATION -----------------------------------------------------------------------------------
#
# nom du fichier à parser
INPUT_FILENAME = 'input.txt';
#
#

# ------ CONSTANTES --------------------------------------------------------------------------------------
#
# chemin absolu vers le dossier contenant le script
SCRIPT_ABS_DIR = os.path.dirname(os.path.realpath(__file__));
#
#
# récupération des options
OPT_VERBOSE = False;
for o in range(1,len(sys.argv)):
    if '-v' in sys.argv[o]:
        OPT_VERBOSE = True;

# ------ FONCTIONS ---------------------------------------------------------------------------------------
# print ssi l'option -v existe
def printv(str):
    if OPT_VERBOSE:
        print(str);

# ------ SCRIPT ------------------------------------------------------------------------------------------

# affiche le chemin d'execution
printv("Running from %s\n" % SCRIPT_ABS_DIR);

with open(SCRIPT_ABS_DIR+'/'+INPUT_FILENAME, 'r') as f:
    for l in f:
        printv(l);
