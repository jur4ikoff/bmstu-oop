#include "cabin.hpp"

Cabin::Cabin(cabin_id_t id, QObject *parent)
    : QObject(parent), _id(id) //, _cur_floor(START_FLOOR), _state(BOARDING_FINISHED), _doors(id)
{
    qDebug() << "Cabin INIT";
}

Cabin::~Cabin()
{
}
