#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "order.h"

class OrderManager
{
public:
    OrderManager();

    Order * next_unhandled_order();

private:
    QVector<Order> _orders;
};

#endif // ORDERMANAGER_H
