#pragma once
#include <vector>

class Entity;
class npc;
class Player;

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
	Player* p;
	Game(int sizex, int sizey);
	void CreateObjects(const char* player_team);
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
	virtual void move() {
		std::cout << "helloooooo";
		// move wasnt needed to be virtual but for the spirit
		// of the excercise it had to be :D
	}
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
	void increaseHp();
};

class Player : public Entity {
	const char* team;
	int potions;
public:
	Player(const char*);
	void move(const char, Game &game); // gets called 
	void healTeam(Game& game);
};