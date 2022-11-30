#include <iostream>
#include "header1.h"
int main() {
	Game game(10,10);
	game.CreateObjects();
	game.drawMap();
	// create gameobjects
	// loop that calls
	//		move, listens to keypress, drawMap
	return 0;
}