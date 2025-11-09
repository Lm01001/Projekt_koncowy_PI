#ifndef SNAKEDETAILS_H
#define SNAKEDETAILS_H

#include <string>

class SnakeDetails{
    public:
        int wynik, dlugosc, lvl;
        std::string powerUp;
        SnakeDetails(int wynik, int dlugosc, int lvl, std::string powerUp); //fabularny
        /*SnakeDetails(string a, int wynik, int dl, int r); //timed
        //SnakeDetails(string a, int wynik, int dl, string p); //powerupy*/

        void aktualizujWynik(int wynik);
        void aktualizujDlugosc(int dlugosc);
        void kolejnyEtap(int lvl);
        int losowaniePowerUpa();
        void przegranaGracza(int wynik, int dlugosc, int lvl); //???
        void wyswietlStatystyki(int wynik, int dlugosc, int lvl);
};

#endif