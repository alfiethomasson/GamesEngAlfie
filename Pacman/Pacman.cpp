#include <iostream>
#include "Pacman.h"
#include "Entity.h"
#include "Ghost.h"
#include "Player.h"	
#include "System_Renderer.h"

using namespace sf;
using namespace std;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

void MenuScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	//Set up the text element here!

	font.loadFromFile("C:/Users/alfie/OneDrive/Documents/GitHub/GamesEngAlfie/res/Fonts/mandalore.ttf");
	text.setFont(font);
}

void GameScene::load() {
	//...
		auto player = make_shared<Player>();
		_ents.list.push_back(player);
	for (int i = 0; i < 4; i++) {
		auto ghost = make_shared<Ghost>();
			_ents.list.push_back(ghost);
	}
	//...
}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
	//...
}

void GameScene::render() {
	Renderer::queue(&text);
	Scene::render();
}