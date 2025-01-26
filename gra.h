#ifndef GRA_H
#define GRA_H

extern int d;
extern int s;
extern int miny;
extern int sp;
extern int dp;
extern int wybor;

int czyll(const char *str); //funkcja sprawdza czy wprowadzona dana jest liczba calkowita

int sprr(const char *a); //funkcja przenosi dana do zmiennej int

int ilebomb( int **O); //ile bomb zostalo do odkrycia wg gracza

int koniec(int **O, int **T); //sprawdza czy gra sie nie skonczyla

void odkryj_pole(int **T, int **O, int x, int y);

void wypisz(int **T, int **O); //wypisanie gry

void gra(int **T); //nasze centrum gry

#endif //GRA_H