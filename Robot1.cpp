#include "Robot1.h"
#include "Map.h"
#include <cstring>
#include <cmath>
void Robot1::Move(int finalRow,int finalColumn, const Map&H)
{
    ///daca destinatia finala e in raza lui de actiune, atunci robotul o sa se indrepte spre ea
    if(abs(finalRow-Row) <=4 && abs(finalColumn-Column)<=4)
    {
        H.matrix[Row][Column]=10;
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
        ///altfel isi constiuna drumul cum stie el, pe linie
        H.matrix[Row][Column]=10;
        ///pe linii impare se duce spre dreapta (incrementam numarul coloanei) pana ajungem la capatul liniei
        if(Row%2==1 && Column<H.m)
        {
            Column++;
            return;   ///oprim functia
        }
        else if(Row%2==0 && Column>1)    ///pe linii pare se duce spre stanga (decrementam coloanele) pana ajungem la capatul liniei
        {
            Column--;
            return;     ///oprim functia
        }
        H.matrix[Row][Column]=10;
        ///am ajuns la capatul liniei ori stang ori drept, robotul trece pe linia urmatoare
        if(Column==H.m && Row%2==1)
        {
            Row++;
        }
        if(Column==1 && Row%2==0)
        {
            Row++;
        }
        H.matrix[Row][Column]=10;
    }
}

void Robot1::EffectItem(int x, int y, Map &H, char *message)
{
    if(H.matrix[x][y]!=1)
        strcpy(message,"Ai gasit un item, insa Robotul tau nu il poate folosi!\n");
    else if(H.matrix[x][y]==1)
    {
        int i,j;
        strcpy(message, "Ai gasit un item! De acum Robotul nu va mai cadea in capcana!\n");
        for(i=1; i<=H.n; i++)
            for(j=1; j<=H.m; j++)
                if(H.matrix[i][j]==-1)
                    H.matrix[i][j]=0;
        H.matrix[x][y]=0;
    }
}
