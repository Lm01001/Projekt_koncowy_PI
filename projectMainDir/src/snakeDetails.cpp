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
        this->szerokoscPlanszy = 20;
        this->wysokoscPlanszy = 20;
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
        // Brama w prawym górnym rogu
        pozycjaBramy = sf::Vector2i(szerokoscPlanszy - 1, 0); 
        // Generowanie pozycji z uwzględnieniem węża i bramy
        pozycjaJedzenia = generujNowaPozycjeJedzenia(szerokoscPlanszy, wysokoscPlanszy); 
        direction = 'r';
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
        /*
        *   Zmienna z zadeklarowana w headerFile tej klasy
        *   przypisanie jej wartosci w celu ustawienia kierunku ruchu
        *   , wartosc przekazana jako parametr w postaci wektora int'ow
        */
        this->kierunekRuchu = kierunek;
    }

    void SnakeDetails::czyKolizjaZeSciana(int szerokoscPlanszy, int wysokoscPlanszy, bool &kolizja){
        /*  Ustawienie pozycji glowy  */
        sf::Vector2i head = wazCialo[0];  
        if(head.x < 0 || head.x >= szerokoscPlanszy || head.y < 0 || head.y >= wysokoscPlanszy){
            kolizja = true;
            this->kolizja = true;
            przegranaGracza(wynik, dlugosc, lvl);
        }else{
            kolizja = false;
            this->kolizja = false;
        } 
    }

    sf::Vector2i SnakeDetails::generujNowaPozycjeJedzenia(int szerokosc, int wysokosc){
         sf::Vector2i nowaPozycja;
        bool pozycjaZajeta = true;

        while (pozycjaZajeta) {
            // Losowanie pozycji
            nowaPozycja.x = rand() % szerokosc;
            nowaPozycja.y = rand() % wysokosc;
            pozycjaZajeta = false;

            // 1. Sprawdzenie czy nie na ciele węża
            for(const auto& segment : wazCialo){
                if(segment == nowaPozycja){
                    pozycjaZajeta = true;
                    break;
                }
            }
            // 2. Sprawdzenie czy nie na bramie wyjściowej
                if(nowaPozycja == pozycjaBramy) 
                    pozycjaZajeta = true;
        }
        return nowaPozycja;
    }

    void SnakeDetails::kolejnyLevel(tgui::CanvasSFML& planszaGry, int brama){
        /*
            Dodanie bramy (png) jako wyjscia z poziomu
            ustawianie albo linii pod albo czegos
            ze po kontakcie wczytanie nowego poziomu
                !!!!!!!!!!!!!!!!!!!!!!
                                                        */
        playNextLevelSound();
    }

    void SnakeDetails::movementAktualizujWeza(float czasOdPoprzedniejKlatki){
        /*  
        *   Waz porusza sie co wartosc zmiennej predkoscRuchu
        *   ustawionej w konstruktorze (0.2f) defaultowo,
        *   jest to predkosc dla latwego poziomu trudnosci.
        */
        gameOver = false;
        timerRuchu += czasOdPoprzedniejKlatki;
        if(timerRuchu < predkoscRuchu)
            return;
        timerRuchu = 0.f;

        /*
        *   Ruch segmentow, blokow z ktorych sklada
        *   sie waz. Od ogona do glowy.
        */
        for(int i = wazCialo.size() - 1; i > 0; i--) {
            wazCialo[i] = wazCialo[i - 1];
        }
        
        /*  Przesuniecie glowy na bazie kierunku ruchu  */
        wazCialo[0] += kierunekRuchu;
        sf::Vector2i head = wazCialo[0];
        
        /*  Sprawdzenie wystapienia kolizji ze sciana   */
        if(head.x < 0 || head.x >= szerokoscPlanszy || head.y < 0 || head.y >= wysokoscPlanszy){
            kolizja = true;
            gameOver = true;
            przegranaGracza(wynik, dlugosc, lvl);
            return;
        }

        // Sprawdzenie kolizji z bramą

        if (head == pozycjaBramy) {
            // Przejście do następnego poziomu
            kolejnyEtap(lvl + 1);
            return;
        }

        /*  Sprawdzenie zjedzenia przedmiotu*/

        /*      Ustawic wydluzenie weza nie co kazdy zjedzony
                tylko np 2, ze modulo z dzielenia wyniku przez
                cos     
                        !!!!!!!!!!!!!!!!!!!!!!!
                                                                */

        
        /*
        *   Instrukcja sprawdzajaca, obslugujaca zjadanie
        *   przedmiotow przez weza.
        *   W przypadku pokrycia sie pozycji glowy z 
        *   przedmiotem wydluza sie cialo weza.
        *   Po zjedzeniu wynik sie zwieksza, a jesli zostaly
        *   zjedzone 3 to losowany jest powerup - wywolanie
        *   funkcji obslugujacej losowanie.
        */
        if(head == pozycjaJedzenia){
            aktualizujWynik(10); 
            zjedzonePrzedmioty++;

            if(zjedzonePrzedmioty % 2 == 0){
                // Dodajemy nowy segment
                wazCialo.push_back(wazCialo.back());
                dlugosc = (int)wazCialo.size();
                aktualizujDlugosc(1);
            }
            if(zjedzonePrzedmioty % 3 == 0){
                losowaniePowerUpa();
            }
            /*
            *   Po zjedzeniu losowanie nowej pozycji
            *   dla nowego przedmiotu i wywolanie
            *   funkcji do wydania dzwieku oznaczajacego
            *   zjedzenie przedmiotu.
            */
            pozycjaJedzenia = generujNowaPozycjeJedzenia(szerokoscPlanszy, wysokoscPlanszy);

            playEatSound();
        }

        /*  Sprawdzenie wystapienia kolizji z wlasnym cialem   */
        /*  Wywolanie funkcji do dzwieku zderzenia i przegranej gracza  */
        for(int i = 1; i < (int)wazCialo.size(); ++i){
            if(wazCialo[i] == head){
                kolizja = true;
                przegranaGracza(wynik, dlugosc, lvl);
                return;
            }
        }
    }

    void SnakeDetails::draw(tgui::CanvasSFML& planszaGryCanvas){
        /*
        *   Czyszczenie planszy - tla.
        *   Kolejno ustawienie rozmiaru jednego kafelka
        *   skaladajacego sie na plansze.
        *   Deklaracja zmiennej do kazdego z fragmentow
        *   ciala weza, a nastepnie rysowanie ciala
        *   w petli, gdzie glowa jest ciemniejsza
        */
        planszaGryCanvas.clear(sf::Color(25, 153, 39)); 
        const float tileSize = 20.f;
        sf::RectangleShape segmentShape(sf::Vector2f(tileSize, tileSize));

        // 1. Rysowanie głowy (Indeks 0)
        if(!wazCialo.empty()){
            segmentShape.setFillColor(sf::Color::Black);
            sf::Vector2f glowaWezaVect(wazCialo[0].x * tileSize, wazCialo[0].y * tileSize);
            segmentShape.setPosition(glowaWezaVect);
            planszaGryCanvas.draw(segmentShape);
        }

        segmentShape.setFillColor(sf::Color(56, 56, 56));
        for(std::size_t i = 1; i < wazCialo.size(); ++i){
            sf::Vector2f segmentShapePosVar((wazCialo[i].x) * tileSize, (wazCialo[i].y) * tileSize);
            segmentShape.setPosition(segmentShapePosVar);
            planszaGryCanvas.draw(segmentShape);
        }

        /*
        *   Rysowanie przedmiotu - jedzenia, dla weza ktore
        *   bedzie zwiekszac wynik o 10 oraz rozmiar weza
        *   o jeden kafelek.
        *   Na koncu aktualizacja canvasu - planszy
        */
        sf::RectangleShape foodShape(sf::Vector2f(tileSize, tileSize));
        foodShape.setFillColor(sf::Color::Red);
        sf::Vector2f foodPosVar((pozycjaJedzenia.x) * tileSize, (pozycjaJedzenia.y) * tileSize);
        foodShape.setPosition(foodPosVar);
        planszaGryCanvas.draw(foodShape);

        /*   */
        sf::RectangleShape gateShape(sf::Vector2f(tileSize, tileSize));
        gateShape.setFillColor(sf::Color::Yellow); // Kolor bramy
        sf::Vector2f pozycjaBramyHelper(pozycjaBramy.x * tileSize, pozycjaBramy.y * tileSize);
        gateShape.setPosition(pozycjaBramyHelper);
        planszaGryCanvas.draw(gateShape);

        planszaGryCanvas.display();
    }

    
    void SnakeDetails::aktualizujWynik(int wynik){
        this->wynik += wynik;
    }

    void SnakeDetails::aktualizujDlugosc(int dlugosc){
        this->dlugosc += dlugosc;
    }

    void SnakeDetails::kolejnyEtap(int lvl){
      this->lvl = lvl;
        //Przyspieszenie
        if(predkoscRuchu > 0.05f)
        predkoscRuchu *= 0.9f;
    
        playNextLevelSound();
        // Reset licznika przedmiotów na nowym poziomie
        zjedzonePrzedmioty = 0;

        // Reset pozycji węża na startową
        wazCialo.clear();
        wazCialo.push_back(sf::Vector2i(10, 10)); 
        wazCialo.push_back(sf::Vector2i(9, 10)); 
        wazCialo.push_back(sf::Vector2i(8, 10));
        dlugosc = (int)wazCialo.size();
        kierunekRuchu = sf::Vector2i(1, 0); // Reset kierunku

        // Zmiana pozycji bramy na nowym poziomie
        // Np. parzyste poziomy: lewy dół, nieparzyste: prawy góra
        if (lvl % 2 == 0)
        pozycjaBramy = sf::Vector2i(0, wysokoscPlanszy - 1);
        else
        pozycjaBramy = sf::Vector2i(szerokoscPlanszy - 1, 0);

        // Wygenerowanie jedzenia w nowym, bezpiecznym miejscu
        pozycjaJedzenia = generujNowaPozycjeJedzenia(szerokoscPlanszy, wysokoscPlanszy);
    }

    //void SnakeDetails::przejscieDoNastepnegoPoziomu(float predkoscRuchu){}

    void SnakeDetails::przegranaGracza(int wynik, int dlugosc, int lvl){
        /*
            !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
                                                                        */
        this->kolizja = true;
        playHitSound();


         // Reset wyniku i poziomu
    this->wynik = 0;
    this->lvl = 1;
    this->zjedzonePrzedmioty = 0;
    this->powerUp = "";
    
    // Reset prędkości do domyślnej
    this->predkoscRuchu = 0.2f;
    this->timerRuchu = 0.f;

    // Reset ciała węża do pozycji startowej (np. 10,10)
    wazCialo.clear();
    wazCialo.push_back(sf::Vector2i(10, 10)); 
    wazCialo.push_back(sf::Vector2i(9, 10)); 
    wazCialo.push_back(sf::Vector2i(8, 10));
    
    // Reset długości zmiennej pomocniczej
    this->dlugosc = (int)wazCialo.size();

    // Reset kierunku
    this->kierunekRuchu = sf::Vector2i(1, 0);

    // Reset pozycji bramy i jedzenia na startowe
    pozycjaBramy = sf::Vector2i(szerokoscPlanszy - 1, 0);
    pozycjaJedzenia = generujNowaPozycjeJedzenia(szerokoscPlanszy, wysokoscPlanszy);
        // /*
        //     Potrzeba ustawic ze przy kazdym z przypadkow gra jest zatrzymywana
        //     prz ykazdym rodzaju kolizji dzwiek wywolywany tylko w metodzie przegrana
        //     ustawic/zainicjalizowac od razu rozmiar planszy zeby miala wartosc 
        //     wieksza od zera bo wywali od razu. Najlepiej bedzie jeszcze wywolac
        //     konstruktor weza przed wyswietleniem np jeszcze podczas  odliczania
        //                 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //                                                                             */
                                                    
    /*
	- Do zrobienia warunek sprawdzajacy zmiane wyniku jakos ze zmienna pomocnicza czy cos
	- Zderzenia z samym soba
	- Mozna zmienic ilosc serduszek na aktywny powerup
	-Po przegranej reset planszy usuniecie labellu przegrana i weza, reset wszystkiego
	
	*/
    }

    tgui::Panel::Ptr SnakeDetails::wyswietlStatystyki(tgui::Panel::Ptr resultPanel, int wynik, int dlugosc, int lvl){
        std::cout << "===STATYSTYKI GRY===" << std::endl;
        std::cout << "Wynik: " << wynik << std::endl;
        std::cout << "Dlugosc: " << dlugosc << std::endl;
        std::cout << "Poziom: " << lvl << std::endl;
        std::cout << "PowerUp: " << powerUp << std::endl;
        //wyswietlanie statystyk
        //przekazanie gdzies tych przypisanie, zeby wykorzystac
        //do dodania do sceny
        //bedzie wywolywana i po przegranej i koncu gry

        resultPanel->removeAllWidgets();
        resultCanvas = tgui::CanvasSFML::create();
            resultCanvas->setSize(400, 550);
            resultCanvas->setPosition(75, 50);
            resultCanvas->moveToBack();
            resultPanel->add(resultCanvas);
            
        resultPanelTitle = tgui::Label::create("===STATYSTYKI GRY===");
            resultPanelTitle->setTextSize(20);
            resultPanelTitle->setPosition(125, 75);
            resultPanel->add(resultPanelTitle);
        resultPanelScore = tgui::Label::create("Wynik:      " + std::to_string(wynik));
            resultPanelScore->setTextSize(25);
            resultPanelScore->setPosition(100, 130);
            resultPanel->add(resultPanelScore);
        resultPanelLvl = tgui::Label::create("Poziom:   " + std::to_string(lvl));
            resultPanelLvl->setTextSize(25);
            resultPanelLvl->setPosition(100, 180);
            resultPanel->add(resultPanelLvl);
        resultPanelLength = tgui::Label::create("Dlugosc:   " + std::to_string(dlugosc));
            resultPanelLength->setTextSize(25);
            resultPanelLength->setPosition(100, 230);
            resultPanel->add(resultPanelLength);
        resultPanel->getRenderer()->setBackgroundColor(sf::Color::Green);
        return resultPanel;
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

