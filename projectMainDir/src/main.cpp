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
    
    // --- KONFIGURACJA OKNA I GUI ---
    // Ustawienie głównego okna aplikacji oraz limitu klatek
    RenderWindow window(VideoMode({550, 650}), "Gra Snake", Style::Default);
    window.setFramerateLimit(60);
    
    // Centrowanie okna na ekranie
    auto desktopScreen = VideoMode::getDesktopMode();
    int x = (desktopScreen.size.x - 550) / 2;
    int y = (desktopScreen.size.y - 650) / 2;
    window.setPosition(sf::Vector2i(x, y));
    window.setVerticalSyncEnabled(false);
    
    tgui::Gui gui{window};

    // =========================================================
    // --- INICJALIZACJA OBIEKTÓW LOGIKI GRY ---
    // =========================================================
    
    // Główny obiekt reprezentujący węża i jego stan
    SnakeDetails snake; 

    // Zegar służący do obliczania czasu między klatkami (Delta Time)
    // Niezbędny do zapewnienia płynności ruchu niezależnie od wydajności komputera
    Clock physicsClock; 

    // Konfiguracja przycisków menu głównego
    ButtonScenesPropertiesClass buttonObj1 = ButtonScenesPropertiesClass(gui ,"Graj", 190, 435, 170, 70, 
        tgui::Color(192, 192, 192), tgui::Color(200, 200, 200), tgui::Color(89, 43, 66), 5, 28);
    auto mainButton = buttonObj1.getButton();
    
    ButtonScenesPropertiesClass buttonSettings = ButtonScenesPropertiesClass(gui, 495, 30, 35, 35, tgui::Color(89, 43, 66), 0);
    auto settingsButton = buttonSettings.getButton();
    
    ButtonScenesPropertiesClass pauseButtonGenerated = ButtonScenesPropertiesClass(gui, 495, 20, 35, 35, tgui::Color(89, 43, 66), 0);
    auto pauseButton = pauseButtonGenerated.getButton();
    
    // Menedżer scen (zarządzanie widokami: Menu, Gra, Pauza, Wyniki)
    ButtonScenesPropertiesClass sceneManager = ButtonScenesPropertiesClass(gui);
    sceneManager.updateAllScenes(mainButton, settingsButton, pauseButton, sceneManager.menuPanel, sceneManager.pausePanel,
            sceneManager.resultPanel, sceneManager.settingsPanel, sceneManager.gamePanel);
    
    // =========================================================
    // --- KONFIGURACJA WARSTWY RYSOWANIA (CANVAS) ---
    // =========================================================
    // Utworzenie specjalnego płótna TGUI, które pozwala na rysowanie obiektów SFML (węża)
    // wewnątrz kontenerów interfejsu graficznego.
    auto gameCanvas = tgui::CanvasSFML::create({550, 600});
    gameCanvas->setPosition(0, 50); // Przesunięcie poniżej paska czasu
    gameCanvas->clear(sf::Color::Transparent); // Tło musi być przezroczyste dla widoczności
    sceneManager.gamePanel->add(gameCanvas); 
    
    // Konfiguracja przycisku wznawiania gry
    ButtonScenesPropertiesClass resumeButtonGenerated = ButtonScenesPropertiesClass(gui ,"Wznow", 190, 360, 170, 70, 
        tgui::Color(192, 192, 192), tgui::Color(200, 200, 200), tgui::Color(89, 43, 66), 5, 28);
    auto resumeButton = resumeButtonGenerated.getButton();
    sceneManager.pausePanel->add(resumeButton);
    
    // Zmienne pomocnicze dla animacji odliczania (3..2..1)
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
        sf::Vector2f positionHelper((winSize.x - circleXPos) / 2.f, (winSize.y - circleYPos) / 2.f);
        circle.setPosition(positionHelper);     

    // Zmienne stanu gry
    float sekundy = c.getElapsedTime().asSeconds();
    int minuty = 0;
    bool roundInProgress = false, gamePaused = false;
    int czasWSekundach, sekundySkrocone;
    sceneManager.gameInProgressTimeVar = 0;

    // --- LOGIKA OBSŁUGI ZDARZEŃ GUI ---
    
    // Obsługa przycisku rozpoczęcia gry
    mainButton->onPress([&sceneManager, &gameStartClick, &counterHelper, &c, &snake, &physicsClock]() {
        gameStartClick = true;
        counterHelper = 3;
        c.restart();
        physicsClock.restart(); // Reset zegara fizyki przy starcie nowej gry
        sceneManager.showGameScene();
    });

    // Obsługa wejścia do ustawień
    bool inSettingsMenu = false;
        SlidersAndCheckbox settingsVolumeSlider(195, 250);
        settingsVolumeSlider.createSlider(0, 100);
    SlidersAndCheckbox checkboxy(200, 400, 20);
    checkboxy.customLabelCreator(185, 360);

    settingsButton->getRenderer()->setTexture("../resources/ikonaUstawien.png");
    settingsButton->onPress([&sceneManager, &inSettingsMenu, &settingsVolumeSlider, &gui, &checkboxy](){
        inSettingsMenu = true;
        settingsVolumeSlider.dodajDoGui(gui);
        checkboxy.dodajCheckbox(gui);
        gui.add(checkboxy.labelCheckBoxSection);
        sceneManager.showSettingsScene();
    });

    // Obsługa pauzy
    pauseButton->getRenderer()->setTexture("../resources/ikonaPrzyciskuPauzy.png");
    pauseButton->onPress([&sceneManager, &c, &gamePaused](){
        gamePaused = true;
        sceneManager.gameInProgressTimeVar += c.getElapsedTime().asSeconds();
        c.restart();
        sceneManager.showPauseScene();
    });

    // Obsługa wznowienia gry
    resumeButton->onPress([&sceneManager, &c, &gamePaused, &physicsClock](){   
        gamePaused = false;
        c.restart();
        physicsClock.restart(); // Ważne: restart zegara po pauzie, aby uniknąć przeskoku w czasie
        sceneManager.showGameScene();
    });

    // =========================================================
    // --- GŁÓWNA PĘTLA APLIKACJI (GAME LOOP) ---
    // =========================================================
    while(window.isOpen()){
        
        // --- PĘTLA ZDARZEŃ SYSTEMOWYCH (INPUT) ---
        while(auto pollEventVarHelper = window.pollEvent()){
            Event event = *pollEventVarHelper;
            gui.handleEvent(event);
            
            if(event.is<Event::Closed>())
                window.close();
            
            // =========================================================
            // --- STEROWANIE WĘŻEM (OBSŁUGA KLAWIATURY) ---
            // =========================================================
            if(event.is<Event::KeyPressed>()){
                auto keyEvent = event.getIf<Event::KeyPressed>();
                
                if(keyEvent->code == Keyboard::Key::Escape){
                    window.close();
                }
                
                // Zmiana kierunku możliwa tylko podczas aktywnej rozgrywki
                if(roundInProgress && !gamePaused) {
                    // Przekazanie wektora kierunku do obiektu węża
                    if(keyEvent->code == Keyboard::Key::Up)    snake.ustawKierunek(sf::Vector2i(0, -1));
                    if(keyEvent->code == Keyboard::Key::Down)  snake.ustawKierunek(sf::Vector2i(0, 1));
                    if(keyEvent->code == Keyboard::Key::Left)  snake.ustawKierunek(sf::Vector2i(-1, 0));
                    if(keyEvent->code == Keyboard::Key::Right) snake.ustawKierunek(sf::Vector2i(1, 0));
                }
            }   
        }

        gui.draw(); // Rysowanie interfejsu użytkownika
        
        // --- LOGIKA ODLICZANIA PRZED STARTEM (3..2..1) ---
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
            // Rozpoczęcie właściwej gry po zakończeniu odliczania
            if(c.getElapsedTime().asSeconds() > 4){
                if(counterHelper == 0){
                    gameStartClick = false;
                    roundInProgress = true;
                    c.restart();
                    physicsClock.restart(); // Rozpoczęcie naliczania czasu dla logiki ruchu
                    sceneManager.showGameScene();
                }       
            }
        }

        // Sprzątanie widoku ustawień po wyjściu
        if(inSettingsMenu && !sceneManager.settingsPanel->isVisible()){
            inSettingsMenu = false;
            settingsVolumeSlider.usunZGui(gui);
            checkboxy.usunCheckboxy(gui);
        }

        // =========================================================
        // --- GŁÓWNA LOGIKA ROZGRYWKI (UPDATE & RENDER) ---
        // =========================================================
        if(roundInProgress && !gamePaused){
            
            // 1. OBLICZANIE DELTA TIME
            // Pobranie czasu od ostatniej klatki dla płynności ruchu
            float dt = physicsClock.restart().asSeconds();
            
            // 2. AKTUALIZACJA LOGIKI WĘŻA
            // Przesunięcie węża zgodnie z jego prędkością i kierunkiem
            snake.movementAktualizujWeza(dt);
            
            // 3. WYKRYWANIE KOLIZJI
            bool czyUderzyl = false;
            // Sprawdzenie czy wąż nie wyszedł poza obszar planszy (wymiary planszy w kratkach)
            snake.czyKolizjaZeSciana(55, 60, czyUderzyl); 
            
            if (czyUderzyl) {
                // Obsługa końca gry (Game Over)
                roundInProgress = false; 
                std::cout << "[SYSTEM] Wykryto kolizję ze ścianą. Koniec gry." << std::endl;
            }

            // 4. RYSOWANIE OBIEKTÓW GRY
            // Wyczyszczenie płótna przed narysowaniem nowej klatki
            gameCanvas->clear(sf::Color::Transparent);
            
            // Wywołanie metody rysującej z klasy węża
            snake.draw(*gameCanvas);
            
            // Wyświetlenie zaktualizowanego płótna
            gameCanvas->display();
            
            // =========================================================
            // --- KONIEC PĘTLI LOGICZNEJ ---
            // =========================================================

            // Aktualizacja licznika czasu gry
            sekundy = sceneManager.gameInProgressTimeVar + c.getElapsedTime().asSeconds();
            czasWSekundach = static_cast<int>(sekundy);
            minuty = czasWSekundach / 60;
            sekundySkrocone = czasWSekundach % 60;
            
            std::stringstream streamTimeUpdate;
            streamTimeUpdate << std::fixed <<  "Time: "<< minuty << ":" <<std::setw(2) << std::setfill('0') << sekundySkrocone;
            sceneManager.timeLabelGame->setText(streamTimeUpdate.str());
            sceneManager.gamePanel->add(sceneManager.timeLabelGame);
        }
        
        window.display();
    }

    return 0;
}