#ifndef DRONE_H
#define DRONE_H

#include <QPoint>
#include <QVector>
#include "warehouse.h"
#include "order.h"

class Drone
{
public:
    enum State {
        AVAILABLE,
        WORKING
    };

    Drone(int id, QPoint pos, int nb_types);

    static int MAX_WEIGHT(int MAX_WEIGHT = -1);
    static int MAX_TURN(int MAX_TURN = -1);

    // -- commands functions
    void load(ItemLeft item_left, Warehouse * w, Order * o);
    void unload(Warehouse * w, int item_id, int item_qty);
    void deliver(Order * o);
    void wait();
    // -- simu functions
    void next_turn();
    // -- data functions
    bool is_full(ItemLeft item_left);

private:
    void _move_to(QPoint p);

private:
    int _id;
    int _current_weight;
    int _workload; // in simu turns
    State _state;
    QPoint _pos;
    QVector<int> _items;

    static int _MAX_WEIGHT;
    static int _MAX_TURN;
};

#endif // DRONE_H
