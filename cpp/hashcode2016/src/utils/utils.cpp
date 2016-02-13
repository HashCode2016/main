#include "utils.h"

QString Utils::point_to_str(const QPoint &p)
{
    return QString("[%1,%2]").arg(QString::number(p.x()), QString::number(p.y()));
}

QString Utils::vect_to_str(const QVector<int> &v)
{
    QStringList l;
    for(int i=0; i < v.count(); ++i)
    {   l << QString::number(v[i]);
    }
    return QString("[%1]").arg(l.join(','));
}

