# /bin/python3
from parser import Parser
import sys



if __name__ == "__main__":
    input = sys.argv[1] if len(sys.argv)>1 else 'input.txt'
    p = Parser(input)
    p.parse()
    print(p.get(0,0))

