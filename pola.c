#include"pola.h"
#include<stdio.h>
#include<stdlib.h>

void pola(int **T)
{
    for(int i = 0; i < d; i++)  // Iteracja po wierszach
    {
        for(int j = 0; j < s; j++)  // Iteracja po kolumnach
        {
            if(T[i][j] == -1)  // Jezeli jest mina
            {
                // Sprawdzanie 8 sasiednich komorek (w tym skosy)
                for(int di = -1; di <= 1; di++)  // Ruch w poziomie (-1, 0, 1)
                {
                    for(int dj = -1; dj <= 1; dj++)  // Ruch w pionie (-1, 0, 1)
                    {
                        // Pomijamy bieżące pole
                        if(di == 0 && dj == 0) continue;

                        int ni = i + di;
                        int nj = j + dj;

                        // Sprawdzamy, czy indeksy mieszczą się w granicach tablicy
                        if(ni >= 0 && ni < d && nj >= 0 && nj < s)
                        {
                            if(T[ni][nj] != -1)  // Jeśli pole nie jest miną
                            {
                                T[ni][nj]++;  // Zwiększamy liczbę sąsiednich min
                            }
                        }
                    }
                }
            }
        }
    }
}
