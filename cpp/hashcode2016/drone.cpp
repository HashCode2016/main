#include "drone.h"
#include "warehouse.h"

#include <QtMath>

int Drone::_MAX_TURN = 0;
int Drone::_MAX_WEIGHT = 0;

Drone::Drone(int id, QPoint pos, int nb_types) :
    _id(id),
    _current_weight(0),
    _workload(0), // in simu turns
    _state(AVAILABLE),
    _pos(pos),
    _items(nb_types, 0)
{
}

int Drone::MAX_WEIGHT(int MAX_WEIGHT)
{   if(MAX_WEIGHT > 0)
    {   _MAX_WEIGHT = MAX_WEIGHT;
    }
    return _MAX_WEIGHT;
}

int Drone::MAX_TURN(int MAX_TURN)
{   if(MAX_TURN > 0)
    {   _MAX_TURN = MAX_TURN;
    }
    return _MAX_TURN;
}

void Drone::load(ItemLeft item_left, Warehouse *w, Order *o)
{
    _state = WORKING;
    // move drone to warehouse
    _move_to(w->pos());
    // load operation takes one more turn
    _workload++;
    // remove items from warehouse
    w->pick(item_left.id, item_left.qty);
    // update current weight
    _current_weight += Warehouse::PRODUCTS_WEIGHT(item_left.id) * item_left.qty;
    // add items to drone
    _items[item_left.id] += item_left.qty;
    // add items to order
    o->loaded(item_left.id, item_left.qty);
}

void Drone::unload(Warehouse *w, int item_id, int item_qty)
{
    _state = WORKING;
    /// \todo implement unload
}

void Drone::deliver(Order * o)
{
    _state = WORKING;
    // move drone to delivery point
    _move_to(o->pos());
    // suppose that drone has only one command into content
    for(int i = 0; i < Warehouse::PRODUCT_COUNT(); ++i)
    {   if(_items[i] > 0)
        {   // increase workload
            _workload++;
            // notify order that items are delivered
            o->delivered(i, _items[i]); // il faudrait peut être mieux demander à l'objet commande de se servir dans le drone d'un point de vue conceptuel
            // decrease weight
            _current_weight -= Warehouse::PRODUCTS_WEIGHT(i) * _items[i];
            // remove items from drone
            _items[i] == 0;
        }
    }
}

void Drone::wait()
{
    _state = AVAILABLE;
    /// \todo implement wait
}

void Drone::next_turn()
{
    // update workload
    _workload--;
    // if workload is lower or equal to 0
    if(_workload <= 0) {
        // drone is available
        _state = AVAILABLE;
    }
}

bool Drone::is_full(ItemLeft item_left)
{
    bool full(false);
    if(item_left.valid && Warehouse::PRODUCTS_WEIGHT(item_left.id) * item_left.qty + _current_weight > _MAX_WEIGHT)
    {   full = true;
    }
    return full;
}

void Drone::_move_to(QPoint p)
{
    _workload += qCeil(qSqrt(qPow(_pos.x()-p.x(), 2)+qPow(_pos.y()-p.y(), 2)));
    _pos.setX(p.x());
    _pos.setY(p.y());
}

