#include "SnakeDetails.h"
#include "SnakeGUI.h"

#include <iostream>
#include <string>
#include <ctime>

    /*
    *
    *   Funkcje do weza, dzialanie, tworzenie aktualizacja
    *   we wszystkich funkcji mozna zmienic argumenty, zalezy
    *   od potrzeby jakie parametry beda potrzebne do przekazania
    * 
    */
    
    SnakeDetails::SnakeDetails() : eatSound(loadEatSoundBuffer), 
    hitSound(loadHitSoundBuffer), nextLevelSound(loadNextLevelSoundBuffer){
        soundEffectsSetup();
        /*
        *   Ustawianie ciala weza, glowa(22) i nastepnie reszta ciala(23-24)
        *   
        */
        wazCialo.clear();
        wazCialo.push_back(sf::Vector2i(10, 10)); 
        wazCialo.push_back(sf::Vector2i(9, 10)); 
        wazCialo.push_back(sf::Vector2i(8, 10));

        /*
        *   Ustawianie poczatkowych wartosci dla wlasnosci weza 
        *   i zmiennych dla logik juz w grze.
        */
        wynik = 0;
        lvl = 1;
        zjedzonePrzedmioty = 0;
        dlugosc = (int)wazCialo.size();
        powerUp = "";
        /*  Predkosc weza, timer na starcie, brak kolizji na starcie  */
        predkoscRuchu = 0.2f; 
        timerRuchu = 0.f;  
        kolizja = false;  

        /*
        *   Przypisanie wartosci do wektora z kierunkiem ruchu,
        *   defaultowo kierunek w prawo
        */
        kierunekRuchu = sf::Vector2i(1, 0); 
        pozycjaJedzenia = sf::Vector2i(5, 5);
    }

    void SnakeDetails::soundEffectsSetup(){
        if(!loadEatSoundBuffer.loadFromFile("../resources/soundEffects/eatSound.wav"))
            std::cerr << "Blad - wczytywanie dzwieku jedzenia!\n";
        if(!loadHitSoundBuffer.loadFromFile("../resources/soundEffects/hitSound.wav"))
            std::cerr << "Blad - wczytywanie dzwieku uderzenia!\n";
        if(!loadNextLevelSoundBuffer.loadFromFile("../resources/soundEffects/nextLevelSound.wav"))
            std::cerr << "Blad - wczytywanie dzwieku nowego poziomu!\n";
        eatSound.setBuffer(loadEatSoundBuffer);
        hitSound.setBuffer(loadHitSoundBuffer); 
        nextLevelSound.setBuffer(loadNextLevelSoundBuffer);
    }

    void SnakeDetails::ustawKierunek(sf::Vector2i kierunek){
        //zmienna z klasy SnakeDetails - przypisanie jej wartosci
        this->kierunekRuchu = kierunek;
        //przekazanego jako parametr wektora
    }

    void SnakeDetails::czyKolizjaZeSciana(int szerokoscPlanszy, int wysokoscPlanszy, bool &kolizja){
        sf::Vector2i head = wazCialo[0];  //pozycja glowy weza
        if(head.x < 0 || head.x >= szerokoscPlanszy || head.y < 0 || head.y >= wysokoscPlanszy){
            kolizja = true;
            this->kolizja = true;
            playHitSound();
        } else {
            kolizja = false;
            this->kolizja = false;
        }
        //sprawdzanie czy kolizja ze sciana, zobaczyc na pozycje
        //planszy i rozmiar i odpowiednio dodac marginesy 
    }

    void SnakeDetails::kolejnyLevel(tgui::CanvasSFML& planszaGry, int brama){
        //dodanie ciemniejszego koloru na brame do kolejnego etapu
        //mozna tez dodac strzalke gdzie wejsc
        //podac szerokosc bramy
        playNextLevelSound();//ew po przejsciu, ale chwilowo
    }

    void SnakeDetails::movementAktualizujWeza(float czasOdPoprzedniejKlatki){
        //waz rusza sie tylko co predkoscRuchu sekund
        timerRuchu += czasOdPoprzedniejKlatki;
        if(timerRuchu < predkoscRuchu)
        return;
        timerRuchu = 0.f;

        //ruch segmentow od ogona do glowy
        for(int i = wazCialo.size() - 1; i > 0; i--) {
            wazCialo[i] = wazCialo[i - 1];
        }
        //przesuniecie glowy na podstawie kierunku
        wazCialo[0] += kierunekRuchu;
        sf::Vector2i head = wazCialo[0];
        //sprawdzanie kolizji ze sciana
        if(head.x < 0 || head.x >= szerokoscPlanszy || head.y < 0 || head.y >= wysokoscPlanszy){
            kolizja = true;
            playHitSound();
            przegranaGracza(wynik, dlugosc, lvl);
            return;
        }
        //sprawdzanie zjedzenia przedmiotu
        if(head == pozycjaJedzenia){
            playEatSound();
            //1. wydluzanie weza
            wazCialo.push_back(wazCialo.back());
            dlugosc = (int)wazCialo.size();
            //2. zwiekszenie wyniku
            aktualizujWynik(10);  //+10 punktow za zjedzenie
            zjedzonePrzedmioty++;
            // co 3 zjedzone przedmioty losujemy power-up
            if(zjedzonePrzedmioty % 3 == 0){
                losowaniePowerUpa();
            }
            //4. ustawienie nowej pozycji jedzenia
            pozycjaJedzenia.x = rand() % szerokoscPlanszy;
            pozycjaJedzenia.y = rand() % wysokoscPlanszy;
            //5. dzwiek zjadania
            playEatSound();
        }
        //kolizja z wlasnym ciałem
        for(int i = 1; i < (int)wazCialo.size(); ++i){
            if(wazCialo[i] == head){
                kolizja = true;
                playHitSound();
                //wywolanie logiki przegranej
                przegranaGracza(wynik, dlugosc, lvl);
                return;
            }
        }
        //aktualizacja timera i przesuniecie weza
        //mozna dodac warunek ze gdy zmienna ze zjedzonymi
        //przedmiotami ma jakas wartosc
        //np. co (200) losowany jest 1 z 4 powerupow
        //warunek jesli osiagniety prog wyniku zwieksza sie waz
        //wywolanie wewnatrz funkcji losowaniePowerUpa
    }

    void SnakeDetails::draw(tgui::CanvasSFML& planszaGry){
        // 1. Wyczyść canvasa (tło planszy)
        planszaGry.clear(sf::Color(30, 30, 30)); // ciemne tło 
        // 2. Stała – rozmiar jednego „kafelka” planszy w pikselach
        const float tileSize = 20.f;
        // 3. Rysowanie ciała węża
        sf::RectangleShape segmentShape(sf::Vector2f(tileSize, tileSize));

        for (std::size_t i = 0; i < wazCialo.size(); ++i){
            // głowa inny kolor
            if(i == 0)
                segmentShape.setFillColor(sf::Color::Green);
            else
                segmentShape.setFillColor(sf::Color(0, 150, 0));

            sf::Vector2f segmentShapePosVar((wazCialo[i].x) * tileSize, (wazCialo[i].y) * tileSize);
            segmentShape.setPosition(segmentShapePosVar);
            planszaGry.draw(segmentShape);
        }

        // 4. Rysowanie jedzenia
        sf::RectangleShape foodShape(sf::Vector2f(tileSize, tileSize));
        foodShape.setFillColor(sf::Color::Red);
        sf::Vector2f foodPosVar((pozycjaJedzenia.x) * tileSize, (pozycjaJedzenia.y) * tileSize);
        foodShape.setPosition(foodPosVar);
        planszaGry.draw(foodShape);

        // 5. Zaktualizowanie zawartości canvasa
        planszaGry.display();
    }

    
    void SnakeDetails::aktualizujWynik(int wynik){
            //Zwiekszanie wynik np po zjedzeniu przedmiotu np. o 10
        this->wynik += wynik;
    }

    void SnakeDetails::aktualizujDlugosc(int dlugosc){
        this->dlugosc = dlugosc;
    }

    void SnakeDetails::kolejnyEtap(int lvl){
        //ustawiamy nowy poziom
        this->lvl = lvl;
        //lekko przyspieszamy weaz przy kazdym etapie
        if(predkoscRuchu > 0.05f)  //zeby nie bylo nieskonczenie szybko
        predkoscRuchu *= 0.9f;  //10% szybciej na nastepnych levelach
        playNextLevelSound();
        //jesli zostanie osiagniety wymagany wynik to etap inkrementacja
        //zatrzymanie stopera - dodac dodatkowy argument albo
        //typu float przetrzymujacej czas lub Clock
    }

    void SnakeDetails::przegranaGracza(int wynik, int dlugosc, int lvl){
        //zapamietujemy statystyki z momentu przegranej
        this->wynik = wynik;
        this->dlugosc = dlugosc;
        this->lvl = lvl;

        kolizja = true;
        playHitSound();
        //reset wartosci aktualnego weza
        //mozliwe ze usuniecie weza, niekoniecznie
        //po prostu reset bo ekran po przegranej przenosi
        //do menu i tak
    }

    void SnakeDetails::wyswietlStatystyki(int wynik, int dlugosc, int lvl){
        std::cout << "===STATYSTYKI GRY===" << std::endl;
        std::cout << "Wynik: " << wynik << std::endl;
        std::cout << "Dlugosc: " << dlugosc << std::endl;
        std::cout << "Poziom: " << lvl << std::endl;
        std::cout << "PowerUp: " << powerUp << std::endl;
        //wyswietlanie statystyk
        //przekazanie gdzies tych przypisanie, zeby wykorzystac
        //do dodania do sceny
        //bedzie wywolywana i po przegranej i koncu gry
    }

    void SnakeDetails::losowaniePowerUpa(){
        int r = rand() % 4; //losuje 0,1,2,3
        if(r == 0) {
            //+50 punktow
            powerUp = "bonus +50 pkt";
            wynik += 50;
        } else if(r == 1) {
            //skrocenie weza (jesli jest dlugi)
            powerUp = "Skrocenie weza";
            if(wazCialo.size() > 3){
                wazCialo.pop_back();
            }
            dlugosc = (int)wazCialo.size();
        } else if(r == 2) {
            //przyspieszenie
            powerUp = "Przyspieszenie";
            predkoscRuchu *= 0.8f;
            if(predkoscRuchu < 0.05f)
            predkoscRuchu = 0.05f;
        } else {
            //zwolnienie
            powerUp = "Zwolnienie";
            predkoscRuchu *= 1.2f;  //wieksza wartosc = wolniej
            if(predkoscRuchu > 0.6f)
            predkoscRuchu = 0.6f; //limit predkosci
        }
    }
    
    
    void SnakeDetails::playEatSound(){
        eatSound.play();
    }

    void SnakeDetails::playHitSound(){
        hitSound.play();
    }

    void SnakeDetails::playNextLevelSound(){
        nextLevelSound.play();
    }

    /*
    *   Ustawianie kwestii zwiazanych z GUI
    *   wygladem wizualnych scen, czyli nie
    *   bezposrednio z obiektem weza samego
    *   w sobie.
    */
    void SnakeGui::ustawTloOkna(sf::RenderWindow& window, sf::Color kolor){
        window.clear(kolor);
    }

    sf::RectangleShape SnakeGui::stworzPasekOkna(int szerokosc, int wysokosc, sf::Color kolor){
        sf::RectangleShape topBar(sf::Vector2f(szerokosc, wysokosc));
        topBar.setFillColor(kolor);
        topBar.setPosition(sf::Vector2f(0, 0));
        return topBar;
    }   
    
    sf::RectangleShape SnakeGui::stworzPrzycisk(int x, int y, int szerokosc, int wysokosc, sf::Color kolor){
        sf::RectangleShape button(sf::Vector2f(szerokosc, wysokosc));
        button.setFillColor(kolor);
        button.setPosition(sf::Vector2f(x, y));
        return button;
    }

