import drone
class DroneManager():
	"""docstring for DroneManager"""
	def __init__(self, max_weight, drone_count, x0, y0):
		self.drones = []
		
	def next_available_drone(self):
		return self.drones[0]

	def closest_drone_available(self, x, y):
		return self.drone[0]
