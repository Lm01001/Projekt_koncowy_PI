#ifndef SNAKEDETAILS_H
#define SNAKEDETAILS_H

#include <string>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/Renderer/SFML-Graphics/CanvasSFML.hpp>

class SnakeDetails{
    public:
        std::vector<sf::Vector2i> wazCialo;

        int wynik, dlugosc, lvl, zjedzonePrzedmioty;
        std::string powerUp;
        sf::Vector2i kierunekRuchu;
        sf::Vector2i pozycjaJedzenia;
        float predkoscRuchu, timerRuchu;
        bool kolizja;
        int szerokoscPlanszy = 10;
        int wysokoscPlanszy = 10;

        SnakeDetails();
        void ustawKierunek(sf::Vector2i kierunek);
        void movementAktualizujWeza(float czasOdPoprzedniejKlatki);
        void draw(tgui::CanvasSFML& planszaGryCanvas);
        void czyKolizjaZeSciana(int szerokoscPlanszy, int wysokoscPlanszy, bool &kolizja);
        void kolejnyLevel(tgui::CanvasSFML& planszaGry, int brama);
        void aktualizujWynik(int wynik);
        void aktualizujDlugosc(int dlugosc);
        void kolejnyEtap(int lvl);
        void losowaniePowerUpa();
        void przegranaGracza(int wynik, int dlugosc, int lvl); //???
        void wyswietlStatystyki(int wynik, int dlugosc, int lvl);

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