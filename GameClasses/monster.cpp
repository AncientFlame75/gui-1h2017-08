#include "monster.h"

Monster::Monster(QVector2D position, float r, QString *path):
    MovingObject(position,r)
{
    this->path=path;
}
