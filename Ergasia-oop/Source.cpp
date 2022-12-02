#include <iostream>
#include <windows.h>
#include "header1.h"
#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
	srand(time(0));
	cout << "give me size x (8-64), size y(8-64), your team(ww-vamp)\n";
	int x,y;
	cin >> x;
	cin >> y;
	char t[4];
	cin >> t;
	Game game(x, y);
	game.CreateObjects(t);

	bool exit = false;
	while (!exit) {
		game.drawMap();
		Sleep(200);
		if (GetKeyState('W') & 8000) game.p->move('w', game);
		else if (GetKeyState('A') & 8000) game.p->move('a', game);
		else if (GetKeyState('S') & 8000) game.p->move('s', game);
		else if (GetKeyState('D') & 8000) game.p->move('d', game);
		else if (GetKeyState('q') & 8000) game.p->move('q', game);
		else if (GetKeyState('p') & 8000) game.p->move('p', game);
		else if (GetKeyState('x') & 8000) return 1;
		system("cls");
		game.update();
	}
	return 0;
}