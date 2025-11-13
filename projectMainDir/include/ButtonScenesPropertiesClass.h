#ifndef BUTTONSCENESPROPERTIESCLASS_H
#define BUTTONSCENESPROPERTIES_H

#include <string>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class ButtonScenesPropertiesClass{            
    public:
        tgui::Gui& gui;
        tgui::Button::Ptr button;
        tgui::Color borderColor;
        tgui::Color bgColor;
        tgui::Color bgColorHover;

        
        ButtonScenesPropertiesClass(tgui::Gui& guiP);
        ButtonScenesPropertiesClass(tgui::Gui& guiP, const std::string& text , int x, int y, int width, int height, tgui::Color bgColor, 
                tgui::Color bgColorHover, tgui::Color borderColor, int border, int textSize);
        ButtonScenesPropertiesClass(tgui::Gui& guiP, int x, int y, int width, int height, tgui::Color borderColor, int border);

        tgui::Button::Ptr getButton();


        tgui::Panel::Ptr menuPanel;
        tgui::Panel::Ptr gamePanel;
        tgui::Panel::Ptr resultPanel;
        tgui::Panel::Ptr pausePanel;
        tgui::Panel::Ptr settingsPanel;
        tgui::Panel::Ptr nextRoundPopup;

        void appendToMenuScene(tgui::Panel::Ptr menuPanel, tgui::Button::Ptr startButton, tgui::Button::Ptr settingsButton);
        void appendBackToMainMenuButton(tgui::Panel::Ptr panel, tgui::Button::Ptr backToMainMenu);
        void appendToNextRoundPopup();

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

        void updateAllScenes(tgui::Button::Ptr startButton, tgui::Button::Ptr settingsButton, tgui::Button::Ptr backToMainMenu,
                tgui::Panel::Ptr menuPanel, tgui::Panel::Ptr pausePanel, tgui::Panel::Ptr resultPanel, tgui::Panel::Ptr settingsPanel,
                tgui::Panel::Ptr gamePanel);
};

#endif