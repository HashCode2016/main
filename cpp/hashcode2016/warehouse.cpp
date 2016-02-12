#include "warehouse.h"
#include "macro.h"

int Warehouse::_PRODUCT_COUNT = 0;
QVector<int> Warehouse::_PRODUCTS_WEIGHT = QVector<int>();

Warehouse::Warehouse(int id, QPoint pos, QVector<int> items) :
    _id(id),
    _pos(pos),
    _items(items)
{
}

bool Warehouse::pick(int item_id, int item_qty)
{
    if(_items[item_id] < item_qty)
    {   ERROR("Pas assez de produit dans la warehouse %1");
        return false;
    }
    _items[item_id] -= item_qty;
    return true;
}

int Warehouse::PRODUCT_COUNT(int PRODUCT_COUNT)
{   if(PRODUCT_COUNT > 0) {
        _PRODUCT_COUNT = PRODUCT_COUNT;
    }
    return _PRODUCT_COUNT;
}

int Warehouse::PRODUCTS_WEIGHT(int id, QVector<int> PRODUCTS_WEIGHT)
{   if(PRODUCTS_WEIGHT.count() > 0) {
        _PRODUCTS_WEIGHT = PRODUCTS_WEIGHT;
    }
    if(id > 0 && id < _PRODUCTS_WEIGHT.count())
    {   return _PRODUCTS_WEIGHT[id];
    }
    return -1;
}
