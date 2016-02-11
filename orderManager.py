from order import Order
class OrderManager():
	"""docstring for OrderManager"""
	def __init__(self):
		self.orders = []

	def add_order(self, id, x, y, types):
		self.orders.append(Order(id, x, y, items))

	def next_unhandled_order(self):
		return self.orders[0]