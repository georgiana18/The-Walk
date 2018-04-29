#ifndef ROBOT1_H
#define ROBOT1_H

#include "Robot.h"


class Robot1 : public Robot
{
public:
    void Move(int,int, const Map&);    ///Robot1 se deplaseaza pe linii
    void EffectItem(int, int, Map&, char *);
};

#endif // ROBOT1_H
