#pragma once
#include <SFML/Graphics.hpp>
//#include "Game.h"

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	//Default constructor is hidden
	Ship();
	bool _exploded;
public:
	bool is_exploded;
	float explodetime;
	virtual void Explode();
	//Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	//Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
	virtual ~Ship() = 0;
	//Update, virtual so can be overridden, but not pure virtual
	virtual void Update(const float& dt);
};

class Invader : public Ship {
public:
	static bool direction;
	static float speed;
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float& dt) override;
};

//ship.h
class Player : public Ship {
public:
	static float pdirection;
	static float playerSpeed;
	//static std::vector<Bullet*> bullets;
	Player();
	void Update(const float& dt) override;
};