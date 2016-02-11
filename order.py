class ORDER_STATUS:
    UNHANDELD = 0
    INPROGRESS = 1
    TERMINATED = 2


class Order:
    def __init__(self, id, x, y, items):
        self.id = id
        self.x = x
        self.y = y
        self.items_needed = items
        self.items_in_progress = []
        self.status = ORDER_STATUS.UNHANDELD

    def count(self, product_type):
        return self.items.count(product_type)

    # Return first needed object + quantity
    # Can return None if nothing left
    def item_left(self):
        items_not_handled = self.items_needed
        for item in self.items_in_progress:
            items_not_handled.remove(item)

        if len(items_not_handled) == 0:
            return None, None

        first_item = items_not_handled[0]
        nb_first_item_needed = items_not_handled.count(first_item)

        return first_item, nb_first_item_needed

    def is_bringing(self, product_id, nb_products):
        for i in range(nb_products):
            self.items_in_progress.append(product_id)
        self.status = ORDER_STATUS.INPROGRESS

    def cancel(self):
        self.status = ORDER_STATUS.TERMINATED

    def drop(self, product_id, nb_products):
        for i in range(nb_products):
            self.items_needed.remove(product_id)
            self.items_in_progress.remove(product_id)

        if len(self.items_needed) == 0:
            self.status = ORDER_STATUS.TERMINATED
        else:
            self.status = ORDER_STATUS.UNHANDELD
