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
		# for warehouse in self.warehouses:
		# 	if warehouse.has(item, quantity):
		# 		return warehouse
		# return None

		# # opti possible with only one for
		# having_item_warehouse = []
		# for drone in self.drones:
		# 	if drone.status == DRONE_STATUS.AVAILABLE:
		# 		having_item_warehouse.append(drone)
		# if len(having_item_warehouse) == 0:
		# 	return None

		# # search for the closest
		# closest_drone = having_item_warehouse[0]
		# min_distance = closest_drone.distance(x,y)
		# for drone in having_item_warehouse:
		# 	cur_distance = drone.distance(x,y)
		# 	if cur_distance < min_distance:
		# 		min_distance = cur_distance
		# 		closest_drone = drone
		# return closest_drone
		pass

	def add_warehouse(self, id, x, y, quantities):
		self.warehouses.append(Warehouse(id, x, y, quantities))

