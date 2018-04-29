#include <fstream>
#include <iostream>
#include "Map.h"
#include "Robot.h"
#include "Robot1.h"
#include "Robot2.h"
#include "Robot3.h"
using namespace std;
ifstream fin("in");
ofstream fout("out");
int main()
{

    Map H;
    fin>>H;
    H.DisplayGameRules();
    int Type;
    ///meniu de alegere al tipului robotului
    cout<<"Alege Robotul (1/2/3) : ";
    cin>>Type;
    Robot *p;
    if(Type==1)
    {
        Robot1 A;
        p=&A;
    }
    if(Type==2)
    {
        Robot2 B;
        p=&B;
    }
    if(Type==3)
    {
        Robot3 C;
        p=&C;
        C.SetRobo();
    }
    H.Simulate(*p);
    return 0;
}
