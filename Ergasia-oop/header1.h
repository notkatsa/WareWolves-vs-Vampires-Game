#pragma once
#include <vector>

class Entity;

class Game {
protected:
	int sizeX;
	int sizeY;
	std::vector<Entity> Entities;
public:
	Game(int sizex, int sizey);
	~Game();
	void CreateObjects();
	void drawMap();
};