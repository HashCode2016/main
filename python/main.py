from input_parser import Parser
import sys
import os
from utils import INPUT_FILE_DIR

from droneManager import DroneManager
from warehouseManager import WarehouseManager
from orderManager import OrderManager
from simu import simu


def create_model(parser):
    product_weights = parser.get_line(2)
    warehouseManager = WarehouseManager(product_weights)
    nb_warehouse = int(parser.get_line(3)[0])
    for i in range(nb_warehouse):
        coords = parser.get_line(4 + i*2)
        x = coords[1]
        y = coords[0]
        quantities = parser.get_line(5 + i*2)
        #print("x {0} / y {1} / quant_len : {2}".format(x, y, len(quantities)))
        warehouseManager.add_warehouse(i, x, y, quantities)

    max_weight = int(parser.get_line(0)[-1])
    drone_count = int(parser.get_line(0)[2])
    max_turns = int(parser.get_line(0)[3])
    first_warehouse_x = int(p.lines[4][1])
    first_warehouse_y = int(p.lines[4][0])
    droneManager = DroneManager(max_weight, drone_count, first_warehouse_x, first_warehouse_y, max_turns)
    
    orderManager = OrderManager()
    order_idx = 4 + nb_warehouse*2
    nb_orders = int(parser.get_line(order_idx)[0])
    for i in range(nb_orders):
        coords = parser.get_line(order_idx + 1 + i*3)
        x = coords[1]
        y = coords[0]
        products_needed = parser.get_line(order_idx + 3 + i*3)
        #print("x {0} / y {1} / pro_len {2}".format(x, y, len(products_needed)))
        orderManager.add_order(i, x, y, products_needed)

    return warehouseManager, orderManager, droneManager


if __name__ == "__main__":
    file = sys.argv[1] if len(sys.argv) > 1 else 'busy_day'
    if not file.endswith('.in'):
        file_name = file + '.in'
    else:
        file_name = file
    input_fn = 'input2016-{0}'.format(file_name)
    input = os.path.join(INPUT_FILE_DIR, input_fn)
    p = Parser(input)
    p.parse()

    warehouseManager, orderManager, droneManager = create_model(p)
    simu(droneManager, orderManager, warehouseManager)
    output_file = 'output2016-{0}.out'.format(file)
    nb_lines = droneManager.write_output(output_file)
    print("{0} lines has been printed to {1}".format(nb_lines, output_file))
