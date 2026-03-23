#pragma once
#include <vector>
#include <memory>
#include <iostream>

class GameObject;

class GameObjectContainer {
public:
	GameObjectContainer();
	void add(GameObject* obj);
	void update(float deltaTime);
	void processAttacks();
	//void removeDead();
	//void spriteRemoved(int index);
	void free();
private:
	void remove(int index);
	std::vector<GameObject*> objects;
};