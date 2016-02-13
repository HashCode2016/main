#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QPoint>
#include <QVector>
#include <QSize>

class Warehouse
{
public:
    Warehouse(int id, QPoint pos, QVector<int> items);

    bool pick(int item_id, int item_qty);
    bool contains(int item_id, int item_qty);

    inline int id() const { return _id; }
    inline QPoint pos() const { return _pos; }

    /**
     * @brief to_string
     *      Debug function
     * @return
     */
    QString to_string() const;

    static int PRODUCT_COUNT(int PRODUCT_COUNT = -1);
    static int PRODUCTS_WEIGHT(int id = -1, QVector<int> PRODUCTS_WEIGHT = QVector<int>());
    static QSize MAP_SIZE(QSize size = QSize());
    static int MAX_DIST();

private:
    int _id;
    QPoint _pos;
    QVector<int> _items;

    static int _PRODUCT_COUNT;
    static QVector<int> _PRODUCTS_WEIGHT;
    static QSize _MAP_SIZE;
    static int _MAX_DIST;
};

#endif // WAREHOUSE_H
