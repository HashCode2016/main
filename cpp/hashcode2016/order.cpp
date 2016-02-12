#include "order.h"
#include "warehouse.h"

Order::Order(int id, QPoint pos, QVector<int> items_required) :
    _id(id),
    _state(UNHANDLED),
    _pos(pos),
    _items_required(items_required),
    _items_loaded(items_required.size(), 0)
{
}

/**
 * @brief Order::item_left
 * @return le premier item dont il reste des elements a livrer qui ne sont pas chargés
 */
ItemLeft Order::item_left()
{
    ItemLeft item;
    item.valid = false;
    for(int i = 0; i < Warehouse::PRODUCT_COUNT(); ++i)
    {   int diff = _items_required[i] - _items_loaded[i];
        if(diff > 0) {
            item.id = i;
            item.qty = diff;
            item.valid = true;
            break;
        }
    }
    return item;
}

/**
 * @brief Order::cancel
 *     Annulation de la commande
 */
void Order::cancel()
{   _state = TERMINATED;
}

void Order::loaded(int item_id, int item_qty)
{
    _items_loaded[item_id] += item_qty;
}

void Order::delivered(int item_id, int item_qty)
{
    _items_loaded[item_id] -= item_qty;
    _items_required[item_id] -= item_qty;
}
