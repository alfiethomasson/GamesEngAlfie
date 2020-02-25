#pragma once
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;
constexpr uint16_t invaders_rows = 5;
constexpr uint16_t invaders_columns = 12;

extern Texture spritesheet;
extern vector<Ship*> ships;
//extern Bullet bullets[256];

const Keyboard::Key controls[3] = {

	Keyboard::Left,
	Keyboard::Right,
	Keyboard::Space,

};