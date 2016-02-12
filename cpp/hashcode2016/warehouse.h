#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QPoint>
#include <QVector>

class Warehouse
{
public:
    Warehouse(int id, QPoint pos, QVector<int> items);

    bool pick(int item_id, int item_qty);

    inline QPoint pos() { return _pos; }

    static int PRODUCT_COUNT(int PRODUCT_COUNT = -1);
    static int PRODUCTS_WEIGHT(int id = -1, QVector<int> PRODUCTS_WEIGHT = QVector<int>());

private:
    int _id;
    QPoint _pos;
    QVector<int> _items;

    static int _PRODUCT_COUNT;
    static QVector<int> _PRODUCTS_WEIGHT;
};

#endif // WAREHOUSE_H
