#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"
//#include "Player.h"
#include "Game.h"

using namespace sf;
using namespace std;

Color black(0, 0, 0);

Player p1;

void Load()
{
	auto p1 = new Player();
	//players.push_back(p1);
}

void Update(RenderWindow& window)
{
	/*for (const auto t : things)
	{
		t->Render(window);
	}*/

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

	p1.Update(dt);

}

void Render(RenderWindow& window)
{
	p1.Render(window);
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
