#ifndef SNAKEDETAILS_H
#define SNAKEDETAILS_H

class SnakeDetails{
    int wynik, dlugosc, level;
    string powerUp;
    public:
        SnakeDetails(int wynik, int dlugosc, int lvl, string powerUp); //fabularny
        /*SnakeDetails(string a, int wynik, int dl, int r); //timed
        //SnakeDetails(string a, int wynik, int dl, string p); //powerupy*/

        void aktualizujWynik(int wynik);
        void aktualizujDlugosc(int dlugosc);
        void kolejnyEtap(int lvl);
        int losowaniePowerUpa();
        void przegranaGracza(int wynik, int dlugosc, int lvl); //???
        void wyswietlStatystyki(int wynik, int dlugosc, int lvl);

}

#endif