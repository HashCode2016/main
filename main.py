from hash_code_parser import HashCodeParser
import sys
import os
from utils import INPUT_FILE_DIR

if __name__ == "__main__":
    input = sys.argv[1] if len(sys.argv) > 1 else 'file-de-bite.in'
    input = os.path.join(INPUT_FILE_DIR, input)
    p = HashCodeParser(input)
    p.parse()
    p.coherence_test()
