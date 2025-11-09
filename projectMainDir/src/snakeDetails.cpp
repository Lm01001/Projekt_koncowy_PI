#include "SnakeDetails.h"
#include "SnakeGUI.h"

#include <iostream>
#include <string>
//#include <windows.h>
#include <ctime>

    SnakeDetails::SnakeDetails(int w, int dl, int l, std::string p) : wynik(w), dlugosc(dl), lvl(l), powerUp(p) {} 
    SnakeGui::SnakeGui() {}
    /*

    *   void SnakeDetails::aktualizujWynik(int wynik){
            //Zwiekszanie wynik np po zjedzeniu przedmiotu np. o 10
        }

    *   void SnakeDetails::aktualizujDlugosc(int dlugosc){
            //Zwiekszanie dlugosci weza po zjedzeniu np 2/3 przedmiotow
        }

    *   void SnakeDetails::kolejnyEtap(int lvl){
            //jesli zostanie osiagniety wymagany wynik to etap inkrementacja
        }

    *   int SnakeDetails::losowaniePowerUpa(){
            //odpalenie losowania jednego z 4 powerup'ów 
        }

        //???
    *   void SnakeDetails::przegranaGracza(int wynik, int dlugosc, int lvl){
            //reset wartosci aktualnego weza
        }

    *   void SnakeDetails::wyswietlStatystyki(int wynik, int dlugosc, int lvl){
            //wyswietlanie statystyk
        }

    */
    void SnakeGui::ustawTloOkna(sf::RenderWindow& window, sf::Color kolor){
        window.clear(kolor);
    }

    sf::RectangleShape SnakeGui::stworzPasekOkna(int szerokosc, int wysokosc, sf::Color kolor){
        sf::RectangleShape topBar(sf::Vector2f(szerokosc, wysokosc));
        topBar.setFillColor(kolor);
        topBar.setPosition(0, 0);
        return topBar;
    }   
    
    sf::RectangleShape SnakeGui::stworzPrzycisk(int x, int y, int szerokosc, int wysokosc, sf::Color kolor){
        sf::RectangleShape button(sf::Vector2f(szerokosc, wysokosc));
        button.setFillColor(kolor);
        button.setPosition(x, y);
        return button;
    }

