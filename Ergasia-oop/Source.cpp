#include <iostream>
#include <windows.h>
#include "header1.h"
#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
	srand(time(0));
	int x,y;
	char t[5];
	bool good;
	do {
		good = true;
		cout << "give me size x (5-64), size y(5-64), your team(ww for Warewolf-vamp for Vampire)\n";
		cin >> x;
		cin >> y;
		cin >> t;
		if (x>64 || y > 64 || (strcmp(t, "ww") != 0 && strcmp(t, "vamp") != 0)) {
			cin.clear();
			cin.ignore(100, '\n'); //100 --> asks cin to discard 100 characters from the input stream.
			good = false;
			cout << "Wrong input :( \n Try again!";
		}
	} while (good == false);
	Game game(x, y);
	game.CreateObjects(t);

	int frames = 0;
	bool exit = false;
	while (!exit && game.winner_team()=="No winner") {
		cout << "It is currently " << (game.is_day() ? "sunny" : "night"); 
		cout << endl;
		game.drawMap(); 
		game.update();
		Sleep(200);
		// player movement
		if (GetKeyState('W') & 8000) game.p->move('w', game);
		else if (GetKeyState('A') & 8000) game.p->move('a', game);
		else if (GetKeyState('S') & 8000) game.p->move('s', game);
		else if (GetKeyState('D') & 8000) game.p->move('d', game);
		else if (GetKeyState('Q') & 8000) game.p->move('q', game);
		else if (GetKeyState('P') & 8000) game.p->move('p', game);
		else if (GetKeyState('X') & 8000) return 1;
		system("cls");
		if (frames++ == 15) {//5frames=1sec -> we change stateofday every 3 seconds
			frames = 0;
			game.update_day();
		}
	}
	cout << "Winner is " + game.winner_team();
	return 0;
}