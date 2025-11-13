#include "ButtonScenesPropertiesClass.h"

#include <iostream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <string>

    /*
    *   Konstruktor do szybszego tworzenia przycisku i od razu przypisywanie
    *   mu jego wlasnosci; w celu zmniejszenia ilosci kodu w f. main().
    */
    ButtonScenesPropertiesClass::ButtonScenesPropertiesClass(tgui::Gui& gui, const std::string& text , int x, int y, int width, int height, tgui::Color bgColor, 
            tgui::Color bgColorHover, tgui::Color borderColor, int border, int textSize) : gui(gui){
                button = tgui::Button::create();
                button->setText(text);
                button->setPosition(x, y);
                button->setSize(width, height);
                button->getRenderer()->setBackgroundColor(bgColor);
                button->getRenderer()->setBackgroundColorHover(bgColorHover);
	            button->getRenderer()->setBorderColor(borderColor);
	            button->getRenderer()->setBorders(border);
                button->setTextSize(textSize);
    }  
    /*
    *   Konstruktor do szybszego tworzenia przyciskow, ale bez tekstu
    *   oraz koloru tla przeznaczony do tworzenia przyciskow
    *   z obrazami, grafikami jako tlo.
    */
    ButtonScenesPropertiesClass::ButtonScenesPropertiesClass(tgui::Gui& gui, int x, int y, int width, int height,  
        tgui::Color borderColor, int border) : gui(gui){
                button = tgui::Button::create();
                button->setPosition(x, y);
                button->setSize(width, height);
                button->getRenderer()->setBackgroundColor(bgColor);
                button->getRenderer()->setBackgroundColorHover(bgColorHover);
	            button->getRenderer()->setBorderColor(borderColor);
	            button->getRenderer()->setBorders(border);
    } 
    

    /*
    *   Getter do uzyskania utworzonego wczesniej przycisku konstruktorem
    */
    tgui::Button::Ptr ButtonScenesPropertiesClass::getButton(){
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
    }

    /*
    *   Tworzenie scen opiera sie glownie na dodawaniu guzikow oraz ustawiania wizualnych
    *   aspektow scene, na koncu dodajac je do gui.
    *   Funkcje maja zazwyczaj, po jednym argumencie, a przy wywolaniu ich przekazujemy jako
    *   parametr wczesniej utworzone przyciski glownie do powrotu => uniwersalny dla wszystkich.
    *   Jedynie poza tym panelem do pokazywania rund
    */
   void ButtonScenesPropertiesClass::createMenuScene(){
        menuPanel = tgui::Panel::create();
        menuPanel->setSize(550, 650);

        gui.add(menuPanel);
    }
    void ButtonScenesPropertiesClass::appendToMenuScene(tgui::Panel::Ptr menuPanel, tgui::Button::Ptr startButton, tgui::Button::Ptr settingsButton){
        menuPanel->add(startButton);
        menuPanel->add(settingsButton);

        gui.add(menuPanel);
    }

    void ButtonScenesPropertiesClass::createGameScene(){
        gamePanel = tgui::Panel::create();
        gamePanel->setSize(550, 650);
        gamePanel->setVisible(false);

        gui.add(gamePanel);
    }

    void ButtonScenesPropertiesClass::createResultScene(){
        resultPanel = tgui::Panel::create();
        resultPanel->setSize(550, 650);
        resultPanel->setVisible(false);

        gui.add(resultPanel);
    }

    void ButtonScenesPropertiesClass::createPauseScene(){
        pausePanel = tgui::Panel::create();
        pausePanel->setSize(550, 650);
        pausePanel->setVisible(false);

        gui.add(pausePanel);
    }

    void ButtonScenesPropertiesClass::createSettingsScene(){
        settingsPanel = tgui::Panel::create();
        settingsPanel->setSize(550, 650);
        settingsPanel->setVisible(false);

        gui.add(settingsPanel);
    }

    void ButtonScenesPropertiesClass::createNextRoundPopup(){
        nextRoundPopup = tgui::Panel::create();
        nextRoundPopup->setSize(550, 650);
        nextRoundPopup->setVisible(false);

        gui.add(nextRoundPopup);
    }


    void ButtonScenesPropertiesClass::appendBackToMainMenuButton(tgui::Panel::Ptr panel, tgui::Button::Ptr backToMainMenu){
        panel->add(backToMainMenu);
        gui.add(panel);
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

    void ButtonScenesPropertiesClass::updateAllScenes(tgui::Button::Ptr startButton, tgui::Button::Ptr settingsButton, tgui::Button::Ptr backToMainMenu,
            tgui::Panel::Ptr menuPanel, tgui::Panel::Ptr pausePanel, tgui::Panel::Ptr resultPanel, tgui::Panel::Ptr settingsPanel, tgui::Panel::Ptr gamePanel){
                appendToMenuScene(menuPanel, startButton, settingsButton);
                appendBackToMainMenuButton(gamePanel, backToMainMenu);
                appendBackToMainMenuButton(pausePanel, backToMainMenu);
                appendBackToMainMenuButton(resultPanel, backToMainMenu);
                appendBackToMainMenuButton(settingsPanel, backToMainMenu);
                showMenuScene();
    }