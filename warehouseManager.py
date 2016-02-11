from warehouse import Warehouse
class WarehouseManager():
	"""docstring for WareHouse"""
	def __init__(self, products_weight):
		Warehouse.product_weight = products_weight
		self.warehouses = []
		
	def get_warehouse_having_item(self, item, quantity):
		for warehouse in self.warehouses:
			if warehouse.has(item, quantity):
				return warehouse
		return None	

	def get_closest_wharehouse_having_item(self, item, quantity, drone):
		# opti possible with only one for
		having_item_warehouse = []
		for warehouse in self.warehouses:
			if warehouse.has(item, quantity):
				having_item_warehouse.append(warehouse)
		if len(having_item_warehouse) == 0:
			return None

		# search for the closest
		closest_warehouse = having_item_warehouse[0]
		min_distance = drone.distance(closest_warehouse.x,closest_warehouse.y)
		for warehouse in having_item_warehouse:
			cur_distance = drone.distance(warehouse.x,warehouse.y)
			if cur_distance < min_distance:
				min_distance = cur_distance
				closest_warehouse = warehouse
		return closest_warehouse

	def add_warehouse(self, id, x, y, quantities):
		self.warehouses.append(Warehouse(id, x, y, quantities))

