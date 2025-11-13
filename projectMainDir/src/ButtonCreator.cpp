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
    *   aspektow scene, na koncu dodajac je do gui
    */
    void ButtonScenesPropertiesClass::createMenuScene(){

    }

    void ButtonScenesPropertiesClass::createGameScene(){

    }

    void ButtonScenesPropertiesClass::createResultScene(){

    }

    void ButtonScenesPropertiesClass::createPauseScene(){

    }

    void ButtonScenesPropertiesClass::createSettingsScene(){

    }

    void ButtonScenesPropertiesClass::createNextRoundPopup(){

    }

    /*
    *   Wyswietlanie opiera sie na tym ze ustawiamy scene przez to ze 
    *   pozostale dostepne sceny ustawiane sa jako niewidzialne, niewidoczne
    */
