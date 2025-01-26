#include"menu.h"
#include<stdio.h>
#include<stdlib.h>

int czyl(const char *str) //funkcja sprawdza czy wprowadzona dana jest liczba calkowita
{
    char *spr;

    strtol(str, &spr, 10); 

    return (*spr == '\0');
}

int spr(const char *a) //funkcja przenosi dana do zmiennej int
{
    if (czyl(a)) 
    {
        return atoi(a);
    }
    return 0;
}

void menu()
{
    printf(" ______________________________________________________________________________________________________________ \n");
    printf("|                                                    SAPER                                                     |\n");
    printf("|______________________________________________________________________________________________________________|\n");
    printf("|   POZIOM TRUDNOSCI (WIELKOSC PLANSZY I ILOSC MIN):                                                           |\n");
    printf("|   _________________________                                                                                  |\n");
    printf("|   |1 - LATWY (9x9 i 10)    |                                                                                 |\n");
    printf("|   |2 - SREDNI (16x16 i 40) |                                                                                 |\n");
    printf("|   |3 - TRUDNY (16x30 i 99) |                                                                                 |\n");
    printf("|   |4 - WLASNY*             |                                                                                 |\n");
    printf("|   |________________________|                                                                                 |\n");
    printf("|                                                                                                              |\n");
    printf("|                                                                                                              |\n");
    printf("|                                                                                                              |\n");
    printf("|                                                                                                              |\n");
    printf("|                                                                                                              |\n");
    printf("|   *TRYB WLASNY JEST NIERANKINGOWY I NIE BEDZIE ZAPISYWANY DO RANKINGU!                                       |\n");
    printf("|______________________________________________________________________________________________________________|\n");

    wybor = 0;
    char a[1000];

    while (wybor < 1 || wybor > 4) //dopuki nie zostanie podana poprawna dana program bedzie pobieral od nowa dana
    {
        printf("WYBIERZ POZIOM TRUDNOSCI: ");
        scanf("%s", a);
        wybor = spr(a);
        printf("\n");
    }

    if(wybor == 1)
    {
        d = 9;
        s = 9;
        miny = 10;
    }
    else if(wybor == 2)
    {
        d = 16;
        s = 16;
        miny = 40;
    }
    else if(wybor == 3)
    {
        d = 16;
        s = 30;
        miny = 99;
    }
    else if(wybor == 4)
    {
        while(d < 3 || d > 50)
        {
            printf("PODAJ ILOSC WIERSZY (Z ZAKRESU 3 - 50): ");
            scanf("%s", a);
            d = spr(a);
            printf("\n");
        }

        while (s < 3 || s > 50)
        {
            printf("PODAJ ILOSC KOLUMN (Z ZAKRESU 3 - 50): ");
            scanf("%s", a);
            s = spr(a);
            printf("\n");
        }

        int g = (d - 1) * (s - 1);

        while(miny < 1 || miny > g)
        {
            printf("PODAJ ILOSC MIN (Z ZAKRESU 1 - %d): ", g);
            scanf("%s", a);
            miny = spr(a);
            printf("\n");
        }
    }

    while(sp < 0 || sp > s)
    {
        printf("PODAJ KOLUMNE STARTOWA Z ZAKRESU 1 - %d: ", s);
        scanf("%s", a);
        sp = spr(a) - 1;
        printf("\n");
    }

    while(dp < 0 || dp > d)
    {
        printf("PODAJ WIERSZ STARTOWY Z ZAKRESU 1 - %d: ", d);
        scanf("%s", a);
        dp = spr(a) - 1;
        printf("\n");
    }
}