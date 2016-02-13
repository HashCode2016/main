#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "src/managers/dronemanager.h"
#include "src/managers/ordermanager.h"

class Simulator
{
public:
    static void run_simu(WarehouseManager & wm, OrderManager & om, DroneManager & dm);

private:
    static void _update_drones(WarehouseManager & wm, OrderManager & om, DroneManager & dm);
    static void _load_drone(Drone * drone, Order * order, WarehouseManager & wm);
    static bool _update_load(const Item & item, Drone * drone);

private:
    Simulator(){}

};

#endif // SIMULATOR_H
