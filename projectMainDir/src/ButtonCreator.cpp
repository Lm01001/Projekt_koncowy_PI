#include "ButtonScenesPropertiesClass.h"

#include <iostream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

    /*
    *   Konstruktor do szybszego tworzenia przycisku i od razu przypisywanie
    *   mu jego wlasnosci; w celu zmniejszenia ilosci kodu w f. main()
    */
    ButtonScenesPropertiesClass::ButtonScenesPropertiesClass(const std::string& text , int x, int y, int width, int height, tgui::Color bgColor, 
            tgui::Color bgColorHover, tgui::Color borderColor, int border, int textSize){
                button = tgui::Button::create(text);
                button->setPosition(x, y);
                button->setSize(width, height);
                button->getRenderer()->setBackgroundColor(bgColor);
                button->getRenderer()->setBackgroundColorHover(bgColorHover);
	            button->getRenderer()->setBorderColor(borderColor);
	            button->getRenderer()->setBorders(border);
                button->setTextSize(textSize);
    }   

    /*
    *   Getter do uzyskania utworzonego wczesniej przycisku konstruktorem
    */
    tgui::Button::Ptr ButtonPropertiesClass::getButton(){
        return button;
    }


    ///     Sekcja zarzadzania oknami scenami       ///     
    /*
    *   Menadzer, zarzadzanie scenami
    */
    ButtonScenesPropertiesClass::ButtonScenesPropertiesClass(tgui::Gui& gui) : gui(gui){
        createMenuScene();
        createGameScene();
        createResultScene();
        createPauseScene();
        createSettingsScene();
        createNextRoundPopup();

        showMenuScene();
    }

    /*
    *   Tworzenie scen opiera sie glownie na dodawaniu guzikow oraz ustawiania wizualnych
    *   aspektow scene, na koncu dodajac je do gui.
    *   Funkcje maja zazwyczaj, po jednym argumencie, a przy wywolaniu ich przekazujemy jako
    *   parametr wczesniej utworzone przyciski glownie do powrotu => uniwersalny dla wszystkich.
    *   Jedynie poza tym panelem do pokazywania rund
    */
    void ButtonScenesPropertiesClass::createMenuScene(tgui::Button::Ptr startButton, tgui::Button::Ptr settingsButton){
        menuPanel = tgui::Panel::create();
        menuPanel->setSize(100%, 100%);

        menuPanel->add(startButton);
        menuPanel->add(settingsButton);

        gui.add(menuPanel);
    }

    void ButtonScenesPropertiesClass::createGameScene(tgui::Button::Ptr backToMainMenu){
        gamePanel = tgui::Panel::create();
        gamePanel->setSize(100%, 100%);
        gamePanel->setVisible(false);

        gamePanel->add(backToMainMenu);

        gui.add(gamePanel);
    }

    void ButtonScenesPropertiesClass::createResultScene(tgui::Button::Ptr backToMainMenu){
        resultPanel = tgui::Panel::create();
        resultPanel->setSize(100%, 100%);
        resultPanel->setVisible(false);

        resultPanel->add(backToMainMenu);

        gui.add(resultPanel);
    }

    void ButtonScenesPropertiesClass::createPauseScene(tgui::Button::Ptr backToMainMenu){
        pausePanel = tgui::Panel::create();
        pausePanel->setSize(100%, 100%);
        pausePanel->setVisible(false);

        pausePanel->add(backToMainMenu);

        gui.add(pausePanel);
    }

    void ButtonScenesPropertiesClass::createSettingsScene(tgui::Button::Ptr backToMainMenu){
        settingsPanel = tgui::Panel::create();
        settingsPanel->setSize(100%, 100%);
        settingsPanel->setVisible(false);
    }

    void ButtonScenesPropertiesClass::createNextRoundPopup(){
        nextRoundPopup = tgui::Panel::create();
        nextRoundPopup->setSize(100%, 100%);
        nextRoundPopup->setVisible(false);

        gui.add(nextRoundPopup);
    }

    /*
    *   Wyswietlanie opiera sie na tym ze ustawiamy scene przez to ze 
    *   pozostale dostepne sceny ustawiane sa jako niewidzialne, niewidoczne
    */
    void ButtonScenesPropertiesClass::showMenuScene(){
        menuPanel->setVisible(true);
        gamePanel->setVisible(false);
        resultPanel->setVisible(false);
        pausePanel->setVisible(false);
        settingsPanel->setVisible(false);
        nextRoundPopup->setVisible(false);
    }

    void ButtonScenesPropertiesClass::showGameScene(){
        gamePanel->setVisible(false);
        menuPanel->setVisible(false);
        resultPanel->setVisible(false);
        pausePanel->setVisible(false);
        settingsPanel->setVisible(false);
        nextRoundPopup->setVisible(false);
    }

    void ButtonScenesPropertiesClass::showResultScene(){
        resultPanel->setVisible(false);
        menuPanel->setVisible(false);
        gamePanel->setVisible(false);
        pausePanel->setVisible(false);
        settingsPanel->setVisible(false);
        nextRoundPopup->setVisible(false);
    }

    void ButtonScenesPropertiesClass::showPauseScene(){
        pausePanel->setVisible(true);
        menuPanel->setVisible(false);
        gamePanel->setVisible(false);
        resultPanel->setVisible(false);
        settingsPanel->setVisible(false);
        nextRoundPopup->setVisible(false);
    }

    void ButtonScenesPropertiesClass::showSettingsScene(){
        settingsPanel->setVisible(true);
        menuPanel->setVisible(false);
        gamePanel->setVisible(false);
        resultPanel->setVisible(false);
        pausePanel->setVisible(false);
        nextRoundPopup->setVisible(false);
    }

    void ButtonScenesPropertiesClass::showNextRoundPopup(){
        nextRoundPopup->setVisible(true);
        menuPanel->setVisible(false);
        gamePanel->setVisible(false);
        resultPanel->setVisible(false);
        pausePanel->setVisible(false);
        settingsPanel->setVisible(false);
    }