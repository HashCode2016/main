# -!- encoding:utf8 -!-

# ------ IMPORTS -------------------
import os
from hash_code_parser import HashCodeParser
import sys
from utils import *


class ParserWrapperTest2016(HashCodeParser):
    def parse(self):
        super(ParserWrapperTest2016, self).parse()
        self.parser.lines[1:] = [list(row[0]) for row in self.parser.lines[1:]]
