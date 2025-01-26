#include<stdio.h>
#include<stdlib.h>
#include "generuj.h"
#include "menu.h"
#include "pola.h"
#include "gra.h"

int d = 2;
int s = 2;
int miny = 0;
int sp = -1;
int dp = -1;
int wybor = 0;
int czy_plik = 0;

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        menu();

        int **T = malloc(d * sizeof(int *));

        for(int i = 0; i < d; i++) //przypisywanie pamieci do tablicy
        {
            T[i] = malloc(s * sizeof(int));
        }

        for(int i = 0; i < d; i++) //uzupelnienie tablicy "0"
        {
            for(int j = 0; j < s; j++)
            {
                T[i][j] = 0;
            } 
        }

        generuj(T);
        pola(T);

        gra(T);

        for(int i = 0; i < d; i++)
        {
            free(T[i]);
        }

        free(T);
    }
    else
    {
        printf("wczytano wlasny plik z plansza i ruchami\n");
        czy_plik = 1;

        if(czy_plik == 1)
        {
            int minys = 0;
            FILE *file = fopen(argv[1], "r");
            fscanf(file, "%d %d", &s, &d);

            int **T = malloc(s * sizeof(int *));

            for(int i = 0; i < d; i++)
            {
                T[i] = malloc(s * sizeof(int));
            }

            for (int i = 0; i < d; i++) 
            {
                for (int j = 0; j < s; j++) 
                {
                    fscanf(file, "%d", &T[i][j]);

                    if(T[i][j] == -1)
                    {
                        minys++;
                    }
                }
            }

        int x = 0;
        int y = 0;
        char akcja = 'd';
        int kroki = 0;
        int punkty = 0;

            while (fscanf(file, " %c %d %d", &akcja, &x, &y) != EOF) 
            {
                if (akcja == 'r') 
                {
                    // Odkrywanie pola
                    if (T[y - 1][x - 1] == -1) 
                    {
                        punkty += (d * s - kroki);
                        printf("Znaleziono mine w ruchu ( x - %d, y - %d)!\n", x, y);
                        printf("do tego czasu wykonano %d poprawnych odkryc i zdobyto %d punktow\n", kroki, punkty);
                        printf("Stan gry (wygrana): 0 \n");
                        break;
                    } 
                    else 
                    {
                        kroki++;
                    }
                } 
                else if (akcja == 'f') 
                {
                    // Ustawienie flagi
                    // Nie mam pojecia jak wyliczac te punkty z tego co rozumiem to punkty to liczba odkrytych pol ktore nie sa minami * poziom trudnosci
                }

                // Jesli gra zostala zakonczona
                if(kroki == (d * s - minys)) 
                {  
                    punkty += (kroki);
                    printf("Gra zakonczona sukcesem! Zdobyto %d punktow, wykonano %d poprawnych odkryc \n", kroki, punkty);
                    printf("Stan gry (wygrana): 1 \n");
                    break;
                }
            }

            fclose(file);

            for(int i = 0; i < d; i++)
            {
                    free(T[i]);
            }

            free(T);
        }
    }
}