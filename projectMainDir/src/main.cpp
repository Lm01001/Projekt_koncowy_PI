#include <iostream>
#include <SFML/Graphics.hpp>
#include "SnakeDetails.h"

using namespace std;
//g++ ../../src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o run

int main() {
	sf::RenderWindow window(sf::VideoMode(800,600), "Test window");
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.display();
	}

	return 0;
}