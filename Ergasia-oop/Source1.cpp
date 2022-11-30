#include <iostream>
#include <vector>
#include <stdlib.h>
#include "header1.h"

Game::Game(int x, int y) {
	sizeX = x;
	sizeY = y;
	sunny = true; //ksekiname mera
}

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
}

void Game::drawMap() {
	for (auto i = Terrarain.begin(); i != Terrarain.end(); ++i) {
		std::cout << (**i).get_name() << " x = " << (**i).get_x() << " y = " << (**i).get_y() << std::endl;
	}
}