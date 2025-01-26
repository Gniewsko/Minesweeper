#include"generuj.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void generuj(int **T)
{
    int ile_zostalo = miny; //ile min pozostalo do rozstawienia na polu minowym
    srand(time(NULL));

    int mina_x; // wspolrzedna x potencjalnej miny
    int mina_y; // wspolrzedna y potencjalnej miny

    while(ile_zostalo != 0)
    {  
        mina_y = rand() % d;
        mina_x = rand() % s;

        if(T[mina_y][mina_x] != -1 && (mina_y != dp && mina_x != sp))
        {
            T[mina_y][mina_x] = -1;
            ile_zostalo--;
        }
    }
}