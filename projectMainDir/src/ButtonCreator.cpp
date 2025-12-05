#include "ButtonScenesPropertiesClass.h"
#include "SlidersAndCheckbox.h"

#include <iostream>
#include <string>

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics.hpp>


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
    /*
    *   Funkcja do dodawania elementow do sceny
    *   poczatkowej/menu, czyli ustawienie ekranu
    *   poczatkowego i dodanie przycisku do
    *   przejscia do ustawien oraz rozpoczecia
    *   gry.
    */
    void ButtonScenesPropertiesClass::appendToMenuScene(tgui::Panel::Ptr menuPanel, tgui::Button::Ptr startButton, tgui::Button::Ptr startButtonEndless, tgui::Button::Ptr settingsButton){
        menuPanel->add(startButton);
        menuPanel->add(startButtonEndless);
        menuPanel->add(settingsButton);
        auto label = tgui::Label::create("Snake");
        label->setTextSize(60);
        label->getRenderer()->setTextColor(sf::Color(0, 1, 40));
        label->setPosition(175,180);
        menuPanel->add(label);
        menuPanel->getRenderer()->setBackgroundColor(sf::Color(115, 115, 98));

        gui.add(menuPanel, "Menu panel");
    }

      /**************************************/
     /*  Sekcja tworzenia baz/sampli scen  */
    /**************************************/
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
            label->setTextSize(28);
            label->getRenderer()->setTextColor(sf::Color::Black);
            label->setPosition(235, 25);
            label->getRenderer()->setTextColor(sf::Color(0, 0, 0));
            panel->add(label);

            auto planszaCanvas = tgui::CanvasSFML::create();
            planszaCanvas->setSize(550, 650);
            planszaCanvas->setPosition(0, 0);
            planszaCanvas->moveToBack();
            gui.add(planszaCanvas);
            sf::RectangleShape linia(sf::Vector2f(550, 1));
            linia.setPosition(sf::Vector2f(0, 550));
            linia.setOutlineColor(sf::Color::Black);
            linia.setOutlineThickness(2);
            planszaCanvas->draw(linia);
            
            planszaGry = sf::RectangleShape(sf::Vector2f(400, 400));
            planszaGry.setPosition(sf::Vector2f(75, 50));
            planszaGry.setFillColor(sf::Color(25, 153, 39));
            planszaGry.setOutlineColor(sf::Color(7, 43, 11));
            planszaGry.setOutlineThickness(9);
            planszaCanvas->draw(planszaGry);
            panel->add(planszaCanvas);

            planszaGryCanvas = tgui::CanvasSFML::create();
            planszaGryCanvas->setSize(400, 400);
            planszaGryCanvas->setPosition(75, 200);
            planszaGryCanvas->moveToFront();
            panel->add(planszaGryCanvas);

            timeLabelGame = tgui::Label::create("Time: 0:00");
            timeLabelGame->setWidgetName("timeLabelGame");
            auto wynik = tgui::Label::create("Wynik:");
            std::string serceE = u8"♡";
            auto zycia = tgui::Label::create("n x " + serceE);
            timeLabelGame->setPosition(30, 70);
            wynik->setPosition(210, 70);
            zycia->setPosition(440, 70);
            timeLabelGame->setTextSize(14);
            wynik->setTextSize(14);
            wynik->setTextSize(14);
            panel->add(timeLabelGame);
            panel->add(wynik);
            panel->add(zycia);

        }else if(panel->getWidgetName() == "Pause panel"){
            panel->getRenderer()->setBackgroundColor(sf::Color(122, 113, 101));
            auto label = tgui::Label::create("Pauza");
            label->setTextSize(45);
            label->getRenderer()->setTextColor(sf::Color(0, 0, 0));
            label->setPosition(200, 90);
            panel->add(label);
        }else if(panel->getWidgetName() == "Settings panel"){
            panel->getRenderer()->setBackgroundColor(sf::Color(136, 89, 102));
            auto label = tgui::Label::create("Ustawienia");
            label->setTextSize(45);
            label->getRenderer()->setTextColor(sf::Color(0, 0, 0));
            label->setPosition(150, 45);
            panel->add(label);
        }else if(panel->getWidgetName() == "Result panel"){
            auto backButton = createNewBackToMainMenuButton();
            backButton->moveToFront();
            panel->add(backButton);
        }    
    }


    /*******************************/
    /*  Sekcja wyswietlania scen  */
    /*****************************/

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
        timeLabelGame->setText("Time: 0:00");

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

    /*
    *   Aktualizacja wszystkich scen, czyli
    *   dodawanie przyciskow przede wszystkim
    *   i ustawienia dotyczace kwestii
    *   wizualnych bazujac na wczesnie utworzonych
    *   samplach.
    */
    void ButtonScenesPropertiesClass::updateAllScenes(tgui::Button::Ptr startButton, tgui::Button::Ptr startButtonEndless, tgui::Button::Ptr settingsButton, tgui::Button::Ptr pauseButton,
        tgui::Panel::Ptr menuPanel, 
            tgui::Panel::Ptr pausePanel, tgui::Panel::Ptr resultPanel, tgui::Panel::Ptr settingsPanel, tgui::Panel::Ptr gamePanel){
                appendToMenuScene(menuPanel, startButton, startButtonEndless, settingsButton);
                
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

      /*************************/
     /*  Sekcja na slidery    */    
    /*************************/

    SlidersAndCheckbox::SlidersAndCheckbox(int x, int y){
        slider = tgui::Slider::create();
        slider->setWidgetName("slider");
        slider->setPosition(x, y);
        slider->setSize(200, 20);
        
        labelName = tgui::Label::create("Glosnosc efektow");
        labelName->setTextSize(24);
        labelName->getRenderer()->setTextOutlineThickness(3);
        labelName->getRenderer()->setTextColor(sf::Color::White);
        labelName->setPosition(x - 15, y - 40);
        labelName->setWidgetName("labelName");

        labelVal = tgui::Label::create("0");
        labelVal->setTextSize(20);
        labelVal->getRenderer()->setTextColor(sf::Color::Black);
        labelVal->setPosition(x + 85, y + 25);
        labelVal->setWidgetName("labelVal");

        labelMin = tgui::Label::create("0");
        labelMin->setTextSize(18);
        labelMin->setPosition(x - 5, y + 25);
        labelMin->setWidgetName("labelMin");

        labelMax = tgui::Label::create("0");
        labelMax->setTextSize(18);
        labelMax->setPosition(x + 180, y + 25);
        labelMax->setWidgetName("labelMax");
    }

    void SlidersAndCheckbox::createSlider(int min, int max){
        sliderVal = min;
        minVal = min;
        maxVal = max;

        slider->setMinimum(min);
        slider->setMaximum(max);
        slider->setValue(min);

        labelMin->setText(std::to_string(min));
        labelMax->setText(std::to_string(max));
    }

    float SlidersAndCheckbox::getSliderVal(){
        return sliderVal;
    }

    void SlidersAndCheckbox::setSliderValue(float val){
        if(val >= minVal && val <= maxVal){
            sliderVal = val;
            slider->setValue(val);
            labelVal->setText(std::to_string((int)val));
        }
    }

    void SlidersAndCheckbox::dodajDoGui(tgui::Gui& gui){
        gui.add(slider);
        gui.add(labelName);
        gui.add(labelVal);
        gui.add(labelMin);
        gui.add(labelMax);
        
        slider->onValueChange([this](float val){
            sliderVal = val;
            labelVal->setText(std::to_string((int)val));
        });
    }

    void SlidersAndCheckbox::usunZGui(tgui::Gui& gui){
        gui.remove(gui.get("slider"));
        gui.remove(gui.get("labelName"));
        gui.remove(gui.get("labelVal"));
        gui.remove(gui.get("labelMin"));
        gui.remove(gui.get("labelMax"));
    }

      /***************************/
     /*  Sekcja na checkboxy    */    
    /***************************/

    SlidersAndCheckbox::SlidersAndCheckbox(int x, int y, int textSize){
        checkboxLatwy = tgui::CheckBox::create("Latwy");
        checkboxLatwy->setWidgetName("Latwy");
        checkboxLatwy->setPosition(x, y);
        checkboxLatwy->setTextSize(textSize);
        checkboxLatwy->setChecked(true);
        checkboxTrudny = tgui::CheckBox::create("Trudny");
        checkboxTrudny->setWidgetName("Trudny");
        checkboxTrudny->setPosition(x + 105, y);
        checkboxTrudny->setTextSize(textSize);
        checkboxTrudny->setChecked(false);
    }

    void SlidersAndCheckbox::customLabelCreator(int x, int y){
        labelCheckBoxSection = tgui::Label::create();
        labelCheckBoxSection->setText("Poziom trudnosci");
        labelCheckBoxSection->setWidgetName("labelCheckbox");
        labelCheckBoxSection->setTextSize(24);
        labelCheckBoxSection->setPosition(x, y);
        labelCheckBoxSection->getRenderer()->setTextOutlineThickness(3);
        labelCheckBoxSection->getRenderer()->setTextColor(sf::Color::White);
    }
    void SlidersAndCheckbox::dodajCheckbox(tgui::Gui& gui){
        gui.add(checkboxLatwy);
        gui.add(checkboxTrudny);

        checkboxLatwy->onChange([&](){
            if(checkboxLatwy->isChecked())
                checkboxTrudny->setChecked(false);
            else
                checkboxTrudny->setChecked(true);
        });
        checkboxTrudny->onChange([&](){
            if(checkboxTrudny->isChecked())
                checkboxLatwy->setChecked(false);
            else
                checkboxLatwy->setChecked(true);
        });
    }

    void SlidersAndCheckbox::usunCheckboxy(tgui::Gui& gui){
        gui.remove(checkboxLatwy);
        gui.remove(checkboxTrudny);
        gui.remove(labelCheckBoxSection);
    }