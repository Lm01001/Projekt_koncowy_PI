#ifndef SNAKEGUI_H
#define SNAKEGUI_H    
    
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class SnakeGui{
    public:
        /*
        * Zmienne do tworzenia, ustawienia wlasnosci przycisków
        */
        bool isClicked = false;
        int xWspolrzedna;
        int yWspolrzedna;
        bool isMouseOn = false;

        SnakeGui();
        void ustawTloOkna(sf::RenderWindow& window, sf::Color kolor);
        sf::RectangleShape stworzPasekOkna(int szerokosc, int wysokosc, sf::Color kolor);
        sf::RectangleShape stworzPrzycisk(int x, int y, int szerokosc, int wysokosc, sf::Color kolor);
};

#endif