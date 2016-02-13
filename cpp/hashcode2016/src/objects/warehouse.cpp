#include "warehouse.h"
#include "src/utils/macro.h"
#include "src/utils/utils.h"
#include <QtMath>

int Warehouse::_PRODUCT_COUNT = 0;
QVector<int> Warehouse::_PRODUCTS_WEIGHT = QVector<int>();
QSize Warehouse::_MAP_SIZE = QSize();
int Warehouse::_MAX_DIST = 0;

Warehouse::Warehouse(int id, QPoint pos, QVector<int> items) :
    _id(id),
    _pos(pos),
    _items(items)
{
}

bool Warehouse::pick(int item_id, int item_qty)
{
    if(_items[item_id] < item_qty)
    {   ERROR("Warehouse","pick",QString("(id=%1) not enough item(id=%2,qty=%3)")
              .arg(QString::number(_id),
                   QString::number(item_id),
                   QString::number(item_qty))
              .toStdString());
        return false;
    }
    _items[item_id] -= item_qty;
    return true;
}

bool Warehouse::contains(int item_id, int item_qty)
{
    return (_items[item_id] >= item_qty);
}

QString Warehouse::to_string() const
{
    return QString("warehouse(id=%1,pos=%2,items=%3)").arg(QString::number(_id), Utils::point_to_str(_pos), Utils::vect_to_str(_items));
}

int Warehouse::PRODUCT_COUNT(int PRODUCT_COUNT)
{
    if(PRODUCT_COUNT > 0) {
        _PRODUCT_COUNT = PRODUCT_COUNT;
    }
    return _PRODUCT_COUNT;
}

int Warehouse::PRODUCTS_WEIGHT(int id, QVector<int> PRODUCTS_WEIGHT)
{
    if(PRODUCTS_WEIGHT.count() > 0) {
        _PRODUCTS_WEIGHT = PRODUCTS_WEIGHT;
    }
    if(id >= 0 && id < _PRODUCTS_WEIGHT.count())
    {   return _PRODUCTS_WEIGHT[id];
    }
    return -1;
}

QSize Warehouse::MAP_SIZE(QSize size)
{
    if(size.isValid())
    {   _MAP_SIZE = size;
        _MAX_DIST = qCeil(qSqrt(qPow(size.width(),2)+qPow(size.height(),2))); // compute max dist on the map
    }
    return _MAP_SIZE;
}

int Warehouse::MAX_DIST()
{
    return _MAX_DIST;
}
