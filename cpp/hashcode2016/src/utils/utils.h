#ifndef UTILS_H
#define UTILS_H

#include <QVector>
#include <QString>
#include <QPoint>

class Utils
{
public:
    static QString point_to_str(const QPoint & p);
    static QString vect_to_str(const QVector<int> & v);

private:
    Utils(){}
    Q_DISABLE_COPY(Utils)
};

#endif // UTILS_H
