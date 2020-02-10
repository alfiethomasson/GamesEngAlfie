#include "bullet.h"
#include "game.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

//Create definition for the constructor
//...

bool _mode;

unsigned char Bullet::bulletPointer = 0;
Bullet Bullet::bullets[256];

Bullet::Bullet() {};

void Bullet::Render(sf::RenderWindow& window) {
	for (const auto& bullet : bullets) {
		//std::cout << "rendering";
		window.draw(bullet);
	}
}

Bullet::Bullet(IntRect ir) : sf::Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};


 void Bullet::Start()
{
	for (auto& bullet : bullets)
	{
		bullet.setPosition(-9999.0f, -9999.0f);
	}
}

void Bullet::Update(const float& dt) {
	
	for(auto &b : bullets)
	{
		b._Update(dt);
	}

};

void Bullet::_Update(const float& dt) {
	//std::cout << getPosition().x << " + " << getPosition().y;
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		//off screen - do nothing
		return;
	}
	else {
		std::cout << "bullet at: " << getPosition().x << " " << getPosition().y << "  ";
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == ships[ships.size() -1]) {
				//player bulelts don't collide with player
				continue;
			}
			if (_mode && s != ships[ships.size() - 1]) {
				//invader bullets don't collide with other invaders
				continue;
			}
			if (!s->is_exploded &&
				s->getGlobalBounds().intersects(boundingBox)) {
				//Explode the ship
				s->Explode();
				//warp bullet off-screen
				setPosition(-100, -100);
				return;
			}
		}
	}
};

void Bullet::Fire(const sf::Vector2f& pos, const bool mode)
{
//	std::cout << "Bullet fired";
	//std::cout << " bullet pointer is currently  " << bulletPointer;
	bullets[bulletPointer].setPosition(pos);
	bullets[bulletPointer]._mode = mode;
//	std::cout << "bullet moved to: " << bullets[bulletPointer].getPosition().x << " , " << bullets[bulletPointer].getPosition().y << "  ";
	bulletPointer++;
}