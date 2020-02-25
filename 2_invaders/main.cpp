#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ship.h"
//#include "Invader.h"
#include "Game.h"
#include "Bullet.h"

using namespace sf;
using namespace std;

//const int gameWidth = 800;
//const int gameHeight = 600;
const int shipsInRow = 8;

Color black(0, 0, 0);

Texture spritesheet;
//Sprite invader;

//vector<Ship *> ships;	

void Load() {
	if (!spritesheet.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/GamesEngAlfie/res/Sprites/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	for (int r = 0; r < invaders_columns; r++) {
		for (int c = 0; c < invaders_rows; c++) {
			auto rect = IntRect(32 * c, 0, 32, 32);
			//float x = 100 * c;
		//	float y = 100 * r;
		Vector2f position =  Vector2f(100 + (50 * r), 100 + (50 * c));
		auto inv = new Invader(rect, position);
		ships.push_back(inv);
		}
	}
	auto rect = IntRect(5, 2, 32, 32);
	Vector2f pos = Vector2f(400, 700);
	auto player = new Player();
	ships.push_back(player);

	Bullet::Start();

}

void Update(RenderWindow& window) {

//	std::cout << "hello";

	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	//quit via esc
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}


	for (const auto s : ships)
	{
		//printf("Current Ship position: = " + s->getPosition());
		s->Update(dt);
	}
	
	Bullet::Update(dt);
	

}

void Render(RenderWindow& window) {
		for (const auto s : ships) 
		{
			window.draw(*s);
		}

		Bullet::Render(window);
	


}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	while (window.isOpen()) {
		window.clear(black);
		Update(window);
		Render(window);
		window.display();
	}

}
