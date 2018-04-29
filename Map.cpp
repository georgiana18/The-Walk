#include "Map.h"
#include <iostream>
#include <new>
#include <cstdlib>
#include <bits/stdc++.h>
#include "Robot.h"
using namespace std;
ofstream out("out");
Map::Map()
{
    ///dimensiunile initiale sunt 0
    m=0;
    n=0;
    numberRound=1;
}

Map::Map(int x, int y)
{
    n=x;
    m=y;

    try
    {
        matrix=new int*[n+2];
        for(int i=0; i<=n+1; i++)
            matrix[i]=new int[m+2];
    }
    catch (bad_alloc xa)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }

}
Map::~Map()
{
    for(int i=0; i<=n+1; i++)
        delete[]matrix[i];
    delete[]matrix;
}

ifstream & operator >> (ifstream & in, Map &H)
{
    in>>H.n>>H.m;   ///citim dimensiunile matricei
    try             ///alocam memorie conform dimensiunii citite
    {
        H.matrix=new int*[H.n+2];
        for(int i=0; i<=H.n+1; i++)
            H.matrix[i]=new int[H.m+2];
    }
    catch (bad_alloc xa)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }

    for(int i=1; i<=H.n; i++)
        for(int j=1; j<=H.m; j++)
            H.matrix[i][j]=0;      ///valoarea 0 reprezinta o zona libera, in care robotul poate merge
    in>>H.numberItems;                ///numarul de iteme de pe harta
    for(int i=0; i<H.numberItems; i++)
    {
        int pozx,pozy,a;            ///Avem itemuri de 2 tipuri (reprezentate cu 1, 2 si 3 pe harta)
        in>>pozx>>pozy>>a;          ///Fiecare corespunde unui tip de robot
        H.matrix[pozx][pozy]=a;
    }
    in>>H.numberTraps;
    for(int i=0; i<H.numberTraps; i++)
    {
        int pozx,pozy;
        in>>pozx>>pozy;
        H.matrix[pozx][pozy]=-1;    ///pe harta reprezentam capcanele cu -1
    }
    in>>H.finalRow>>H.finalColumn;
    return in;
}

ofstream & operator <<(ofstream & out,const Map &H)
{
    out<<"\n";
    for(int i=1; i<=H.n; i++)
    {
        for(int j=1; j<=H.m; j++)
        {
            if(H.matrix[i][j]==10)
                out<<"R ";      ///Drumul Robotului va fi marcat prin litera R
            else if(i==H.finalRow && j== H.finalColumn)
                out<<"D ";    ///cu D reprezentam la afisare destinatia robotului
            else if(H.matrix[i][j]==-1)
                out<<"X ";              ///X pe harta inseamna capcana
            else
                out<<H.matrix[i][j]<<" ";             ///vom aveam 0 pt zone libere, sau 1, 2 ,3 pt itemuri nefolosite inca
        }
        out<<"\n";
    }
    return out;
}
void Map::Update(Robot &A)
{
    A.Move(finalRow,finalColumn, *this);   ///functia Move va deplasa robotul cu 1 pozitie
}
void Map::Simulate(Robot &A)
{
    bool trap=0;
    matrix[A.Row][A.Column]=10;     ///am dat o valoare arbitrara prin care sa reprezint pozitia robotului pe harta
    char *message =new char[100];     ///se trimite un mesaj in unele cazuri
    while( !(A.Row==finalRow && A.Column==finalColumn))     ///pana cand nu am ajuns la destinatie
    {
        if(trap==true)                                  ///daca robotul meu a cazut in capcana
        {
            out<<"Round "<<numberRound<<" : Robotul sta o tura!\n\n";     ///va sta o tura
            trap=false;                                                  ///apoi va iesi din capcana
            numberRound++;                                               ///acesta a pierdut o runda
        }
        out<<"Round "<<numberRound<<" : Pozitia Robotului: "<<A.Row<<" "<<A.Column<<"\n";     ///afisam pozitia actuala a robotului
        Update(A);                                              ///reactualizam pozitia robotului
        out<<*this;                                             ///afisam harta
        if(matrix[A.Row][A.Column]==-1)                         ///daca noua pozitie e o capana
        {
            out<<"Robotul a cazut in capcana!";                ///afisam mesajul
            trap=true;                                         ///si actualizam variabila trap, ca sa stim ca stam o tura
        }
        if(matrix[A.Row][A.Column]>0 && matrix[A.Row][A.Column]!=10)      ///daca am dat de o valoare pozitiva dar diferita de 10(adica poz robot)
        {
            A.EffectItem(A.Row, A.Column, *this, message);           ///inseamna ca am gasit un item, si verificam daca il putem folosi
            out<<message;                                           ///afisam mesajul ca sa stim daca l-am folosit sau nu
        }
        out<<"\n\n";
        numberRound++;                                           ///incrementam numarul rundei

    }
    out<<"Round "<<numberRound<<" : Pozitia Robotului: "<<A.Row<<" "<<A.Column<<"\n";
    matrix[A.Row][A.Column]=10;
    out<<"Robotul a ajuns la destinatie!\n";
    out<<*this;
    delete []message;
}
void Map::DisplayGameRules()
{
    cout<<"Avem o harta pe care se afla un Robot (coltul din stanga sus).\n";
    cout<<"Pe harta exista o locatie in care Robotul trebuie sa ajunga.\n";
    cout<<"Pe harta exista capcane. Daca Robotul cade in capcana, va sta o tura.\n";
    cout<<"Pe harta exista si itemuri, care pot ajuta Robotul daca sunt compatibili.\n";
    cout<<"Avem la dispozitie 3 tipuri de Robot, ceea ce ii diferentiaza este modul de a se deplasa.\n";
    cout<<"Robotul 1 se deplaseaza pe linie, in mod serpuit (stanga->dreapta apoi dreapta->stanga).\n";
    cout<<"Robotul 2 se deplaseaza pe coloana in mod serpuit (sus->jos apoi jos->sus).\n";
    cout<<"Robotul 3 se deplaseaza in spirala, in sensul acelor de ceas.\n";
    cout<<"Robotul vede ce se afla in jurul lui pe o distanta de 4 fata de pozitia lui curenta.\n";
    cout<<"Daca in raza lui de actiune se vede locatia finala, atunci robotul se va deplasa spre ea indiferent de modul lui de deplasare specific.\n";
    cout<<"Robotul 1 are un item anti-capcane. Prin urmare, daca il gaseste, el va ajunge mai repede la destinatie.\n";
    cout<<"Robotul 2 are un item care ii permite sa se mai deplaseze cu o pozitie in acceeasi runda.\n";
    cout<<"Robotul 3 are un item de teleportare catre destinatia finala.\n";
    cout<<"\n";
}

