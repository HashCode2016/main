# -!- encoding:utf8 -!-

# ------ IMPORTS -------------------
import os
import sys
from utils import *


class Parser:
    def __init__(self, file_name):
        self.file_name = file_name
        self.lines = []
        self.size = 0
        self.max_col = 0

    def parse(self):
        self.size = 0
        with open(self.file_name, 'r') as f:
            for line in f:
                self.size += 1
                splitted_line = [int(x) for x in line.split()]
                self.lines.append(splitted_line)
                self.max_col = max(len(splitted_line), self.max_col)

    def get_column(self, c):
        col = []
        if c >= self.max_col:
            return col
        for line in self.lines:
            if len(line) > c:
                col.append(line[c])
        return col

    def get_line(self, l):
        return self.lines[l] if l < self.size else []

    def get_columns(self, start, end):
        while start < end:
            yield(self.get_column(start))
            start += 1

    def get_lines(self, start, end):
        while start < end:
            yield(self.get_line(start))
            start += 1

    def get(self, l, c):
        line = self.get_line(l)
        return aformat(line[c]) if len(line) > c else None
