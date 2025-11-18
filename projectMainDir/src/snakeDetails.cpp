#include "SnakeDetails.h"
#include "SnakeGUI.h"

#include <iostream>
#include <string>
//#include <windows.h>
#include <ctime>

    SnakeDetails::SnakeDetails(int w, int dl, int l, std::string p) : wynik(w), dlugosc(dl), lvl(l), powerUp(p) {} 
    
    
    /*
    *
    *   funkcje do weza, dzialanie, tworzenie aktualizacja
    *   we wszystkich funkcji mozna zmienic argumenty, zalezy
    *   od potrzeby jakie parametry beda potrzebne do przekazania
    * 
    */
    
    /*SnakeDetails::SnakeDetails(){
        //ustawienie ciala weza
        //przypisanie wartosci do wektora z kierunkiem
        //przypisanie wartosci zmiennym od predkosci ruchu i ustawienie timera
    }

    void SnakeDetails::ustawKierunek(sf::Vector2i kierunek){
        //zmienna z klasy SnakeDetails - przypisanie jej wartosci
        //przekazanego jako parametr wektora
    }

    void czyKolizjaZeSciana(int szerokoscPlanszy, int wysokoscPlanszy, bool kolizja){
        //sprawdzanie czy kolizja ze sciana, zobaczyc na pozycje
        //planszy i rozmiar i odpowiednio dodac marginesy 
    }

    void kolejnyLevel(tgui::CanvasSFML& planszaGry, int brama){
        //dodanie ciemniejszego koloru na brame do kolejnego etapu
        //mozna tez dodac strzalke gdzie wejsc
        //podac szerokosc bramy
    }

    void SnakeDetails::movementAktualizujWeza(float czasOdPoprzedniejKlatki){
        //aktualizacja timera i przesuniecie weza
        //mozna dodac warunek ze gdy zmienna ze zjedzonymi
        //przedmiotami ma jakas wartosc
        //np. co (200) losowany jest 1 z 4 powerupow
        //warunek jesli osiagniety prog wyniku zwieksza sie waz
        //wywolanie wewnatrz funkcji losowaniePowerUpa
    }

    void SnakeDetails::draw(tgui::CanvasSFML& planszaGry){
        //bazowe rysowanie i tworzenie weza
    }
    
    void SnakeDetails::aktualizujWynik(int wynik){
            //Zwiekszanie wynik np po zjedzeniu przedmiotu np. o 10
    }

    void SnakeDetails::kolejnyEtap(int lvl){
        //jesli zostanie osiagniety wymagany wynik to etap inkrementacja
        //zatrzymanie stopera - dodac dodatkowy argument albo
        //typu float przetrzymujacej czas lub Clock
    }

    void SnakeDetails::przegranaGracza(int wynik, int dlugosc, int lvl){
        //reset wartosci aktualnego weza
        //mozliwe ze usuniecie weza, niekoniecznie
        //po prostu reset bo ekran po przegranej przenosi
        //do menu i tak
    }

    void SnakeDetails::wyswietlStatystyki(int wynik, int dlugosc, int lvl){
        //wyswietlanie statystyk
        //przekazanie gdzies tych przypisanie, zeby wykorzystac
        //do dodania do sceny
        //bedzie wywolywana i po przegranej i koncu gry
    }
    */
    

    /*
    *   Ustawianie kwestii zwiazanych z GUI
    *   wygladem wizualnych scen, czyli nie
    *   bezposrednio z obiektem weza samego
    *   w sobie.
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

