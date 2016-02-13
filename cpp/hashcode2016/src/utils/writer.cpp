#include "writer.h"
#include "macro.h"

#include <QFile>

void Writer::write(QString filename, DroneManager &dm)
{
    QFile f(filename);
    if(f.open(QIODevice::WriteOnly))
    {   f.write(dm.commands());
    }
    else
    {   ERROR("Writer","write","can't open file in readonly mode !");
    }
}
