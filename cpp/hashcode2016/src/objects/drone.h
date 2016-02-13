#ifndef DRONE_H
#define DRONE_H

#include <QPoint>
#include <QVector>
#include "warehouse.h"
#include "src/struct.h"

class Order;

class Drone
{
public:
    enum State {
        AVAILABLE,
        WORKING
    };

    Drone(int id, QPoint pos, int nb_types);

    inline int id() const { return _id; }
    inline State state() const { return _state; }
    inline QByteArray commands() const { return _commands; }
    inline int commands_count() const { return _command_counter; }

    // -- commands functions
    void load(int item_id, int item_qty, Warehouse * w, Order * o);
    void unload(Warehouse * w, int item_id, int item_qty);
    void deliver(Order * o);
    void wait();
    // -- simu functions
    void next_turn();
    // -- data functions
    int pick(int order_id, int item_id, int item_qty);
    int max_qty(Item item);

    // -- utils functions
    int distance_to(QPoint p);

    QString to_string() const;

    static int MAX_WEIGHT(int MAX_WEIGHT = -1);
    static int MAX_TURN(int MAX_TURN = -1);

private:
    void _move_to(QPoint p);
    void _add_command(QString command);

private:
    int _id;
    int _current_weight;
    int _workload; // in simu turns
    State _state;
    QPoint _pos;
    QVector<int> _items;
    QByteArray _commands;
    int _command_counter;

    static int _MAX_WEIGHT;
    static int _MAX_TURN;
};

#endif // DRONE_H
