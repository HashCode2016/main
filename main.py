from input_parser import Parser
import sys
import os
from utils import INPUT_FILE_DIR

if __name__ == "__main__":
    input = sys.argv[1] if len(sys.argv) > 1 else 'input.txt'
    input = os.path.join(INPUT_FILE_DIR, input)
    p = Parser(input)
    p.parse()
    print(p.get(0, 0))
    print(p.get(0, 1))
    print(p.get(0, 2))
    print(p.get(1, 0))


