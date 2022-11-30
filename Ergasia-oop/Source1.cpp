#include <iostream>
#include <vector>
#include <stdlib.h>
#include "header1.h"

Game::Game(int x, int y) {
	sizeX = x;
	sizeY = y;
	sunny = true; //ksekiname mera
}

Entity::Entity() {
	name = "";
	x = 0;
	y = 0;
};
Entity::Entity(const char* str, int x_size, int y_size) {
	name = str;
	x = rand() % x_size;
	y = rand() % y_size;
}

int Entity::get_x() {
	return x;
};

int Entity::get_y() {
	return y;
};

const char* Entity::get_name() {
	return name;
}

void Game::CreateObjects() {
	int num_of_trees_and_lakes = lround(sizeX * sizeY / 20);
	for (int i = 0; i < num_of_trees_and_lakes; i++) {
		Terrarain.push_back(new Entity("tree", sizeX, sizeY));
		Terrarain.push_back(new Entity("limnh", sizeX, sizeY));
	}
	int num_of_npc_per_team = lround(sizeX * sizeY / 15);
	for (int i = 0; i < num_of_npc_per_team; i++) {
		Warewolf.push_back(new npc("ww", sizeX, sizeY));
		Vampire.push_back(new npc("vamp", sizeX, sizeY));
	}

}

void Game::drawMap() {
	for (auto i = Terrarain.begin(); i != Terrarain.end(); ++i) {
		std::cout << (**i).get_name() << " x = " << (**i).get_x() << " y = " << (**i).get_y() << std::endl;
	}
	for (auto i = Vampire.begin(); i != Vampire.end(); ++i) {
		std::cout << (**i).get_name() << " x = " << (**i).get_x() << " y = " << (**i).get_y() << std::endl;
	}
	for (auto i = Warewolf.begin(); i != Warewolf.end(); ++i) {
		std::cout << (**i).get_name() << " x = " << (**i).get_x() << " y = " << (**i).get_y() << std::endl;
	}
}

npc::npc(const char* str, int x_size, int y_size) {
	name = str;
	x = rand() % x_size;
	y = rand() % y_size;
	attack = rand() % 4; // 0 1 2 3
	if (attack == 0) ++attack;
	def = rand() % 3; // 0 1 2 
	if (def == 0) ++def;
	potions = rand() % 3; // 0 1 2
	hp = 3; // paradoxh so it withstands at least 1 attack.
};
