#include <gameObjectContainer.hpp>
#include <gameObject.hpp>

GameObjectContainer::GameObjectContainer() {}

void GameObjectContainer::update(float deltaTime) {
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update(deltaTime);
	}
}

void GameObjectContainer::processAttacks() {
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = 0; j < objects.size(); j++)
		{
			objects[i]->attack(objects[j]);
		}
	}
}

void GameObjectContainer::add(GameObject* obj) {
	objects.push_back(std::move(obj));
}

void GameObjectContainer::remove(int index) {
	if (index < objects.size())
		objects.erase(objects.begin() + index);
	else
		std::cout << "Could not remove object, index is out of bounds\n"; //TODO: Cambiar
}

/*void GameObjectContainer::removeDead() {
	for (int i = 0; i < objects.size(); i++)
	{
		if(!objects[i]->isAlive())
		{
			objects[i]->onDeath();
			remove(i);
		}
	}
}*/

/*void GameObjectContainer::spriteRemoved(int index) {
	for (auto& obj : objects)
	{
		obj->spriteRemoved(index);
	}
}*/

void GameObjectContainer::free(){
	for (auto& obj : objects)
	{
		delete obj;
		obj = nullptr;
	}
}