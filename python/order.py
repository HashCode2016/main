from warehouse import Warehouse

class ORDER_STATUS:
    UNHANDELD = 0
    INPROGRESS = 1
    TERMINATED = 2


class Order:
    def __init__(self, id, x, y, items):
        self.id = id
        self.x = x
        self.y = y
        self.items_needed = []
        self.items_in_progress = []
        for i in range(len(Warehouse.product_weight)):
            self.items_needed.append(items.count(i))
            self.items_in_progress.append(0)
        self.status = ORDER_STATUS.UNHANDELD

    def count(self, product_type):
        return self.items.count(product_type)

    # Return first needed object + quantity
    # Can return None if nothing left
    def item_left(self):
        for i in range(len(self.items_needed)):
            item_diff = self.items_needed[i] - self.items_in_progress[i]
            if item_diff > 0:
                return i, item_diff

        return None, None

    def is_bringing(self, product_id, nb_products):
        self.items_in_progress[product_id] += nb_products
        self.status = ORDER_STATUS.INPROGRESS

    def cancel(self):
        self.status = ORDER_STATUS.TERMINATED

    def drop(self, product_id, nb_products):
        self.items_needed[product_id] -= nb_products
        self.items_in_progress[product_id] -= nb_products
        if(self.items_needed[product_id]<0):
            print('warning!! trying to drop {0} items, {1} needed'.format(nb_products,self.items_needed[product_id]+nb_products ))
            print(product_id, self.id)
            print('in progress ; {0}'.format(self.items_in_progress[product_id]+nb_products))

        if sum(self.items_needed) == 0:
            self.status = ORDER_STATUS.TERMINATED
        else:
            self.status = ORDER_STATUS.UNHANDELD
