#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "src/objects/order.h"

class OrderManager
{
public:
    OrderManager();

    inline int count() const { return _orders.count(); }

    Order * next_unhandled_order();
    void add(int id, QPoint pos, int total_item_count, QVector<int> items_required);
    void sort();

    QString to_string() const;

private:
    QList<Order> _orders;
};

#endif // ORDERMANAGER_H
