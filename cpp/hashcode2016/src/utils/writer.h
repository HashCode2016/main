#ifndef WRITER_H
#define WRITER_H

#include "src/managers/dronemanager.h"

class Writer
{
public:
    static void write(QString filename, DroneManager &dm);

private:
    Writer(){}
    Q_DISABLE_COPY(Writer)
};

#endif // WRITER_H
