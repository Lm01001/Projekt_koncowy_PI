#ifndef BUTTONPROPERTIESCLASS_H
#define BUTTONPROPERTIES_H

#include <string>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class ButtonScenesPropertiesClass{            
    public:
        tgui::Gui& gui;
        tgui::Button::Ptr button;
        
        ButtonScenesPropertiesClass(tgui::Gui& gui);
        ButtonScenesPropertiesClass(const std::string& text , int x, int y, int width, int height, tgui::Color bgColor, 
                tgui::Color bgColorHover, tgui::Color borderColor, int border, int textSize);

        tgui::Button::Ptr getButton();

        
        tgui::Panel::Ptr menuPanel;
        tgui::Panel::Ptr gamePanel;
        tgui::Panel::Ptr resultPanel;
        tgui::Panel::Ptr pausePanel;
        tgui::Panel::Ptr settingsPanel;
        tgui::Panel::Ptr nextRoundPopup;

        void createMenuScene();
        void createGameScene();
        void createResultScene();
        void createPauseScene();
        void createSettingsScene();
        void createNextRoundPopup();

        void showMenuScene();
        void showGameScene();
        void showResultScene();
        void showPauseScene();
        void showSettingsScene();
        void showNextRoundPopup();
};

#endif