#include "ship.h"

class Invader : public Ship {
public:
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void Update(const float& dt) override;
};