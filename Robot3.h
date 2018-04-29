#ifndef ROBOT3_H
#define ROBOT3_H

#include "Robot.h"

class Robot3 : public Robot
{
private:
    int spireColumnLeft,spireColumnRight,spireRowDown,spireRowUp,mode;
public:
    void SetRobo() {spireColumnLeft=spireColumnRight=spireRowDown=spireRowUp=mode=0;}
    void Move(int, int, const Map &);
    void EffectItem(int, int, Map &, char *);
};

#endif // ROBOT3_H
