#ifndef ORDER_H
#define ORDER_H

#include <QPoint>
#include <QVector>
#include "drone.h"
#include "src/struct.h"

class Order
{
public:
    enum State {
        UNHANDLED,
        INPROGRESS,
        TERMINATED
    };

    Order(int id, QPoint pos, int total_item_count, QVector<int> items_required);

    inline int id() const { return _id; }
    inline State state() const { return _state; }
    inline QPoint pos() const { return _pos; }
    inline int total_item_count() const { return _total_item_count; }

    /**
     * @brief item
     * @return le premier item dont il reste des elements a livrer qui ne sont pas chargés
     */
    Item item_left();
    /**
     * @brief cancel
     *     Annulation de la commande
     */
    void cancel();
    /**
     * @brief loaded
     * @param item_id
     * @param item_qty
     */
    void loaded(int item_id, int item_qty);
    /**
     * @brief delivered
     * @param item_id
     * @param item_qty
     */
    void retrieve_items(Drone * d);

    QString to_string() const;

private:
    int _id;
    State _state;
    QPoint _pos;
    int _total_item_count;
    QVector<int> _items_required;
    QVector<int> _items_loaded;
};

#endif // ORDER_H
