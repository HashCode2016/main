#include "dronemanager.h"
#include "src/utils/macro.h"

int DroneManager::_DRONE_COUNT = 0;

DroneManager::DroneManager(WarehouseManager & wm) :
    turn_counter(0),
    _drones()
{
    for(int i = 0; i < _DRONE_COUNT; ++i)
    {   _drones.push_back(Drone(i, wm.drones_origin(), Warehouse::PRODUCT_COUNT()));
    }
}

bool DroneManager::simu_finished()
{
    return (turn_counter >= Drone::MAX_TURN());
}

void DroneManager::next_turn()
{
    // foreach drone, call next_turn
    for(QList<Drone>::iterator it = _drones.begin(); it != _drones.end(); ++it)
    {   it->next_turn();
    }
    // increment turn counter
    turn_counter++;
    // info
    if(turn_counter % 2000 == 0)
    {   INFO("DroneManager", "next_turn", QString("%1/%2 completed.")
             .arg(QString::number(turn_counter),
                  QString::number(Drone::MAX_TURN()))
             .toStdString());
    }
}

Drone *DroneManager::next_available_drone()
{
    Drone * drone = NULL;
    for(QList<Drone>::iterator it = _drones.begin(); it != _drones.end(); ++it)
    {   if(it->state() == Drone::AVAILABLE)
        {   drone = &(*it);
            break;
        }
    }
    return drone;
}

QByteArray DroneManager::commands() const
{
    QByteArray data;
    int commands_total(0);
    for(QList<Drone>::const_iterator it = _drones.begin(); it != _drones.end(); ++it)
    {   commands_total += it->commands_count();
        data += it->commands();
    }
    return data.prepend(QString::number(commands_total).append('\n').toUtf8());
}

QString DroneManager::to_string() const
{
    QString drone_list("\n");
    for(QList<Drone>::const_iterator it = _drones.begin(); it != _drones.end(); ++it)
    {   drone_list += it->to_string() + '\n';
    }
    return drone_list;
}

int DroneManager::DRONE_COUNT(int DRONE_COUNT)
{
    if(DRONE_COUNT > 0)
    {   _DRONE_COUNT = DRONE_COUNT;
    }
    return _DRONE_COUNT;
}

