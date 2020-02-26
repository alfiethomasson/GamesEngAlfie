#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "Ghost.h"
#include "Player.h"

using namespace sf;
using namespace std;

Color black(0, 0, 0);

vector<Entity*> entities;

Player p1;

float ghostNumber = 4;

void Load()
{
	auto p1 = new Player();
	p1->setPosition(Vector2f(400.0f, 400.0f));
	entities.push_back(p1);
	for (int i = 1; i < ghostNumber + 1; i++)
	{
		auto ghost = new Ghost();
		ghost->setPosition(Vector2f(150.0f * i, 300.0f));
		entities.push_back(ghost);
	}

}

void Update(RenderWindow& window)
{

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

	for (const auto e : entities)
	{
		e->Update(dt);
	}

}

void Render(RenderWindow& window)
{ 
	for(const auto e : entities)
	{
		e->Render(window);
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
