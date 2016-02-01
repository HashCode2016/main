# /bin/python3
# -!- encoding:utf8 -!-

# ------ IMPORTS -------------------
import os
import sys

# ------ CONFIGURATION -------------
#
# nom du fichier à parser
INPUT_FILENAME = 'input.txt'
#
#


class Parser:
    def __init__(self, file_name):
        self.file_name = file_name
        self.lines = []

    def parse(self):
        splitted_line = []
        with open(self.file_name, 'r') as f:
            for line in f:
                splitted_line = line.split()
                self.lines.append(splitted_line)

    def column(self, c):
        col = []
        for line in self.lines:
            col.append(line[c])
        return col

    def line(self, l):
        return self.lines[l]

    def columns(self, start, end):
        while(start < end):
            yield(self.column(start))
            start += 1

    def lines(self, start, end):
        while(start < end):
            yield(self.line(start))
            start += 1


# ------ CONSTANTES ---------------
#
# chemin absolu vers le dossier contenant le script
SCRIPT_ABS_DIR = os.path.dirname(os.path.realpath(__file__))
#
#
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
