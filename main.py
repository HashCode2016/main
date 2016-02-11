from input_parser import Parser
import sys
import os
from utils import INPUT_FILE_DIR

if __name__ == "__main__":
    input = sys.argv[1] if len(sys.argv) > 1 else 'input2016-busy_day.in'
    input = os.path.join(INPUT_FILE_DIR, input)
    p = Parser(input)
    p.parse()

    first_warehouse_x = p.lines[4][0]
    first_warehouse_y = p.lines[4][1]
