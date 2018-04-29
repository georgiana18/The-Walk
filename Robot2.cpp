#include "Robot2.h"
#include <cstring>
#include <cmath>
void Robot2::Move(int finalRow,int finalColumn, const Map &H)
{
    ///daca destinatia finala e in raza lui de actiune, atunci robotul o sa se indrepte spre ea
    if(abs(finalRow-Row) <=4 && abs(finalColumn-Column)<=4)
    {
        H.matrix[Row][Column]=10;     ///actualizez pozitia robotului pe harta (pt afisare)
        ///poate merge pe linie, coloana sau diagonala, doar sa ajunga cat mai repde
        if(finalRow<Row)
            Row--;
        else if(finalRow>Row)
            Row++;
        if(finalColumn<Column)
            Column--;
        else if(finalColumn>Column)
            Column++;
    }
    else
    {
        ///altfel merge doar pe coloana
        H.matrix[Row][Column]=10;
        if(Column%2==1 && Row<H.n)       ///daca Robotul e pe coloana impara, si inca nu este la capatul de jos al acesteia
        {
            Row++;       ///trecem pe randul urmator
            return;
        }
        else if(Column%2==0 && Row>1)      ///daca Robotul e pe coloana para si inca nu este la capatul de sus al acesteia
        {
            Row--;                     ///trecem pe randul de sus
            return;
        }
        H.matrix[Row][Column]=10;
        ///altfel schimbam coloana
        if(Row==H.n && Column%2==1)
        {
            Column++;
        }
        if(Row==1 && Column%2==0)
        {
            Column++;
        }
        H.matrix[Row][Column]=10;
    }
}

void Robot2::EffectItem(int x, int y, Map &H, char *message)
{
    if(H.matrix[x][y]!=2)
    {
        strcpy(message,"Ai gasit un item dar nu este potrivit pentru Robotul tau!\n");
    }
    if(H.matrix[x][y]==2)
    {
        strcpy(message,"\nAi gasit un item! Te mai poti deplasa cu inca o pozitie in aceasta runda!\n");
        H.numberRound--;
        H.matrix[x][y]=0;
    }
}
