#ifndef MAP_H
#define MAP_H
#include <fstream>
using namespace std;
class Robot;
class Map
{
private:
    int n;                             ///dimensiunile matricei
    int m;
    int **matrix;                     ///harta pe care se deplaseaza Robotul
    int finalRow,finalColumn;        ///destinatia Robotului
    int numberItems,numberTraps;
    Robot *A;                       ///pointer catre un obiect de tip robot
    int numberRound;                ///numarul de runde pe care le-a avut Robotul
public:
    friend class Robot1;
    friend class Robot2;
    friend class Robot3;
    Map();                         ///constructor fara parametri
    Map(int, int);                 ///constructor cu parametri
    ~Map();                        ///destructor
    friend ifstream & operator >> (ifstream &,Map &);
    friend ofstream & operator << (ofstream &, const Map &);
    void Simulate(Robot &A);       ///metoda prin care simulam regulile jocului
    void Update(Robot &A);        ///metoda prin care reactualizam pozitia robotului
    void DisplayGameRules();     ///In consola se vor explica regulile jocului
};

#endif // MAP_H
