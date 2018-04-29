#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>
#include "Map.h"
using namespace std;
class Map;
class Robot                     ///clasa abstracta
{
protected:
    int Row;
    int Column;
public:
    friend class Map;
    Robot() {Row=1; Column=1;};
    int GetRow() const {return Row;}
    int GetColumn() const {return Column;}
    virtual void Move(int,int, const Map&)=0;               ///metoda virtual pura de deplasare a robotuluii
    virtual void EffectItem(int, int, Map&, char *)=0;      ///metoda virtual pura de folosire a itemului
};

#endif // ROBOT_H
