#include "warehousemanager.h"

#include "src/utils/macro.h"

WarehouseManager::WarehouseManager() :
    _warehouses()
{
}

Warehouse *WarehouseManager::get_closest_having(int item_id, int item_qty, Drone *drone)
{
    // find closest warehouse having item
    int min_dist = Warehouse::MAX_DIST();
    Warehouse * closest = NULL;
    for(int i = 0; i < _warehouses.count(); ++i)
    {   // if warehouse contains the item
        if(_warehouses[i].contains(item_id, item_qty))
        {   // if distance to drone is min
            int dist = drone->distance_to(_warehouses[i].pos());
            if(dist < min_dist)
            {   min_dist = dist;
                closest = &(_warehouses[i]);
            }
        }
    }
    TRACE("WarehouseManager","get_closest_having",QString("warehouse(id=%1) is the closest having item(id=%2,required_qty=%3,stock_qty=%4)")
            .arg(QString::number(closest->id()),
                 QString::number(item_id),
                 QString::number(item_qty),
                 QString::number(closest->quantity(item_id)))
            .toStdString());
    return closest;
}

void WarehouseManager::add(int id, QPoint pos, QVector<int> items)
{
    _warehouses.push_back(Warehouse(id, pos, items));
}

QPoint WarehouseManager::drones_origin()
{
    QPoint pos;
    if(_warehouses.count() > 0)
    {   pos = _warehouses.first().pos();
    }
    return pos;
}

QString WarehouseManager::to_string() const
{
    QString warehouse_list("\n");
    for(QList<Warehouse>::const_iterator it = _warehouses.begin(); it != _warehouses.end(); ++it)
    {   warehouse_list += it->to_string() + '\n';
    }
    return warehouse_list;
}

