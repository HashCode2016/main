# -!- encoding:utf8 -!-

# ------ IMPORTS -------------------
from hash_code_parser import HashCodeParser


class ParserWrapperTest2016(HashCodeParser):
    def parse(self):
        super(ParserWrapperTest2016, self).parse()
        # Recalculate rows
        self.parser.lines[1:] = [list(row[0]) for row in self.parser.lines[1:]]
        # Recalculate matrix
        self.generate_matrix()
