#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

#include "SnakeDetails.h"
#include "SnakeGUI.h"

using namespace std;
using namespace sf; 

//g++ src/*.cpp -I include -lsfml-graphics -lsfml-window -lsfml-system -o run 

int main() {
	SnakeGui instForGui = SnakeGui();
	SnakeGui buttonObj = SnakeGui();
	Vector2i pozycjaMyszy;

	/*
	* Zmienna typu RenderWindow - wyswietlane okno, RectangleShape pod stworzenie przycisku
	*/
	RenderWindow window(VideoMode(550, 650), "Gra Snake", Style::Default);
	window.display();

	VideoMode desktopScreen = VideoMode::getDesktopMode();
	int x = (desktopScreen.width - 800) / 2;
	int y = (desktopScreen.height - 800) / 2;
	window.setPosition(sf::Vector2i(x, y));
	window.setVerticalSyncEnabled(true);
	
	//sf::RectangleShape gornyPasekOkna = instForGui.stworzPasekOkna(800, 50, sf::Color(168, 168, 168));
	RectangleShape mainButtonFrame = instForGui.stworzPrzycisk(175, 400, 200, 100, Color(89,43,66));
	RectangleShape mainButton = buttonObj.stworzPrzycisk(190, 415, 170, 70, Color(192, 192, 192));
	buttonObj.xWspolrzedna = x + 190;
	buttonObj.yWspolrzedna = y + 415;

	/*
	*
	*/
	const string text = "Graj";
	Text text1;
	text1.setString(text);
	text1.setPosition(Vector2f(buttonObj.xWspolrzedna + 30,  buttonObj.yWspolrzedna + 30));
	text1.setFillColor(Color::Black);
	text1.setCharacterSize(30);
	while(window.isOpen()){
		Event event;
		mainButton.setOutlineColor(Color(89,43,66));
		mainButton.setOutlineThickness(5);
		mainButton.setFillColor(Color(192, 192, 192));
		buttonObj.isMouseOn = false;

		while(window.pollEvent(event)){
			if(event.type == Event::Closed)
				window.close();
		}

		pozycjaMyszy = Mouse::getPosition();
		if(pozycjaMyszy.x >= buttonObj.xWspolrzedna && pozycjaMyszy.y >= buttonObj.yWspolrzedna &&
			(pozycjaMyszy.x <= buttonObj.xWspolrzedna + 170) && (pozycjaMyszy.y <= buttonObj.yWspolrzedna + 70) &&
			Mouse::isButtonPressed(Mouse::Left)){
				buttonObj.isMouseOn = true;
				//window.close();				
		}
	
		window.clear();
		instForGui.ustawTloOkna(window, Color(222, 216, 194));
		window.draw(mainButton);
		/*if(buttonObj.isMouseOn){
			mainButton.setPosition(Vector2f(buttonObj.xWspolrzedna, buttonObj.yWspolrzedna));
			window.draw(mainButton);
		}*/
		

		/*
		*	dla pauzy
		*/
		if(Keyboard::isKeyPressed(Keyboard::Escape)){
				window.close();
		}
		

		/*if(!buttonObj.isClicked){
			mainButton.setPosition(Vector2f(buttonObj.xWspolrzedna, buttonObj.yWspolrzedna));
			//window.draw(mainButton);
		}
		if(buttonObj.isClicked){
			mainButton.setFillColor(Color(128,128,128));
		}*/


		window.display();
	}

	return 0;
}