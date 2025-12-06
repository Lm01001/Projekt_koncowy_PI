#ifndef SNAKEDETAILS_H
#define SNAKEDETAILS_H

#include <string>
#include <vector>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/Renderer/SFML-Graphics/CanvasSFML.hpp>

class SnakeDetails{
    public:
        std::vector<sf::Vector2i> wazCialo;
        std::vector<sf::Vector2i> przeszkody;

        int wynik, dlugosc, lvl, zjedzonePrzedmioty;
        int progPunktowyBramy;
        int szerokoscPlanszy, wysokoscPlanszy;
        std::string powerUp;
        sf::Vector2i kierunekRuchu;
        sf::Vector2i pozycjaJedzenia;
        sf::Vector2i pozycjaBramy;
        float predkoscRuchu, timerRuchu;
        bool kolizja, trybEndless;
        char direction;

        SnakeDetails();
        void ustawTrybEndless(bool czyTrybEndless);
        void generujPrzeszkody();
        void ustawKierunek(sf::Vector2i kierunek);
        void movementAktualizujWeza(float czasOdPoprzedniejKlatki);
        void draw(tgui::CanvasSFML& planszaGryCanvas);
        void czyKolizjaZeSciana(int szerokoscPlanszy, int wysokoscPlanszy, bool &kolizja);
        void kolejnyLevel(tgui::CanvasSFML& planszaGry, int brama);
        void aktualizujWynik(int wynik);
        void aktualizujDlugosc(int dlugosc);
        void kolejnyEtap(int lvl);
        void losowaniePowerUpa();
        sf::Vector2i generujNowaPozycjeJedzenia(int szerokoscPlanszy, int wysokoscPlanszy);

        tgui::CanvasSFML::Ptr resultCanvas;
        tgui::Panel::Ptr resultPanel;
        tgui::Label::Ptr resultPanelTitle;
        tgui::Label::Ptr resultPanelScore;
        tgui::Label::Ptr resultPanelLength;
        tgui::Label::Ptr resultPanelLvl;
        bool gameOver;
        sf::Clock clockForWaiting;

        void przegranaGracza(int wynik, int dlugosc, int lvl, sf::Clock clockForWaiting);
        tgui::Panel::Ptr wyswietlStatystyki(tgui::Panel::Ptr resultPanel, int wynik, int dlugosc, int lvl);
        

        sf::SoundBuffer loadEatSoundBuffer;
        sf::SoundBuffer loadHitSoundBuffer;
        sf::SoundBuffer loadNextLevelSoundBuffer;
        sf::Sound eatSound;
        sf::Sound hitSound;
        sf::Sound nextLevelSound;

        void soundEffectsSetup();
        void playEatSound();
        void playHitSound();
        void playNextLevelSound();
};

#endif