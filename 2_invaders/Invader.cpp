/*#include "Invader.h"
#include "Game.h"

using namespace sf;
using namespace std;

Invader::Invader() : Ship() {};

bool direction;
bool speed = 1.0f;

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float& dt) {
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			ships[i]->move(0, 24);
		}
	}
}*/