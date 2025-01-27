#include"gra.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int czyll(const char *str) //funkcja sprawdza czy wprowadzona dana jest liczba calkowita
{
    char *sprr;

    strtol(str, &sprr, 10); 

    return (*sprr == '\0');
}

int sprr(const char *a) //funkcja przenosi dana do zmiennej int
{
    if (czyll(a)) 
    {
        return atoi(a);
    }
    return 0;
}

int ilebomb( int **O) //ile jest bomb - miejsc oflagowanych jako bomby
{
    int bomby = miny;

    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < s; j++)
        {
            if(O[i][j] == -1)
            {
                bomby--;
            }
        }
    }

    return bomby;
}

int ilepkt(int **O) //funkcja liczaca na biezaco nasze punkty
{
    int pkt = 0;

    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < s; j++)
        {
            if(O[i][j] == 1)
            {
                pkt++;
            }
        }
    }

    pkt = pkt * wybor;

    return pkt;
}

int koniec(int **O, int **T) //funkcja spradzajaca czy nasza gra sie skonczyla
{
    int odkr = 0;
    int pom = 0;

    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < s; j++)
        {
            if(O[i][j] == 1 || O[i][j] == -1)
            {
                odkr++;
            }

            if(O[i][j] == 1 && T[i][j] == -1)
            {
                pom = -1;
                return pom;
            }
        }
    }

    if(odkr == d*s)
    {
        pom = 1;
    }

    return pom;
}

void odkryj_pole(int **T, int **O, int x, int y) //funkcja odkrywajaca nasze pola
{
    // Sprawdzenie, czy wspolrzedne są w granicach planszy i czy pole jest juz odkryte
    if (x < 0 || x >= d || y < 0 || y >= s || O[x][y] == 1)
    {
        return; // Jesli pole jest poza plansza lub juz odkryte, nic nie rob
    }

    O[x][y] = 1; // Odkryj pole

    // Jesli pole jest puste (brak min w okolicy), odkrywamy sasiednie pola
    if (T[x][y] == 0)
    {
        // Sprawdzamy 8 sasiednich pol
        for (int dx = -1; dx <= 1; dx++) 
        {
            for (int dy = -1; dy <= 1; dy++) 
            {
                int nx = x + dx;
                int ny = y + dy;
                
                // Sprawdzamy, czy sasiednie pole jest w granicach planszy i nie zostalo odkryte
                if (nx >= 0 && nx < d && ny >= 0 && ny < s && O[nx][ny] == 0)
                {
                    odkryj_pole(T, O, nx, ny); // Rekurencyjnie odkrywamy sasiednie pole
                }
            }
        }
    }
}

void wypisz(int **T, int **O)
{
    printf("pozostalo: %d min\n", ilebomb(O));
    printf("masz: %d punktow\n", ilepkt(O));
    
    // Wypisanie numerow kolumn
    printf("  ");
    for(int i = 0; i < s; i++)
    {
        printf("\033[1;34m%4d\033[0m", i+1); // Numery kolumn
    }
    printf("\n");

    // Wypisanie gornej krawedzi
    printf("    ");
    for(int i = 0; i < s; i++)
    {
        printf("----"); // Krawedz dla kazdej kolumny
    }
    printf("\n");

    // Wypisanie planszy
    for (int i = 0; i < d; i++) // Iteracja po wierszach
    {
        printf("\033[1;34m%3d\033[0m", i+1);  // Wypisanie numeru wiersza, z wyrownaniem
        printf("|"); // Poczatek kazdej linii

        for (int j = 0; j < s; j++) // Iteracja po kolumnach
        {
            // Odkryte pole
            if (O[i][j] == 1)
            {
                if (T[i][j] != -1) // Liczba min w okolicy
                {
                    printf("\033[1m% d \033[0m", T[i][j]);
                }
                else // Mina
                {
                    printf("\033[1;31m X \033[0m");
                }
            }
            // Flaga
            else if (O[i][j] == -1)
            {
                printf("\033[1;32m * \033[0m");
            }
            // Zakryte pole
            else
            {
                printf("   ");
            }

            printf("|"); // Krawedz komorki
        }
        printf("\n");

        // Wypisanie dolnej krawedzi
        printf("    ");
        for (int j = 0; j < s; j++)
        {
            printf("----");
        }
        printf("\n");
    }
}

int warunek(const void *a, const void *b)
{
    return (const int *) a - (const int *) b;
}

typedef struct spis
{
    int w;
    char *nick;
} zwy;

