#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Invader.h"

using namespace sf;
using namespace std;

const Keyboard::Key controls[3] = {

	Keyboard::Space,
	Keyboard::Left,
	Keyboard::Right
};

const int gameWidth = 800;
const int gameHeight = 600;
const int shipsInRow = 8;

Color black(0, 0, 0);

Texture spritesheet;
//Sprite invader;

vector<Ship *> ships;	

void Load() {
	if (!spritesheet.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/GamesEngAlfie/res/Sprites/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	for (float i = 1; i < shipsInRow; i++)
	{
			Invader* invader = new Invader(IntRect(0, 0, 32, 32), { 100 * i, 100 });
			ships.push_back(invader);
	}
	//invader.setTexture(spritesheet);
	//invader.setTextureRect(IntRect(0, 0, 32, 32));

}

void Update(RenderWindow& window) {


}

void Render(RenderWindow& window) {
		for (const auto s : ships) 
		{
			window.draw(*s);
		}
	
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
