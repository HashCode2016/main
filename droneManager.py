from drone import Drone, DRONE_STATUS

class DroneManager():
	"""docstring for DroneManager"""
	def __init__(self, max_weight, drone_count, x0, y0, max_turn):
		self.drones = []
		self.max_weight = max_weight
		self.max_turn = max_turn
		self.current_turn = 0
		for i in range(0, drone_count):
			self.drones.append(Drone(i, x0, y0))
		Drone.max_weight = max_weight
		Drone.max_turn = max_turn
		
	def next_available_drone(self):
		for drone in self.drones:
			if drone.status == DRONE_STATUS.AVAILABLE:
				return drone
		return None

	def closest_drone_available(self, x, y):
		# opti possible with only one for
		available_drones = []
		for drone in self.drones:
			if drone.status == DRONE_STATUS.AVAILABLE:
				available_drones.append(drone)
		if len(available_drones) == 0:
			return None

		# search for the closest
		closest_drone = available_drones[0]
		min_distance = closest_drone.distance(x,y)
		for drone in available_drones:
			cur_distance = drone.distance(x,y)
			if cur_distance < min_distance:
				min_distance = cur_distance
				closest_drone = drone
		return closest_drone

	def next_turn(self):
		for drone in self.drones:
			drone.next_turn()
		self.current_turn += 1

	def simu_finished(self):
		return (self.current_turn - self.max_turn) < 0

	def get_output(self):
		output = []
		for drone in self.drones:
			ouput += drone.command_string
		return ouput

	def write_output(self, filename):
		output = self.get_output()
		with open(filename, 'w') as f:
			f.write("{0}\n".format(len(output)))
	        for op in output:
				f.write("{0}\n".format(op)