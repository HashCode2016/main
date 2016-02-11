from math import sqrt, fabs, pow, ceil
from warehouse import Warehouse
import sys

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
        for i in range(len(Warehouse.product_weight)):
            self.items.append(0)
        #self.turns = 0
        self.working_turn = 0
        self.command_string = []
        self.status = DRONE_STATUS.AVAILABLE

    # Error cases: too much weight / not enough produts available in warehouse
    def load(self, warehouse, product_id, nb_products, order):
        self.move(warehouse.x, warehouse.y)
        # Load
        warehouse.pick(product_id, nb_products)
        self.items[product_id] += nb_products
        order.is_bringing(product_id, nb_products)
        self.curr_weight += Drone.get_product_weight_with_nb(product_id, nb_products)
        #self.turns += 1
        self.working_turn += 1
        self.status = DRONE_STATUS.WORKING
        self.command_string.append("{0} L {1} {2} {3}".format(self.id, warehouse.id, product_id, nb_products))
        print("{0} L {1} {2} {3}".format(self.id, warehouse.id, product_id, nb_products))
        sys.stdout.flush()

    def deliver_all(self, order):
        for i in range(len(self.items)):
            if self.items[i] != 0:
                self.deliver(order, i, self.items[i])

    def deliver(self, order, product_id, nb_products):
        self.move(order.x, order.y)
        # Deliver
        order.drop(product_id, nb_products)
        self.items[product_id] -= nb_products
        self.curr_weight -= Drone.get_product_weight_with_nb(product_id, nb_products)
        #self.turns += 1
        self.working_turn += 1
        self.status = DRONE_STATUS.WORKING
        self.command_string.append("{0} D {1} {2} {3}".format(self.id, order.id, product_id, nb_products))
        print("{0} D {1} {2} {3}".format(self.id, order.id, product_id, nb_products))
        sys.stdout.flush()

    def move(self, x, y):
        distance = self.distance(x, y)
        #self.turns += ceil(distance)
        self.working_turn += ceil(distance)
        self.x = x
        self.y = y

    def distance(self, x, y):
        Xs = pow(fabs(self.x - x), 2)
        Ys = pow(fabs(self.y - y), 2)
        return sqrt(Xs +Ys)

    def next_turn(self):
        #self.turns += 1
        if self.working_turn > 0:
            self.working_turn -= 1
        if self.working_turn <= 0:
            self.status = DRONE_STATUS.AVAILABLE

    def is_full(self, product_id, nb_products):
        if product_id is None:
            return False

        expected_weight = self.curr_weight + Drone.get_product_weight_with_nb(product_id, nb_products)
        return expected_weight > Drone.max_weight

    def get_product_weight_with_nb(product_id, nb_products):
        return Drone.get_product_weight(product_id) * nb_products

    def get_product_weight(product_id):
        return int(Warehouse.product_weight[product_id])
