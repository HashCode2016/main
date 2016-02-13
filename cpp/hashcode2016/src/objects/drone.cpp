#include "drone.h"
#include "order.h"
#include "warehouse.h"
#include "src/utils/macro.h"
#include "src/utils/utils.h"

#include <QtMath>

int Drone::_MAX_TURN = 0;
int Drone::_MAX_WEIGHT = 0;

Drone::Drone(int id, QPoint pos, int nb_types) :
    _id(id),
    _current_weight(0),
    _workload(0), // in simu turns
    _state(AVAILABLE),
    _pos(pos),
    _items(nb_types, 0),
    _commands("")
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

void Drone::load(Item item, Warehouse *w, Order *o)
{
    TRACE("Drone","load",QString("(id=%1,state=WORKING) at warehouse(id=%2) for order(id=%3).")
          .arg(QString::number(_id),QString::number(w->id()),QString::number(o->id()))
          .toStdString());
    _state = WORKING;
    // move drone to warehouse
    _move_to(w->pos());
    // load operation takes one more turn
    _workload++;
    // remove items from warehouse
    w->pick(item.id, item.qty);
    // update current weight
    _current_weight += Warehouse::PRODUCTS_WEIGHT(item.id) * item.qty;
    // add items to drone
    _items[item.id] += item.qty;
    // add items to order
    o->loaded(item.id, item.qty);
    // add command
    _add_command(QString("%1 L %2 %3 %4").arg(
                     QString::number(_id),
                     QString::number(w->id()),
                     QString::number(item.id),
                     QString::number(item.qty)));
}

void Drone::unload(Warehouse *w, int item_id, int item_qty)
{
    _state = WORKING;
    /// \todo implement unload
    ERROR("Drone","unload","called but not implemented !");
}

void Drone::deliver(Order * o)
{
    TRACE("Drone","deliver",QString("(id=%1, state=WORKING) delivering items for order(id=%2).")
          .arg(QString::number(_id),
               QString::number(o->id()))
          .toStdString());
    _state = WORKING;
    // move drone to delivery point
    _move_to(o->pos());
    // notify order that items can be retrieved
    o->retrieve_items(this);
}

void Drone::wait()
{
    _state = AVAILABLE;
    /// \todo implement wait
    ERROR("Drone","wait","called but not implemented !");
}

void Drone::next_turn()
{
    // update workload
    _workload--;
    // if workload is lower or equal to 0
    if(_workload <= 0) {
        // drone is available
        TRACE("Drone","next_turn",QString("(id=%1,state=AVAILABLE)").arg(_id).toStdString());
        _state = AVAILABLE;
    }
}

int Drone::pick(int order_id, int item_id, int item_qty)
{
    int real_qty(0);
    // si le drone possède l'item
    if(_items[item_id] > 0)
    {   // increase workload
        _workload++;
        // la quantité réelle déposée est la quantité minimum entre celle souhaitée et celle que possède le drone
        real_qty = qMin(_items[item_id], item_qty);
        // on enlève cette quantité des items du drone
        _items[item_id] -= real_qty;
        // decrease weight
        _current_weight -= Warehouse::PRODUCTS_WEIGHT(item_id) * real_qty;
        // on génère l'action
        _add_command(QString("%1 D %2 %3 %4").arg(
                         QString::number(_id),
                         QString::number(order_id),
                         QString::number(item_id),
                         QString::number(real_qty)));
        // trace
        TRACE("Drone","pick",QString("(id=%1) order(id=%2) picking item(id=%3,expected_qty=%4,real_qty=%5)")
                  .arg(QString::number(_id),
                       QString::number(order_id),
                       QString::number(item_id),
                       QString::number(item_qty),
                       QString::number(real_qty))
                  .toStdString());
    }
    // on retourne la quantité réelle récupérée par la commande dans le drone
    return real_qty;
}

bool Drone::is_full(Item item)
{
    bool full(false);
    if(item.valid && Warehouse::PRODUCTS_WEIGHT(item.id) * item.qty + _current_weight > _MAX_WEIGHT)
    {   full = true;
    }
    return full;
}

int Drone::distance_to(QPoint p)
{
    return qCeil(qSqrt(qPow(_pos.x()-p.x(), 2)+qPow(_pos.y()-p.y(), 2)));
}

QString Drone::to_string() const
{
    return QString("drone(id=%1,pos=%2,current_weight=%3,workload=%4,items=%5)").arg(
                QString::number(_id),
                Utils::point_to_str(_pos),
                QString::number(_current_weight),
                QString::number(_workload),
                Utils::vect_to_str(_items));
}

void Drone::_move_to(QPoint p)
{
    TRACE("Drone","_move_to",QString("(id=%1) moving from %2 to %3")
          .arg(QString::number(_id),
               Utils::point_to_str(_pos),
               Utils::point_to_str(p))
          .toStdString());
    _workload += distance_to(p);
    _pos.setX(p.x());
    _pos.setY(p.y());
}

void Drone::_add_command(QString command)
{
    _commands += command + '\n';
}

