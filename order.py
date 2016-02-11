class ORDER_STATUS:
    UNHANDELD = 0
    INPROGRESS = 1
    TERMINATED = 2


class Order:
    def __init__(self, id, x, y, items):
        self.id = id
        self.x = x
        self.y = y
        self.items = items
        self.status = ORDER_STATUS.UNHANDELD

    def count(self, product_type):
        return self.items.count(product_type)
