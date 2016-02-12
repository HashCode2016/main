#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include "drone.h"

class DroneManager
{
public:
    DroneManager();

    bool simu_finished();
    void next_turn();
    Drone * next_available_drone();

private:
    QVector<Drone> _drones;
};

#endif // DRONEMANAGER_H
