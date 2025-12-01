#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
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
#include "SlidersAndCheckbox.h"

using namespace std;
using namespace sf;


int main() {
	
	/*
	* Zmienna typu RenderWindow - wyswietlane okno, RectangleShape pod stworzenie przycisku
	*/
	RenderWindow window(VideoMode({550, 650}), "Gra Snake", Style::Default);
	window.setFramerateLimit(60);
	auto desktopScreen = VideoMode::getDesktopMode();
	int x = (desktopScreen.size.x - 550) / 2;
	int y = (desktopScreen.size.y - 650) / 2;
	window.setPosition(sf::Vector2i(x, y));
	window.setVerticalSyncEnabled(false);
	
	tgui::Gui gui{window};

	SnakeDetails snakeInstance;
	// Zegar służący do obliczania czasu między klatkami (Delta Time)
    // Niezbędny do zapewnienia płynności ruchu niezależnie od wydajności komputera
    Clock movementHelperClock; 


	/*
	*	Glowny przycisk do przejscia do ekranu gry.
	*/
	ButtonScenesPropertiesClass buttonObj1 = ButtonScenesPropertiesClass(gui ,"Graj", 190, 435, 170, 70, 
		tgui::Color(192, 192, 192), tgui::Color(200, 200, 200), tgui::Color(89, 43, 66), 5, 28);
	auto mainButton = buttonObj1.getButton();
	
	/*
	*	Przycisk do przejscia do ustawien rozgrywki w
	*	menu glownym i ustawienia poziomu trudnosci
	*	oraz efektow dzwiekowych
	*/
	ButtonScenesPropertiesClass buttonSettings = ButtonScenesPropertiesClass(gui, 495, 30, 35, 35, tgui::Color(89, 43, 66), 0);
	auto settingsButton = buttonSettings.getButton();
	
	/*
	*	Przycisk do zatrzymywania gry w rogu
	*	juz w trakcie rozgrywki.
	*/
	ButtonScenesPropertiesClass pauseButtonGenerated = ButtonScenesPropertiesClass(gui, 495, 20, 35, 35, tgui::Color(89, 43, 66), 0);
	auto pauseButton = pauseButtonGenerated.getButton();
	
	/*
	*	Tworzenie bazowych scen dla projektu oraz dodawanie 
	*	do nich koniecznych elementow ze wzgledu na to,
	*	ze w konstruktorze sa funkcje bez argumentow.
	*/
	ButtonScenesPropertiesClass sceneManager = ButtonScenesPropertiesClass(gui);
	sceneManager.updateAllScenes(mainButton, settingsButton, pauseButton, sceneManager.menuPanel, sceneManager.pausePanel,
			sceneManager.resultPanel, sceneManager.settingsPanel, sceneManager.gamePanel);
	

	/*
	*	Wznawianie gry z menu pauzy, przycisk sluzacy do tego.
	*/
	ButtonScenesPropertiesClass resumeButtonGenerated = ButtonScenesPropertiesClass(gui ,"Wznow", 190, 360, 170, 70, 
		tgui::Color(192, 192, 192), tgui::Color(200, 200, 200), tgui::Color(89, 43, 66), 5, 28);
	auto resumeButton = resumeButtonGenerated.getButton();
	sceneManager.pausePanel->add(resumeButton);
	
	/*
	*	Segment na zmienne pod nextRoundPopup.
	*	Czyli wszystko potrzebne pod to, zeby 
	*	bylo odliczanie przed poczatkiem i cyfry
	*	w kolach + zmienna pomocnicza do tego,
	*	czy uzytkownik rozpoczal gre przez 
	*	wcisniecie glownego przycisku.
	*/
	bool gameStartClick = false;
	Clock c;
	int counterHelper;
	auto labelCount = tgui::Label::create();
		labelCount->setTextSize(100);
		labelCount->setPosition("(&.width - width) / 2", "(&.height - height) / 2");		
		labelCount->getRenderer()->setTextColor(sf::Color::Black);
		labelCount->getRenderer()->setTextOutlineThickness(3);
	sf::Vector2u winSize = window.getSize();
	sf::CircleShape circle(100.f);
		circle.setFillColor(sf::Color(21, 61, 117));
		circle.setOutlineColor(sf::Color(13, 39, 74));
		circle.setOutlineThickness(5);
		float circleXPos = circle.getRadius() * 2;
		float circleYPos = circle.getRadius() * 2;
		/*
		*	Dla CircleShape .setPosition() musi byc Vector2f, wiec dodatkowo
		*	tworzymy ten vector poza dla przejrzystosci wiekszej kodu. 
		*/
		sf::Vector2f positionHelper((winSize.x - circleXPos) / 2.f, (winSize.y - circleYPos) / 2.f);
		circle.setPosition(positionHelper);		

	/*
	*	Ustawianie wszystkie przygotowujacego do rozgrywki
	*	inicjalizacja wszystkiego zwiazanego z 
	*	rozgrywka w tym odpalenie timera oraz
	*	ustawianie stanow przez zmienne pomocnicze,
	*	np. czy pauza lub czy gra w trakcie.
	*/
	float sekundy = c.getElapsedTime().asSeconds();
	int minuty = 0;
	bool roundInProgress = false, gamePaused = false;
	int czasWSekundach, sekundySkrocone;
	sceneManager.gameInProgressTimeVar = 0;
	mainButton->onPress([&sceneManager, &gameStartClick, &counterHelper, &c]() {
		/*
		* 	Miejsce na reszte kodu do dodania juz
		*	po implementacji funkcjonalnosci weza
		*/	
		gameStartClick = true;
		counterHelper = 3;
		c.restart();
		sceneManager.showGameScene();
	});

	/*
	*	Tworzenie slidera do ustawienia poziomu
	*	glosnosci efektow dzwiekowych 
	*	domyslnie ustawione na 0, czyli wylaczone.
	*/
	bool inSettingsMenu = false;
		SlidersAndCheckbox settingsVolumeSlider(195, 250);
		settingsVolumeSlider.createSlider(0, 100);
	/*
	*	Tworzenie checkbox'ow sluzacych do wyboru,
	*	zaznaczenia poziomu trudnosci.
	*/
	SlidersAndCheckbox checkboxy(200, 400, 20);
	checkboxy.customLabelCreator(185, 360);
	/*
	*	Przycisk ustawien z ikona z dir z zasobami
	*	po nacisnieciu otwiera okno gdzie mozna ustawic
	*	glosnosc efektow dzwiekowych i wybrac poziom
	*	trudnosci. Defaultowo to latwy, wiaze sie to tylko
	*	z predkoscia poruszania weza.
	*/
	settingsButton->getRenderer()->setTexture("../resources/ikonaUstawien.png");
	settingsButton->onPress([&sceneManager, &inSettingsMenu, &settingsVolumeSlider, &gui, &checkboxy](){
		inSettingsMenu = true;
		settingsVolumeSlider.dodajDoGui(gui);
		checkboxy.dodajCheckbox(gui);
		gui.add(checkboxy.labelCheckBoxSection);
		sceneManager.showSettingsScene();

	});
	/*
	*	Zatrzymuje rozgrywke i timer, mozna albo wznowic
	*	rozgrywke albo wyjsc do menu. W celu przerwania
	*	zakonczenia gry przed jej ukonczeniem jeszcze
	*	lub przegrana => to to jedyne miejsce.
	*/
	auto gameLostLabel = tgui::Label::create("Przegrana!");
	gameLostLabel->setWidgetName("przegrana");
	pauseButton->getRenderer()->setTexture("../resources/ikonaPrzyciskuPauzy.png");
	pauseButton->onPress([&sceneManager, &c, &gamePaused, &gameLostLabel](){
		gamePaused = true;
		sceneManager.gameInProgressTimeVar += c.getElapsedTime().asSeconds();
		c.restart();
		sceneManager.showPauseScene();
	});
	/*
	*	Przycisk do wznawiania gry, wyjscia z ekranu ustawien
	*	resetuje timer, ale przechowuje wartosc czasu
	*	w momencie zatrzymania, wiec po wznowieniu jest
	*	wznawiany i nie resetuje się wizualnie.
	*/
	resumeButton->onPress([&sceneManager, &c, &gamePaused](){	
		gamePaused = false;
		c.restart();
		sceneManager.showGameScene();
	});

	/*
	*	Glowna petla, ktorej sa fragmenty kodu odpowiedzialne
	*	za wszystkie interakcje typu rozpoczecie gry,
	*	zmiany w ustawieniach, czy pauzowanie gry.
	*/
	while(window.isOpen()){
		/*
		*	Dzieki zmianie na SFML 3 i braku domyslnego konstruktora dla event
		*	trzeba przekazac jako warunek zmienna tu np. - pollEventVarHelper
		*	zeby przy kazdym przejsciu petli byla odswiezana
		*/
		while(auto pollEventVarHelper = window.pollEvent()){
			Event event = *pollEventVarHelper;
			gui.handleEvent(event);
			if(event.is<Event::Closed>())
				window.close();
			if(event.is<Event::KeyPressed>()){
				if(event.getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape){
					window.close();
				}
			} 	

			/*
			*	Zmiana kierunku mozliwa tylko podczas trwajacej, aktywnej rozgrywki.
			*/
			if(roundInProgress && !gamePaused) {
				/*	
				*	Dodanie instrukcji, czy jakikolwiek przycisk jest wcisniety,
				*	bo brak generowal bledy i ciagle program wchodzil w sprawdzanie
				*	warunkow, i tak kazdego z czterech, bo solo if'y a nie if..else
				*/
				if(event.is<Event::KeyPressed>()){
					auto keyPressedEventHelper = event.getIf<Event::KeyPressed>();
					if(keyPressedEventHelper){
						/*	
						*	Zmienna pomocnicza, zmniejszajaca ilosc kodu i wygode (zamiast)
						*	ciaglego -> 
						*/
						auto code = keyPressedEventHelper->code;
						/*	Przekazanie wektora kierunku do obiektu klasy z wezem	*/
						if(code == Keyboard::Key::Up && snakeInstance.direction != 'd' && snakeInstance.direction != 'u'){
							snakeInstance.ustawKierunek(sf::Vector2i(0, -1));
							snakeInstance.direction = 'u';
						}else if(code == Keyboard::Key::Down && snakeInstance.direction != 'u' && snakeInstance.direction != 'd'){
							snakeInstance.ustawKierunek(sf::Vector2i(0, 1));
							snakeInstance.direction = 'd';
						}else if(code == Keyboard::Key::Left && snakeInstance.direction != 'r' && snakeInstance.direction != 'l'){
							snakeInstance.ustawKierunek(sf::Vector2i(-1, 0));
							snakeInstance.direction = 'l';
						}else if(code == Keyboard::Key::Right && snakeInstance.direction != 'l' && snakeInstance.direction != 'r'){
							snakeInstance.direction = 'r';
							snakeInstance.ustawKierunek(sf::Vector2i(1, 0));
						}
					}
				}			
            }

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
			if(c.getElapsedTime().asSeconds() > 1.5 && counterHelper == 2){
				labelCount->setText("2");
				labelCount->moveToFront();
				window.draw(circle);
				sceneManager.nextRoundPopup->add(labelCount);
				sceneManager.showNextRoundPopup();					
				counterHelper--;
			}
			if(c.getElapsedTime().asSeconds() > 3 && counterHelper == 1){
				labelCount->setText("1");
				labelCount->moveToFront();
				window.draw(circle);
				sceneManager.nextRoundPopup->add(labelCount);
				sceneManager.showNextRoundPopup();
				counterHelper--;
			}
			if(c.getElapsedTime().asSeconds() > 4){
				if(counterHelper == 0){
					gameStartClick = false;
					roundInProgress = true;
					c.restart();
					sceneManager.showGameScene();
				}		
			}
		}

		/*
		*	Wylaczanie menu ustawien, a raczej ustawien z okna
		*	bez tej instrukcji po wyjsciu z ustawien zostawaly 
		*	one na ekranie
		*/
		if(inSettingsMenu && !sceneManager.settingsPanel->isVisible()){
			inSettingsMenu = false;
			settingsVolumeSlider.usunZGui(gui);
			checkboxy.usunCheckboxy(gui);
		}

		/*
		*	Obsluga timera znajdujacego sie na gornym
		*	pasku w trakcie rozgrywki.
		*/
		if(roundInProgress && !gamePaused){
			 // 1. OBLICZANIE DELTA TIME
            // Pobranie czasu od ostatniej klatki dla płynności ruchu
            float lastFrameTime = movementHelperClock.restart().asSeconds();
            
            // 2. AKTUALIZACJA LOGIKI WĘŻA
            // Przesunięcie węża zgodnie z jego prędkością i kierunkiem
            snakeInstance.movementAktualizujWeza(lastFrameTime);
            
            // 3. WYKRYWANIE KOLIZJI
            bool czyUderzyl = false;
            // Sprawdzenie czy wąż nie wyszedł poza obszar planszy (wymiary planszy w kratkach)
            snakeInstance.czyKolizjaZeSciana(55, 60, czyUderzyl); 
            
            if (czyUderzyl) {
                // Obsługa końca gry (Game Over)
				/*
				Ustawic znikanie labelu lub po prostu ustawic wtedy scene z rezultatem wynikiem i opcja tylkjo
				wyjscia do menu i usunac
				*/ 
                roundInProgress = false; 
                //std::cout << "[SYSTEM] Wykryto kolizję ze ścianą. Koniec gry." << std::endl;
        		gameLostLabel->setTextSize(65);
        		gameLostLabel->getRenderer()->setTextColor(sf::Color::Red);
        		gameLostLabel->setPosition(105, 180);
				gameLostLabel->getRenderer()->setTextOutlineThickness(2);
				gameLostLabel->getRenderer()->setBackgroundColor(sf::Color::Transparent);
				sceneManager.gamePanel->add(gameLostLabel);
				sceneManager.showGameScene();
            }

            // 4. RYSOWANIE OBIEKTÓW GRY
            // Wyczyszczenie płótna przed narysowaniem nowej klatki
            sceneManager.planszaGryCanvas->clear(sf::Color::Transparent);
			//sceneManager.planszaGryCanvas->moveToFront();
            
            // Wywołanie metody rysującej z klasy węża
            snakeInstance.draw(*sceneManager.planszaGryCanvas);
            
            // Wyświetlenie zaktualizowanego płótna
            sceneManager.planszaGryCanvas->display();

			/*
			*	static_cast sluzy do konwersji z float na int tutaj.
			*	c.getElapsedTime() przypisuje do zmiennej typu float, 
			*	czyli robimy sobie static_cast co powinno być bezpieczniejsze
			*	niz konwersja (int)zmiennaTypuString
			*/
			sekundy = sceneManager.gameInProgressTimeVar + c.getElapsedTime().asSeconds();
			czasWSekundach = static_cast<int>(sekundy);
			minuty = czasWSekundach / 60;
			sekundySkrocone = czasWSekundach % 60;
			/*
			*	Używamy do zapisu danych do wyświetlenia strumienia
			*	tekstowego, czyli strumien dla stringow. Innymi
			*	przykladowymi sa cout, cin albo chociaz cerr, ktorego
			*	uzywamy do wyswietlania bledow przy operacjach na plikach.
			*	Tu tez do przekazywania uzywa sie << co logiczne.
			*/
			std::stringstream streamTimeUpdate;
			streamTimeUpdate << std::fixed <<  "Time: "<< minuty << ":" <<std::setw(2) << std::setfill('0') << sekundySkrocone;
			sceneManager.timeLabelGame->setText(streamTimeUpdate.str());
			sceneManager.gamePanel->add(sceneManager.timeLabelGame);
		}
	}
	return 0;
}