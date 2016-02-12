#ifndef ORDER_H
#define ORDER_H

#include <QPoint>
#include <QVector>

typedef struct {
    bool valid;
    int id;
    int qty;
} ItemLeft;

class Order
{
public:
    enum State {
        UNHANDLED,
        INPROGRESS,
        TERMINATED
    };

    Order(int id, QPoint pos, QVector<int> items_required);

    inline State state() { return _state; }
    inline QPoint pos() { return _pos; }

    ItemLeft item_left();
    void cancel();
    void loaded(int item_id, int item_qty);
    void delivered(int item_id, int item_qty);

private:
    int _id;
    State _state;
    QPoint _pos;
    QVector<int> _items_required;
    QVector<int> _items_loaded;
};

#endif // ORDER_H
