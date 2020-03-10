#include "Scene.h"
#include "System_Renderer.h"

void Scene::render() { for( auto e : _ents.list)
						e->Render(); }
//void Scene::render() {  }
void Scene::update(double dt) {}
void Scene::load() {}
std::vector<std::shared_ptr<Entity>>& Scene::getEnts()
{
	return _ents.list;
}