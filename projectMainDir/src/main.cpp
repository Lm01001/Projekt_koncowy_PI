#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

#include "SnakeDetails.h"
#include "SnakeGUI.h"

using namespace std;
//g++ ../../src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o run

int main() {
	SnakeGui instForGui = SnakeGui();
	SnakeGui buttonObj = SnakeGui();
	sf::Vector2i pozycjaMyszy;

	/*
	* Zmienna typu RenderWindow - wyswietlane okno, RectangleShape pod stworzenie przycisku
	*/
	sf::RenderWindow window(sf::VideoMode(550, 650), "Gra Snake");
	//sf::RectangleShape gornyPasekOkna = instForGui.stworzPasekOkna(800, 50, sf::Color(168, 168, 168));
	sf::RectangleShape mainButtonFrame = instForGui.stworzPrzycisk(175, 400, 200, 100, sf::Color(89,43,66));
	sf::RectangleShape mainButton = buttonObj.stworzPrzycisk(190, 415, 170, 70, sf::Color(192, 192, 192));
	buttonObj.xWspolrzedna = 190;
	buttonObj.yWspolrzedna = 415;

	/*
	*
	*/
	sf::VideoMode desktopScreen = sf::VideoMode::getDesktopMode();
	int x = (desktopScreen.width - 800) / 2;
	int y = (desktopScreen.height - 800) / 2;
	window.setPosition(sf::Vector2i(x, y));

	while(window.isOpen()){
		sf::Event event;
		mainButton.setFillColor(sf::Color(192, 192, 192));
		button.isMouseOn = false;

		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}

		pozycjaMyszy = Mouse::getPosition(window);
		if(pozycjaMyszy.x <= buttonObj.xWspolrzedna && pozycjaMyszy <= buttonObj.yWspolrzedna &&
			pozycjaMyszy.x >= buttonObj.xWspolrzedna + 170 && pozycjaMyszy.y >= buttonObj.yWspolrzedna + 70){
				button.isMouseOn = true;
		}
		window.clear();
		instForGui.ustawTloOkna(window, sf::Color(222, 216, 194));
		window.draw(mainButtonFrame);

		if(!button.isClicked){
			mainButton.setPosition(sf::Vector2f(button.xWspolrzedna, button.yWspolrzedna));
			window.draw(mainButton);
		}
		if(button.isClicked){
			mainButton.setFillColor(sf::Color(128,128,128));
		}
		
		window.display();
	}

	return 0;
}