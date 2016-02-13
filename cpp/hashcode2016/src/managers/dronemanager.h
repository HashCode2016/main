#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include "src/objects/drone.h"
#include "warehousemanager.h"

class DroneManager
{
public:
    DroneManager(WarehouseManager & wm);

    inline int count() const { return _drones.count(); }

    bool simu_finished();
    void next_turn();
    Drone * next_available_drone();

    QByteArray commands() const;

    QString to_string() const;

    static int DRONE_COUNT(int DRONE_COUNT = -1);

private:
    int turn_counter;
    QList<Drone> _drones;

    static int _DRONE_COUNT;
};

#endif // DRONEMANAGER_H
