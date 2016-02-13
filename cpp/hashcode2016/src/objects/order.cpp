#include "order.h"
#include "warehouse.h"
#include "src/utils/utils.h"
#include "src/utils/macro.h"

Order::Order(int id, QPoint pos, int total_item_count, QVector<int> items_required) :
    _id(id),
    _state(UNHANDLED),
    _pos(pos),
    _total_item_count(total_item_count),
    _items_required(items_required),
    _items_loaded(items_required.size(), 0)
{
}

Item Order::item_left()
{
    Item item;
    item.valid = false;
    for(int i = 0; i < Warehouse::PRODUCT_COUNT(); ++i)
    {   int diff = _items_required[i] - _items_loaded[i];
        if(diff > 0) {
            item.id = i;
            item.qty = diff;
            item.valid = true;
            TRACE("Order","item_left",QString("(id=%1) need item(id=%2,qty=%3)")
                  .arg(QString::number(_id),
                       QString::number(item.id),
                       QString::number(item.qty))
                  .toStdString());
            break;
        }
    }
    return item;
}

void Order::cancel()
{
    TRACE("Order","cancel",QString("(id=%1,state=TERMINATED)").arg(_id).toStdString());
    _state = TERMINATED;
}

void Order::loaded(int item_id, int item_qty)
{
    TRACE("Order","loaded",QString("(id=%1,state=INPROGRESS)").arg(_id).toStdString());
    _state = INPROGRESS;
    _items_loaded[item_id] += item_qty;
}

void Order::retrieve_items(Drone *d)
{
    for(int i = 0; i < Warehouse::PRODUCT_COUNT(); ++i)
    {   // if items loaded for id 'i'
        if(_items_loaded[i] > 0)
        {   int real_pick = d->pick(_id, i, _items_loaded[i]);
            // remove retrieved items from items loaded and items required
            _items_loaded[i] -= real_pick;
            _items_required[i] -= real_pick;
        }
    }
    // update order state,
    // if no more item required
    if(_items_required.count(0) == Warehouse::PRODUCT_COUNT())
    {   TRACE("Order","retreive_items",QString("(id=%1,state=TERMINATED)").arg(_id).toStdString());
        _state = TERMINATED;
    }
    else
    {   TRACE("Order","retreive_items",QString("(id=%1,state=UNHANDLED)").arg(_id).toStdString());
        _state= UNHANDLED;
    }
}

QString Order::to_string() const
{
    return QString("order(id=%1,pos=%2,total=%3,items=%4,loaded=%5)").arg(
                QString::number(_id),
                Utils::point_to_str(_pos),
                QString::number(_total_item_count),
                Utils::vect_to_str(_items_required),
                Utils::vect_to_str(_items_loaded));
}
