#ifndef SNAKEDETAILS_H
#define SNAKEDETAILS_H

#include <string>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class SnakeDetails{
    public:
        int wynik, dlugosc, lvl, zjedzonePrzedmioty;
        std::string powerUp;
        SnakeDetails(int wynik, int dlugosc, int lvl, std::string powerUp); // ???????


        std::vector<sf::Vector2i> wazCialo;
        sf::Vector2i kierunekRuchu;
        float predkoscRuchu, timerRuchu;
        bool kolizja;

        SnakeDetails();
        void ustawKierunek(sf::Vector2i kierunek);
        void movementAktualizujWeza(float czasOdPoprzedniejKlatki);
        void draw(tgui::CanvasSFML& planszaGry);
        void czyKolizjaZeSciana(int szerokoscPlanszy, int wysokoscPlanszy);
        void kolejnyLevel(tgui::CanvasSFML& planszaGry, int brama);
        void aktualizujWynik(int wynik);
        void aktualizujDlugosc(int dlugosc);
        void kolejnyEtap(int lvl);
        int losowaniePowerUpa();
        void przegranaGracza(int wynik, int dlugosc, int lvl); //???
        void wyswietlStatystyki(int wynik, int dlugosc, int lvl);

        sf::SoundBuffer loadEatSoundBuffer;
        sf::SoundBuffer loadHitSoundBuffer;
        sf::SoundBuffer loadNextLevelSoundBuffer;
        sf::Sound eatSound;
        sf::Sound hitSound;
        sf::Sound nextLevelSound;
        void playEatSound();
        void playHitSound();
        void playNextLevelSound();
};

#endif