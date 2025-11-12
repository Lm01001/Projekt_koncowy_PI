#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "SnakeDetails.h"
#include "SnakeGUI.h"

using namespace std;
using namespace sf;

//g++ src/*.cpp -I include -lsfml-graphics -lsfml-window -lsfml-system -o run 
//git submodule add https://github.com/texus/TGUI.git projectMainDir/libs/SFML-Button

int main() {
	SnakeGui instForGui = SnakeGui();
	SnakeGui buttonObj = SnakeGui();

	/*
	* Zmienna typu RenderWindow - wyswietlane okno, RectangleShape pod stworzenie przycisku
	*/
	RenderWindow window(VideoMode(550, 650), "Gra Snake", Style::Default);

	VideoMode desktopScreen = VideoMode::getDesktopMode();
	int x = (desktopScreen.width - 550) / 2;
	int y = (desktopScreen.height - 650) / 2;
	window.setPosition(sf::Vector2i(x, y));
	window.setVerticalSyncEnabled(true);
	

	tgui::Gui gui{window};
	/*
	*
	*	wrzucic to jako funkcje do klasy ustawianie tego wszystkiego
	*
	*/
	auto mainButton = tgui::Button::create("Graj");
	mainButton->setPosition(190, 435);
	mainButton->setSize(170, 70);
	mainButton->getRenderer()->setBackgroundColor(tgui::Color(192, 192, 192));
	mainButton->getRenderer()->setBackgroundColorHover(tgui::Color(200, 200, 200));
	mainButton->getRenderer()->setBorderColor(tgui::Color(89, 43, 66));
	mainButton->getRenderer()->setBorders(5);
	mainButton->setTextSize(28);

	mainButton->onPress([]() {
		cout<<"dziala przycisk"<<endl;
	});
	//sf::RectangleShape gornyPasekOkna = instForGui.stworzPasekOkna(800, 50, sf::Color(168, 168, 168));
	/*RectangleShape mainButtonFrame = instForGui.stworzPrzycisk(175, 400, 200, 100, Color(89,43,66));
	RectangleShape mainButton = buttonObj.stworzPrzycisk(190, 415, 170, 70, Color(192, 192, 192));
	buttonObj.xWspolrzedna = x + 190;
	buttonObj.yWspolrzedna = y + 415;

	/*
	*
	
	const string text = "Graj";
	Text text1;
	text1.setString(text);
	text1.setPosition(Vector2f(buttonObj.xWspolrzedna + 30,  buttonObj.yWspolrzedna + 30));
	text1.setFillColor(Color::Black);
	text1.setCharacterSize(30);*/


	gui.add(mainButton);

	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			gui.handleEvent(event);

			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		window.clear(Color(222, 216, 194));
		gui.draw();

		window.display();
	}

	return 0;
}