void to_koniec(int **T, int **O)
{
    if(koniec(O, T) == 1)
    {
        printf("\n---------------------------------------");
        printf("\n|GRATULACJE, ODNIOSLES/AS ZWYCIESTWO!!!|\n");
        printf("----------------------------------------\n");

        if(wybor != 4)
        {
            printf("twoja rozgrywka byla rankingowa, a wiec \n");

            zwy *tab = malloc(7 * sizeof(zwy));

            FILE* plikkon;
            plikkon = fopen("listazwyciezcow.txt", "r+");

            if (plikkon == NULL) {
                printf("Nie udalo sie otworzyc pliku.\n");
                return;
            }

            printf("podaj swoj pseudonim: ");
            tab[0].nick = malloc(100 * sizeof(char)); // Alokacja pamieci na pseudonim
            scanf("%s", tab[0].nick);
            tab[0].w = (d * s - miny) * wybor;

            // Wczytanie dotychczasowych wynikow
            for(int i = 1; i < 6; i++)
            {
                tab[i].nick = malloc(100 * sizeof(char));  // Alokacja pamieci dla nicka
                fscanf(plikkon, "%s %d", tab[i].nick, &tab[i].w);
            }

            // Sortowanie wynikow
            char pomn[100];  // Alokacja pamieci dla tymczasowego nicka
            int pomw = 0;

            for(int i = 0; i < 5; i++)  // Zmieniony zakres petli
            {
                for(int j = 1; j < 6; j++)
                {
                    if(tab[j].w >= tab[j-1].w)
                    {
                        strcpy(pomn, tab[j].nick);
                        strcpy(tab[j].nick, tab[j-1].nick);
                        strcpy(tab[j-1].nick, pomn);

                        pomw = tab[j].w;
                        tab[j].w = tab[j-1].w;
                        tab[j-1].w = pomw; 
                    }
                }
            }

            printf("\nPo twojej wspanialej rozgrywce top 6 graczy wyglada nastepujaco:\n");

            fclose(plikkon);
            plikkon = fopen("listazwyciezcow.txt", "w+");

            // Zapis posortowanych wynikow
            for(int i = 0; i < 6; i++)
            {
                printf("%d. %s - %d pkt\n", i+1, tab[i].nick, tab[i].w);
                fprintf(plikkon, "%s %d\n", tab[i].nick, tab[i].w);
            }

            fclose(plikkon);

            // Zwolnienie pamieci
            for (int i = 0; i < 6; i++) {
                free(tab[i].nick);
            }
            free(tab);
        }
    }
    else if(koniec(O, T) == -1)
    {
        printf("\n-------------------------------------------");
        printf("\n|NIESTETY :(( NIE TYM RAZEM, PRZEGRALES/AS|\n");
        printf("-------------------------------------------\n");
    }
}



void gra(int **T)
{
    int **O = malloc(s * sizeof(int*)); // pola odwiedzone
    
    for(int i = 0; i < d; i++)
    {
        O[i] = malloc(s * sizeof(int));
    }

    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < s; j++)
        {
            O[i][j] = 0;
        }
    }

    O[dp][sp] = 1;
    odkryj_pole(T, O, dp, sp);
    char decyzja = 'd';
    int odkrywanex = -1;
    int odkrywaney = -1;
    char a[1000];

    while(koniec(O, T) == 0) //gra trwa do kiedy sie nie skonczy
    {
        wypisz(T, O);

        decyzja = 'd';
        odkrywanex = -1;
        odkrywaney = -1;

        while(decyzja != 'r' && decyzja != 'f') //skanuje dopuki nie dostanie zdanej wartosci
        {
            printf("podaj co chcesz zrobic r - otworz pole, f - oflaguj pole lub je odflaguj\n");
            scanf(" %c", &decyzja);
        }

        while(odkrywanex < 0 || odkrywanex >= s)
        {
            printf("podaj wspolrzedna x ");
            scanf(" %s", a);
            odkrywanex = sprr(a) - 1;
        }

        while(odkrywaney < 0 || odkrywaney >= d)
        {
            printf("podaj wspolrzedna y ");
            scanf(" %s", a);
            odkrywaney = sprr(a) - 1;
        }

        

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        if(decyzja == 'r')
        {
            odkryj_pole(T, O, odkrywaney, odkrywanex);
        }
        else if(decyzja == 'f')
        {
            if(O[odkrywaney][odkrywanex] == -1)
            {
                O[odkrywaney][odkrywanex] = 0;
            }
            else
            {
                O[odkrywaney][odkrywanex] = -1;
            }
        }
    }

    wypisz(T, O);

    to_koniec(T, O);

    for(int i = 0; i < d; i++) 
    {
        free(O[i]);
    }
    free(O);
}