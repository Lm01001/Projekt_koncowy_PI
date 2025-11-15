#include <iostream>
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
//#include <windows.h>
#include <unistd.h>
#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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
	auto mainButton = buttonObj1.getButton();
	
	/*
	*	Przycisk do przejscia do ustawien rozgrywki
	*/
	ButtonScenesPropertiesClass buttonSettings = ButtonScenesPropertiesClass(gui, 495, 30, 35, 35, tgui::Color(89, 43, 66), 0);
	auto settingsButton = buttonSettings.getButton();
	
	/*
	*	
	*/
	ButtonScenesPropertiesClass pauseButtonGenerated = ButtonScenesPropertiesClass(gui, 495, 30, 35, 35, tgui::Color(89, 43, 66), 0);
	auto pauseButton = pauseButtonGenerated.getButton();
	
	/*
	*	Tworzenie bazowych scen dla projektu
	*/
	ButtonScenesPropertiesClass sceneManager = ButtonScenesPropertiesClass(gui);
	sceneManager.updateAllScenes(mainButton, settingsButton, pauseButton, sceneManager.menuPanel, sceneManager.pausePanel,
			sceneManager.resultPanel, sceneManager.settingsPanel, sceneManager.gamePanel);
	
	
	/*
	*	Segment na zmienne pod nextRoundPopup
	*/
	bool gameStartClick = false;
	Clock c;
	int counterHelper = 3;
	auto labelCount = tgui::Label::create();
		labelCount->setTextSize(100);
		labelCount->setPosition("(&.width - width) / 2", "(&.height - height) / 2");		
		labelCount->getRenderer()->setTextColor(sf::Color::Black);
		labelCount->getRenderer()->setTextOutlineThickness(3);
	sf::Vector2u winSize = window.getSize();
	sf::CircleShape circle(100.f);
		circle.setFillColor(sf::Color(122, 113, 101));
		float circleXPos = circle.getRadius() * 2;
		float circleYPos = circle.getRadius() * 2;
		circle.setPosition((winSize.x - circleXPos) / 2, (winSize.y - circleYPos) / 2);		

	/*
	*	Ustawianie zmian scen przycisku
	*/
	mainButton->onPress([&sceneManager, &gameStartClick]() {
		/*
		*
		*/	
		sceneManager.showGameScene();
		gameStartClick = true;
	});

	
	settingsButton->getRenderer()->setTexture("../resources/ikonaUstawien.png");
	settingsButton->onPress([&sceneManager](){
		sceneManager.showSettingsScene();

	});
	pauseButton->getRenderer()->setTexture("../resources/ikonaPrzyciskuPauzy.png");
	pauseButton->onPress([&sceneManager](){
		sceneManager.showPauseScene();
	});

	
	while(window.isOpen()){
		Event event;
		while(window.pollEvent(event)){
			gui.handleEvent(event);

			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		gui.draw();
		window.display();
		
		/*
		*	Wczytywanie gry => Odliczanie, zeby nie odpalic gry
		*	bezposrednio po kliknieciu przycisku i zmiany
		*	sceny.
		*/
		if(gameStartClick){
			if(counterHelper == 3){
				labelCount->setText("3");
				labelCount->moveToFront();
				window.draw(circle);
				sceneManager.nextRoundPopup->add(labelCount);
				sceneManager.showNextRoundPopup();
				counterHelper--;
			}
			
			if(c.getElapsedTime().asSeconds() > 2.5 && counterHelper == 2){
				labelCount->setText("2");
				labelCount->moveToFront();
				window.draw(circle);
				sceneManager.nextRoundPopup->add(labelCount);
				sceneManager.showNextRoundPopup();					
				counterHelper--;
			}

			if(c.getElapsedTime().asSeconds() > 4.5 && counterHelper == 1){
				labelCount->setText("1");
				labelCount->moveToFront();
				window.draw(circle);
				sceneManager.nextRoundPopup->add(labelCount);
				sceneManager.showNextRoundPopup();
				counterHelper--;
			}

			if(c.getElapsedTime().asSeconds() > 6){
				if(counterHelper == 0){
					gameStartClick = false;
					sceneManager.showGameScene();
				}		
			}
		}
	}

	return 0;
}