class Warehouse:
    product_weight = []

    def __init__(self, id, x, y, items):
        self.id = id
        self.x = x
        self.y = y
        self.items = items

    def pick(self, product_id, nb_products):
        available_items = self.items[product_id]
        if available_items < nb_products:
            raise Exception('Not enough products (warehouse {0})'.format(self.id))

        self.items[product_id] -= nb_products

    def has(self, product_id, nb_products):
        return self.items[product_id] >= nb_products