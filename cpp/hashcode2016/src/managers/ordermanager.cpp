#include "ordermanager.h"
#include <algorithm>

OrderManager::OrderManager()
{}

Order *OrderManager::next_unhandled_order()
{
    Order * order = NULL;
    for(QList<Order>::iterator it = _orders.begin(); it != _orders.end(); ++it)
    {   if(it->state() == Order::UNHANDLED)
        {   order = &(*it);
            break;
        }
    }
    return order;
}


void OrderManager::add(int id, QPoint pos, int total_item_count, QVector<int> items_required)
{
    _orders.push_back(Order(id, pos, total_item_count, items_required));
}

// define operator < for Order class to be able to use std::sort algorithm
bool operator<(const Order & o1, const Order & o2)
{
    return o1.total_item_count() < o2.total_item_count();
}
void OrderManager::sort()
{   // No Qt equivalent for this function
    std::sort(_orders.begin(), _orders.end(), std::less<Order>());
}

QString OrderManager::to_string() const
{
    QString order_list("\n");
    for(QList<Order>::const_iterator it = _orders.begin(); it != _orders.end(); ++it)
    {   order_list += it->to_string() + '\n';
    }
    return order_list;
}
