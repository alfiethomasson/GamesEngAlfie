#pragma once
#include <SFML/Graphics.hpp>
//#include "Entity.h"
#include "Player.h"

using namespace sf;
using namespace std;

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;

extern vector<Entity*> players;

const Keyboard::Key controls[4] = {

	Keyboard::Up,
	Keyboard::Down,
	Keyboard::Left,
	Keyboard::Right

};