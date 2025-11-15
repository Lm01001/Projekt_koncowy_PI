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

        gui.add(menuPanel, "Menu panel");
    }
    void ButtonScenesPropertiesClass::appendToMenuScene(tgui::Panel::Ptr menuPanel, tgui::Button::Ptr startButton, tgui::Button::Ptr settingsButton){
        menuPanel->add(startButton);
        menuPanel->add(settingsButton);
        auto label = tgui::Label::create("Snake");
        label->setTextSize(60);
        label->getRenderer()->setTextColor(sf::Color(0, 1, 40));
        label->setPosition(175,180);
        menuPanel->add(label);

        gui.add(menuPanel, "Menu panel");
    }

    void ButtonScenesPropertiesClass::createGameScene(){
        gamePanel = tgui::Panel::create();
        gamePanel->setSize(550, 650);
        gamePanel->setVisible(false);
        
        gui.add(gamePanel, "Game panel");
    }

    void ButtonScenesPropertiesClass::createResultScene(){
        resultPanel = tgui::Panel::create();
        resultPanel->setSize(550, 650);
        resultPanel->setVisible(false);

        gui.add(resultPanel, "Result panel");
    }

    void ButtonScenesPropertiesClass::createPauseScene(){
        pausePanel = tgui::Panel::create();
        pausePanel->setSize(550, 650);
        pausePanel->setVisible(false);

        gui.add(pausePanel, "Pause panel");
    }

    void ButtonScenesPropertiesClass::createSettingsScene(){
        settingsPanel = tgui::Panel::create();
        settingsPanel->setSize(550, 650);
        settingsPanel->setVisible(false);

        gui.add(settingsPanel, "Settings panel");
    }

    void ButtonScenesPropertiesClass::createNextRoundPopup(){
        nextRoundPopup = tgui::Panel::create();
        nextRoundPopup->setSize(550, 650);
        nextRoundPopup->setVisible(false);
        nextRoundPopup->getRenderer()->setBackgroundColor(sf::Color::Transparent);
		nextRoundPopup->getRenderer()->setBorders(0);
        
        gui.add(nextRoundPopup, "NextRound Popup");
    }

    /*
    *   Dodatkowa metoda do utworzenia nowego guzika powrotu dla kazdej ze scen
    *   uzywanie tego samego dodawalo tylko do tej dla, ktorej ostatniej
    *   byla wywolana funkcja
    */
    tgui::Button::Ptr ButtonScenesPropertiesClass::createNewBackToMainMenuButton(){
        auto button = tgui::Button::create();
        button->setPosition(495, 30);
        button->setSize(35, 35);	        
        button->getRenderer()->setBorderColor(tgui::Color(89, 43, 66));
        button->getRenderer()->setBorders(0);
        button->getRenderer()->setTexture("../resources/ikonaPowrotuDoMenu.png");
        button->onPress([this](){
            showMenuScene();
        });
        return button;
    }

    void ButtonScenesPropertiesClass::appendBackToMainMenuButton(tgui::Panel::Ptr panel){
        if(gui.get("Game panel") == panel){
            panel->getRenderer()->setBackgroundColor(sf::Color(163, 150, 135));
            auto label = tgui::Label::create("Level");
            label->setTextSize(45);
            label->setPosition(200, 30);
            label->getRenderer()->setTextColor(sf::Color(0, 0, 0));
            panel->add(label);
        }else if(panel->getWidgetName() == "Pause panel"){
            panel->getRenderer()->setBackgroundColor(sf::Color(122, 113, 101));
            auto label = tgui::Label::create("Pauza");
            label->setTextSize(45);
            label->getRenderer()->setTextColor(sf::Color(0, 0, 0));
            label->setPosition(200, 90);
            panel->add(label);
        }else if(panel->getWidgetName() == "Result panel"){
            panel->getRenderer()->setBackgroundColor(sf::Color(136, 0, 23));
            auto label = tgui::Label::create("Wynik:");
            label->setTextSize(30);
            label->setPosition(100, 45);
            panel->add(label);
        }else if(panel->getWidgetName() == "Settings panel"){
            panel->getRenderer()->setBackgroundColor(sf::Color(136, 89, 102));
            auto label = tgui::Label::create("Ustawienia");
            label->setTextSize(45);
            label->getRenderer()->setTextColor(sf::Color(0, 0, 0));
            label->setPosition(150, 45);
            panel->add(label);
        }
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
        gamePanel->setVisible(true);
        menuPanel->setVisible(false);
        resultPanel->setVisible(false);
        pausePanel->setVisible(false);
        settingsPanel->setVisible(false);
        nextRoundPopup->setVisible(false);
    }

    void ButtonScenesPropertiesClass::showResultScene(){
        resultPanel->setVisible(true);
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

    void ButtonScenesPropertiesClass::updateAllScenes(tgui::Button::Ptr startButton, tgui::Button::Ptr settingsButton, tgui::Button::Ptr pauseButton,
        tgui::Panel::Ptr menuPanel, 
            tgui::Panel::Ptr pausePanel, tgui::Panel::Ptr resultPanel, tgui::Panel::Ptr settingsPanel, tgui::Panel::Ptr gamePanel){
                appendToMenuScene(menuPanel, startButton, settingsButton);
                
                appendBackToMainMenuButton(gamePanel);
                gamePanel->add(pauseButton);

                appendBackToMainMenuButton(settingsPanel);
                settingsPanel->add(createNewBackToMainMenuButton());

                appendBackToMainMenuButton(pausePanel);
                pausePanel->add(createNewBackToMainMenuButton());

                appendBackToMainMenuButton(resultPanel);
                resultPanel->add(createNewBackToMainMenuButton()); 

                showMenuScene();
    }