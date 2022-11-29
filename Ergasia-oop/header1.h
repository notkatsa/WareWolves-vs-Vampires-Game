#pragma once
#include <vector>

class Entity;
class npc;

class Game {
protected:
	int sizeX;
	int sizeY;
	bool sunny;
	std::vector<Entity> Terrarain;
	std::vector<npc> Warewolf;
	std::vector<npc> Vampire;
public:
	Game(int sizex, int sizey);
	~Game();
	void CreateObjects();
	void drawMap();
	friend class npc;
	friend class Player;
};

class Entity {
private:
	int x;
	int y;
	char* name; // limnh, dentro, ww, vmp
};

class npc : public Entity { // ww - vmp
private:
	int attack;
	int def;
	int potions;
	int hp;
public:
	npc(); // constructor
	~npc();
	void move(); // nada, step, attack, heal
};

class Player : public Entity {
	char* team;
	int potions;
public:
	void move(); // gets called 
	void heal();

};