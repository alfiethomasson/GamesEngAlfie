#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
	static void Start();
	static void Update(const float& dt);
	static void Render(sf::RenderWindow& window);
	static void Fire(const sf::Vector2f& pos, const bool mode);
	//Bullet(const sf::Vector2f& pos, const bool mode);
	~Bullet() = default;
	//Constructor that takes a sprite
	explicit Bullet(sf::IntRect ir);
protected:
	static unsigned char bulletPointer;
	static Bullet bullets[256];
	void _Update(const float& dt);
	Bullet();
	//false=player bullet, true=Enemy bullet
	bool _mode;
	sf::IntRect _sprite;
};