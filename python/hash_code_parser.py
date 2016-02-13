# -!- encoding:utf8 -!-

# ------ IMPORTS -------------------
import os
from input_parser import Parser
import sys
from utils import *


class HashCodeParser:
    def __init__(self, file_name):
        self.parser = Parser(file_name)
        self.nb_lines = 0
        self.nb_columns = 0
        self.matrix = []

    def parse(self):
        self.parser.parse()
        self.nb_lines = self.parser.size - 1
        self.nb_columns = self.parser.get(0, 1)
        self.generate_matrix()

    def generate_matrix(self):
        self.matrix = []
        for i in range(1, len(self.parser.lines)):
            self.matrix.append(self.parser.lines[i])

    '''
    line_idx and column_idx are 0-based. First value at 0
    If value at given indices doesn't exist : returns None
    '''
    def get(self, line_idx, column_idx):
        return self.parser.get(line_idx + 1, column_idx)

    '''
    0-based index
    '''
    def get_column(self, column_idx):
        col = []
        if column_idx >= self.nb_columns:
            return col
        for line in self.parser.lines[1:]:
            if len(line) > column_idx:
                col.append(line[column_idx])
        return col

    '''
    0-based index
    '''
    def get_line(self, line_idx):
        return self.parser.lines[line_idx + 1] if line_idx < self.nb_lines else []

    '''
    0-based index
    end parameter is excluded
    Ex : [1, 4] : returns columns 1, 2 and 3
    '''
    def get_columns(self, start=0, end=None):
        if end is None:
            end = self.nb_columns
        while start < end:
            yield(self.get_column(start))
            start += 1

    '''
    0-based index
    end parameter is excluded
    Ex : [1, 4] : returns lines 1, 2 and 3
    '''
    def get_lines(self, start=0, end=None):
        if end is None:
            end = self.nb_lines
        while start < end:
            yield(self.get_line(start))
            start += 1

    def coherence_test(self):
        if self.nb_lines == 0:
            raise RuntimeError('You must parse before calling the coherence test')

        theoretical_line_nb = self.parser.get(0, 0)
        if theoretical_line_nb != self.nb_lines and theoretical_line_nb == len(self.parser.lines) - 1:
            raise SyntaxError('File should have {0} lines, but got {1}'.format(theoretical_line_nb, self.nb_lines))

        first_line_len = len(self.parser.lines[0])
        theoretical_first_line_nb = 2
        if first_line_len != theoretical_first_line_nb:
            raise SyntaxError('First line not the right size ({0} instead of {1})'.format(first_line_len,
                                                                                          theoretical_first_line_nb))

        for row in self.parser.lines[1:]:
            if len(row) != self.nb_columns:
                raise SyntaxError('Row {0} is not long enough ({1} instead of {2} columns)'.format(row,
                                                                                                   len(row),
                                                                                                   self.nb_columns))