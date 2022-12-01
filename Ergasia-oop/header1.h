#pragma once
#include <vector>

class Entity;
class npc;

class Game {
protected:
	int sizeX;
	int sizeY;
	bool sunny;
	std::vector<Entity*> Terrarain;
	std::vector<npc*> Warewolf;
	std::vector<npc*> Vampire;
	std::vector<Entity*> All;
public:
	Game(int sizex, int sizey);
	void CreateObjects();
	void drawMap();
	void update();
	friend class Entity;
	friend class npc;
	friend class Player;
};

class Entity {
protected:
	int x;
	int y;
	const char* name; // limnh, dentro, ww, vmp
public:
	Entity();
	Entity(const char* str, int x_size, int y_size);
	int get_x();
	int get_y();
	const char* get_name();
};

class npc : public Entity { // ww - vmp
private:
	int attack;
	int def;
	int potions;
	int hp;
public:
	npc(const char* str, int x_size, int y_size); // constructor
	
	void move(Game &game); // nada, step, attack, heal
	bool hit(npc& enemy, Game &game);
	bool heal(npc& teammate);
};

class Player : public Entity {
	char* team;
	int potions;
public:
	void move(); // gets called 
	void heal();

};