#include <iostream>
#include <chrono>
#include <thread>
#include "header1.h"
int main() {
	srand(time(0));
	Game game(10,10);
	game.CreateObjects();
	for (int i = 0; i < 20; i++) {
		game.drawMap();
		game.update();
		std::cout << "/////////////////" << std::endl;
	}
	return 0;
}