#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Game.h"
#include "Ghost.h"
#include "Player.h"
#include "System_Renderer.h"
#include "Scene.h"
#include "Pacman.h"
//#include "Scene.h"


using namespace sf;
using namespace std;

Color black(0, 0, 0);

float ghostNumber = 4;

EntityManager em;

void Load()
{

	auto p1 = make_shared<Player>();
	
//	Player p = shared_ptr<p1>;
	//p1->setPosition(Vector2f(400.0f, 400.0f));
	//entities.push_back(p1);
	em.list.push_back(p1);
	for (int i = 1; i < ghostNumber + 1; i++)
	{
		auto ghost = make_shared<Ghost>();
		ghost->setPosition(Vector2f(150.0f * i, 300.0f));
		em.list.push_back(ghost);
	}

	// Load Scene-Local Assets
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();
	// Start at main menu
	activeScene = menuScene;

}

void Update(RenderWindow& window)
{

	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->update(dt);

	/*static Clock clock;
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

	for (auto e : em.list)
	{
		e->Update(dt);
	}*/

}

void Render(RenderWindow& window)
{ 
/*	for(const auto e : em.list)
	{
		e->Render(window);
	}*/

//	Renderer::queue(&em.list.get_allocator());

	activeScene->render(window);
	// flush to screen
	Renderer::render();
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
