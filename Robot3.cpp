#include "Robot3.h"
#include <cstring>
#include <cmath>
//intinte 1
//inapoi 2
//in jos 3
//in sus 4
void Robot3::Move(int finalRow, int finalColumn, const Map &H)
{
    ///daca destinatia finala e in raza lui de actiune, atunci robotul o sa se indrepte spre ea
    if(abs(finalRow-Row) <=4 && abs(finalColumn-Column)<=4)
    {
        H.matrix[Row][Column]=10;   ///actualizez pozitia robotului, pentru afisare
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
        H.matrix[Row][Column]=10;
        ///Robotul parcurge in spirala matricea
        if(mode%2==0)
        {
            if(mode%4==0 && Column<H.m-spireColumnRight)   ///linia de sus
            {
                Column++;
                return;
            }
            else if(mode%4==2 && Column>1+spireColumnLeft)    ///linia de jos
            {
                Column--;
                return;
            }
            H.matrix[Row][Column]=10;
            if(Column==H.m-spireColumnRight )
            {
                mode++;
                spireRowUp++;            ///am terminat un rand in partea de sus; parcurgem pana la H.n-spireRowUp
            }
            if(Column==1+spireColumnLeft)
            {
                mode++;
                spireRowDown++;     ///am terminat un rand in partea de jos; parcurgem pana la H.n-spireRowDown
            }
        }
        H.matrix[Row][Column]=10;
    }
    if(mode%2==1)      ///coloana din dreapta

    {
        if(mode%4==1 && Row<H.n-spireRowDown)
        {
            Row++;
            return;
        }
        else if(mode%4==3 && Row>1+spireRowUp)    ///coloana din stanga
        {
            Row--;
            return;
        }
        if(Row==H.n-spireRowDown )
        {
            mode++;
            spireColumnRight++;    ///am terminat o coloana in partea dreapta; parcurgem pana la H.m-spireColumnRight
        }
        if(Row==1+spireRowUp)
        {
            mode++;
            spireColumnLeft++; ///am terminat un rand in partea stanga; parcurgem de la H.m-spireColumnLeft
        }
        H.matrix[Row][Column]=10;

    }
}
}

void Robot3::EffectItem(int x, int y, Map & H, char *message)
{
    if(H.matrix[x][y]!=3)
        strcpy(message, "Ai gasit un item, insa Robotul tau nu il poate folosi!\n");
    else
    {
        strcpy(message,"Ai gasit un item! Acesta te-a teleportat direct la destinatia finala\n");
        H.matrix[x][y]=0;
        this->Row=H.finalRow;
        this->Column=H.finalColumn;
    }
}
