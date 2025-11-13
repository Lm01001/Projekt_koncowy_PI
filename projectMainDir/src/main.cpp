#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "SnakeDetails.h"
#include "SnakeGUI.h"
#include "ButtonScenesPropertiesClass.h"

using namespace std;
using namespace sf;


int main() {
	//SnakeGui instForGui = SnakeGui();
	//SnakeGui buttonObj = SnakeGui();


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
	*	Glowny przycisk do przejscia do ekranu gry
	*/
	ButtonScenesPropertiesClass buttonObj1 = ButtonScenesPropertiesClass(gui ,"Graj", 190, 435, 170, 70, 
		tgui::Color(192, 192, 192), tgui::Color(200, 200, 200), tgui::Color(89, 43, 66), 5, 28);
	/*
	*	Przycisk do przejscia do ustawien rozgrywki
	*/
	ButtonScenesPropertiesClass buttonSettings = ButtonScenesPropertiesClass(gui, 20, 510, 20, 20, tgui::Color(89, 43, 66), 3);
	//buttonSettings->getRenderer()->setTexture("resources/ikonaUstwien.png");

	ButtonScenesPropertiesClass sceneManager = ButtonScenesPropertiesClass(gui);
	//sceneManager.menuPanel


	auto mainButton = buttonObj1.getButton();

	mainButton->onPress([]() {
		cout<<"dziala przycisk"<<endl;
	});


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