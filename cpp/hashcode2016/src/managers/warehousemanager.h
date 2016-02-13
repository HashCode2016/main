#ifndef WAREHOUSEMANAGER_H
#define WAREHOUSEMANAGER_H

#include "src/objects/warehouse.h"
#include "src/objects/order.h"
#include "src/objects/drone.h"

class WarehouseManager
{
public:
    WarehouseManager();

    inline int count() const { return _warehouses.count(); }
    Warehouse * get_closest_having(int item_id, int item_qty, Drone * drone);
    void add(int id, QPoint pos, QVector<int> quantities);
    QPoint drones_origin();

    /**
     * @brief to_string
     *      Debug function
     * @return
     */
    QString to_string() const;

private:
    QList<Warehouse> _warehouses;
};

#endif // WAREHOUSEMANAGER_H
