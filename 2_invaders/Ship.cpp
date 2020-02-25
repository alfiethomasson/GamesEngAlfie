#include "Ship.h"
#include "Game.h"
#include "bullet.h"
#include <iostream>

using namespace sf;
using namespace std;

float Player::pdirection;
float Player::playerSpeed = 100.0f;
bool Invader::direction;
float Invader::speed = 10.0f;
//vector<Bullet*> bullets;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	is_exploded = false;
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

//ship.cpp
Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
//	setTexture(spritesheet);
	//setTextureRect(ir);
	setOrigin(16, 16);
	setPosition(pos);
}

	void Invader::Update(const float& dt) {
		if (!is_exploded)
		{
			Ship::Update(dt);

			move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

			if ((direction && getPosition().x > gameWidth - 16) ||
				(!direction && getPosition().x < 16)) {
				direction = !direction;
				for (int i = 0; i < ships.size() - 1; ++i) {
					ships[i]->move(0, 24);
				}
			}

			static float firetime = 0.0f;
			firetime -= dt;
			if (firetime <= 0 && rand() % 100 == 0) {
				Bullet::Fire(getPosition(), true);
				firetime = 4.0f + (rand() % 60);
			}
		}
		else
		{
			float newalpha = explodetime -= dt;
			if (getColor().a > 0)
			{
				setColor(Color(255, 255, 255, 255.0f * newalpha));
			}
		}
	}

//ship.cpp
Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
    setPosition({gameHeight * .5f, gameHeight - 32.f});
}

void Player::Update(const float &dt) {
	if (!is_exploded)
	{
		Ship::Update(dt);

		//std::cout << "Player position currently: " << getPosition().x << " + " << getPosition().y << "  ";

		//Bullet::Update(dt);
		pdirection = 0.0;

		if (Keyboard::isKeyPressed(controls[0])) {
			pdirection--;
		}
		if (Keyboard::isKeyPressed(controls[1])) {
			pdirection++;
		}
		static float firetime = 0.0f;
		firetime -= dt;
		if (firetime <= 0 && Keyboard::isKeyPressed(controls[2])) {
			Bullet::Fire(getPosition(), false);
			firetime = 0.7f;
		}

		move(pdirection * playerSpeed * dt, 0);

	}
	else
	{
		float newalpha = explodetime -= dt;
		if (getColor().a > 0)
		{
			setColor(Color(255, 255, 255, 255.0f * newalpha));
		}
	}

    //Move left

    //Move Right
}

void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	explodetime = 2.0f;
	_exploded = true;
	is_exploded = true;
}	