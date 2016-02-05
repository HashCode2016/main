from parser_wrapper_test2016 import ParserWrapperTest2016
import sys
import os
from utils import INPUT_FILE_DIR

if __name__ == "__main__":
    input = sys.argv[1] if len(sys.argv) > 1 else 'test-input2016-logo.in'
    input = os.path.join(INPUT_FILE_DIR, input)
    p = ParserWrapperTest2016(input)
    p.parse()
    p.coherence_test()
    print(p.nb_lines)
    print(p.nb_columns)
    #print(p.get_line(0))
    '''for r in p.get_lines(0, 2):
        print(r)'''
    print(p.get_column(0))
    for c in p.get_columns(0, 2):
        print(c)

