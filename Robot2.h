#ifndef ROBOT2_H
#define ROBOT2_H
#include "Robot.h"

class Robot2 : public Robot
{
public:
    void Move(int, int, const Map&);           ///Robot2 se deplaseaza pe coloane
    void EffectItem(int,int, Map &, char *);
};

#endif // ROBOT2_H
