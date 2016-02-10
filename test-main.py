from parser_wrapper_test2016 import ParserWrapperTest2016
import sys
import os
from utils import INPUT_FILE_DIR


class Square:
    def __init__(self, line, col, must_be_painted):
        self.line = line
        self.col = col
        self.must_be_painted = must_be_painted
        self.is_painted = False


def create_empty_building_facade(parser):
    facade = []
    for line_idx in range(parser.nb_lines):
        facade.append([])
        for col_idx in range(parser.nb_columns):
            facade[line_idx].append(None)

    for line_idx in range(parser.nb_lines):
        for col_idx in range(parser.nb_columns):
            must_be_painted = (parser.matrix[line_idx][col_idx] == '#')
            #print("{0} {1} : {2}".format(line_idx, col_idx, must_be_painted))
            facade[line_idx][col_idx] = Square(line_idx, col_idx, must_be_painted)

    return facade


def paint_facade(facade, nb_lines, nb_columns):
    paint_operations = []
    for line_idx in range(0, nb_lines):
        for col_idx in range(0, nb_columns):
            right_empty_squares = get_right_un_painted_squares(facade, line_idx, col_idx, nb_columns)
            bottom_empty_squares = get_bottom_un_painted_squares(facade, line_idx, col_idx, nb_lines)
            nb_right_empty = len(right_empty_squares)
            nb_bottom_empty = len(bottom_empty_squares)

            if (nb_right_empty == 0 and nb_bottom_empty == 0) or (nb_right_empty == 1 and nb_bottom_empty == 1):
                square = facade[line_idx][col_idx]
                if square.must_be_painted and not square.is_painted:
                    operation = paint_square(square)
                    paint_operations.append(operation)
            else:
                if nb_right_empty >= nb_bottom_empty:
                    operation = paint_squares(right_empty_squares)
                    paint_operations.append(operation)
                elif nb_right_empty <= nb_bottom_empty:
                    operation = paint_squares(bottom_empty_squares)
                    paint_operations.append(operation)

    return paint_operations


def get_right_un_painted_squares(facade, line_idx, col_idx, bound):
    if facade[line_idx][col_idx].is_painted:
        return []

    un_painted_right_squares = []

    while col_idx < bound and facade[line_idx][col_idx].must_be_painted:
        curr_square = facade[line_idx][col_idx]
        if not curr_square.is_painted:
            un_painted_right_squares.append(curr_square)

        col_idx += 1

    return un_painted_right_squares


def get_bottom_un_painted_squares(facade, line_idx, col_idx, bound):
    if facade[line_idx][col_idx].is_painted:
        return []

    un_painted_bottom_squares = []
    while line_idx < bound and facade[line_idx][col_idx].must_be_painted:
        curr_square = facade[line_idx][col_idx]
        if not curr_square.is_painted:
            un_painted_bottom_squares.append(curr_square)

        line_idx += 1

    return un_painted_bottom_squares


def paint_squares(squares):
    for s in squares:
        paint_square(s)

    first_square = squares[0]
    last_square = squares[-1]
    return "PAINT_LINE {0} {1} {2} {3}".format(first_square.line, first_square.col, last_square.line, last_square.col)


def paint_square(square):
    square.is_painted = True
    #print("Paint {0} {1}".format(square.line, square.col))
    return "PAINT_SQUARE {0} {1} {2}".format(square.line, square.col, 0)


def write_output_file(operations):
    '''for op in operations:
        write_to_file_with_newline(sys.stdout, op)'''
    with open('test-output2016.out', 'w') as f:
        write_to_file_with_newline(f, len(operations))
        for op in operations:
            write_to_file_with_newline(f, op)


def write_to_file_with_newline(file, line):
    file.write("{0}\n".format(line))


if __name__ == "__main__":
    input = sys.argv[1] if len(sys.argv) > 1 else 'test-input2016-logo.in'
    input = os.path.join(INPUT_FILE_DIR, input)
    p = ParserWrapperTest2016(input)
    p.parse()
    p.coherence_test()

    # Test output
    '''for l in range(p.nb_lines):
        for c in range(p.nb_columns):
            print(p.matrix[l][c], end='')
        print()
    '''

    building_facade = create_empty_building_facade(p)
    operations = paint_facade(building_facade, p.nb_lines, p.nb_columns)
    write_output_file(operations)
    print("{0} lines written into output file".format(len(operations)))
