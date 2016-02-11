from math import sqrt, fabs, pow, ceil
from warehouse import Warehouse

class DRONE_STATUS:
    WORKING = 0
    AVAILABLE = 1


class Drone:
    max_weight = 0
    max_turns = 0

    def __init__(self, id, x, y):
        self.id = id
        self.x = x
        self.y = y
        self.curr_weight = 0
        self.items = []
        self.turns = 0
        self.working_turn = 0
        self.command_string = []
        self.status = DRONE_STATUS.AVAILABLE

    # Error cases: too much weight / not enough produts available in warehouse
    def load(self, warehouse, product_id, nb_products, order):
        self.move(warehouse.x, warehouse.y)
        # Load
        warehouse.pick(product_id, nb_products)
        for i in range(nb_products):
            self.items.append(product_id)
        order.is_bringing(product_id, nb_products)
        self.curr_weight += (Drone.get_product_weight(product_id) * nb_products)
        self.turns += 1
        self.working_turn += 1
        self.status = DRONE_STATUS.WORKING
        self.command_string.append("{0} L {1} {2} {3}", self.id, warehouse.id, product_id, nb_products)

    def deliver(self, order, product_id, nb_products):
        self.move(order.x, order.y)
        # Deliver
        order.drop(product_id, nb_products)
        for i in range(nb_products):
            self.items.remove(product_id)
        self.curr_weight -= (Drone.get_product_weight(product_id) * nb_products)
        self.turns += 1
        self.working_turn += 1
        self.status = DRONE_STATUS.WORKING
        self.command_string.append("{0} D {1} {2} {3}", self.id, order.id, product_id, nb_products)

    def move(self, x, y):
        distance = self.distance(x, y)
        self.turns += ceil(distance)
        self.working_turn += ceil(distance)
        self.x = x
        self.y = y

    def distance(self, x, y):
        Xs = pow(fabs(self.x - x), 2)
        Ys = pow(fabs(self.y - y), 2)
        return sqrt(Xs +Ys)

    def next_turn(self):
        self.turns += 1
        if self.working_turn > 0:
            self.working_turn -= 1
        if self.working_turn <= 0:
            self.status = DRONE_STATUS.AVAILABLE

    def is_full_if(self, product_id, nb_products):
        if product_id is None:
            return False

        expected_weight = self.curr_weight + (Drone.get_product_weight(product_id) * nb_products)
        return expected_weight > Drone.max_weight

    def get_product_weight(product_id):
        Warehouse.product_weight[product_id]
