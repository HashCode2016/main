#ifndef WAREHOUSEMANAGER_H
#define WAREHOUSEMANAGER_H

#include "warehouse.h"
#include "order.h"
#include "drone.h"

class WarehouseManager
{
public:
    WarehouseManager();


    Warehouse * get_closest_having(ItemLeft item_left, Drone * drone);

private:
    QVector<Warehouse> _warehouses;
};

#endif // WAREHOUSEMANAGER_H
