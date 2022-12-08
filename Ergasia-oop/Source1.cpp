#include <iostream>
#include <vector>
#include <stdlib.h>
#include "header1.h"

Game::Game(int x, int y) {
	sizeX = x;
	sizeY = y;
	sunny = true; //ksekiname mera
	p = NULL;
	Potion = NULL;
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

void Entity::set_x_y_name(const char* str, int a, int b) {
	name = str;
	x = a;
	y = b;
}

void Game::GeneratePotion() {
	while (1) {
		int x = rand() % sizeX;
		int y = rand() % sizeY;
		bool occupied = false;
		for (auto i = All.begin(); i != All.end(); i++) {
			if ((*i)->get_x() == x || (*i)->get_y() == y) {
				occupied = true;
				break;
			}
		}
		if (!occupied) {
			Potion = new Entity();
			Potion->set_x_y_name("pot", x, y);
			return;
		}
	}
}
void Game::CreateObjects(const char* playerteam) {
	p = new Player(playerteam);
	this->All.push_back(p);
	int num_of_trees_and_lakes = lround(sizeX * sizeY / 20);
	for (int i = 0; i < num_of_trees_and_lakes; i++) {
		Entity* tree = new Entity("T", sizeX, sizeY);
		Entity* limnh = new Entity("O", sizeX, sizeY);
		Terrarain.push_back(tree);
		Terrarain.push_back(limnh);
		All.push_back(tree);
		All.push_back(limnh);
	}
	int num_of_npc_per_team = lround(sizeX * sizeY / 15);
	for (int i = 0; i < num_of_npc_per_team; i++) {
		npc* ww = new npc("ww", sizeX, sizeY);
		Warewolf.push_back(ww);
		npc* vamp = new npc("vamp", sizeX, sizeY);
		Vampire.push_back(vamp);
		All.push_back(ww);
		All.push_back(vamp);
	}
	GeneratePotion();

}

void Game::drawMap() {
	for (auto i = 0; i <= 2 * sizeX; i++) { //position x is 2*x
		for (auto j = 0; j < sizeY; j++) {//position y is y
			if (i % 2 == 0) {
				std::cout << "+---";

			}
			else {
				std::cout << "|";
				bool full = false;//empty cell
				if (p->get_x() == i / 2 && p->get_y() == j) {
					std::cout << " P ";
					full = true;

				}
				if (Potion->get_x() == i / 2 && Potion->get_y() == j) {
					std::cout << "POT";
					full = true;

				}
				if (full == false) {
					for (auto k = Terrarain.begin(); k != Terrarain.end(); ++k) {
						if ((**k).get_x() == i / 2 && (**k).get_y() == j) {
							std::cout << " " << (**k).get_name() << " ";
							full = true;//filled
							break;
						}
					}
				}
				if (full == false) {//if still empty check for vamp
					for (auto k = Vampire.begin(); k != Vampire.end(); ++k) {
						if ((**k).get_x() == i / 2 && (**k).get_y() == j) {
							std::cout << " " << "V" << " ";
							full = true;//filled
							break;
						}
					}
				}
				if (full == false) {//if still empty check for ww
					for (auto z = Warewolf.begin(); z != Warewolf.end(); ++z) {
						if ((**z).get_x() == i / 2 && (**z).get_y() == j) {
							std::cout << " " << "W" << " ";
							full = true;//filled
							break;
						}
					}
				}
				if (full == false)
					std::cout << "   ";
			}
		}
		if (i % 2 == 0) {
			std::cout << "+";//end of +--- row
		}
		else {
			std::cout << "|";//end of info row
		}
		std::cout << "\n";
	}
};


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

void npc::move(Game &game) {
	if (this->name == "ww") {
		// check for attacks
		for (auto i = game.Vampire.begin(); i != game.Vampire.end(); ++i) {
			if (this->get_x() != (**i).get_x()) {
				if (this->get_y() != (**i).get_y()) //diff row and col
					continue;
				else if (abs(this->get_x() - (**i).get_x()) == 1) { //same row - neighboring col
					if (this->hit(**i, game)) return; //in 1 tick it only does 1 action
				}
			}
			else if (abs(this->get_y() - (**i).get_y()) == 1) { //same col - neighboring row 
				if (this->hit(**i, game)) return;
			}
		}
		// copy paste ^ same logic only for friendlys so it heals
		// check for heals
		for (auto i = game.Warewolf.begin(); i != game.Warewolf.end(); ++i) {
			if (this->get_x() != (**i).get_x()) {
				if (this->get_y() != (**i).get_y()) //diff row and col
					continue;
				else if (abs(this->get_x() - (**i).get_x()) == 1) { //same row - neighboring col
					if (this->heal(**i)) return; //in 1 tick it only does 1 action
				}
			}
			else if (abs(this->get_y() - (**i).get_y()) == 1) { //same col - neighboring row 
				if (this->heal(**i)) return;
			}
		}
		// move
		do {
			int position = rand() % 5; // 0-still 1-top 2-right 3-bottom 4-left
			bool occupied = false;
			if (position == 0)
				return;
			else if (position == 1) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if ((this->get_x() == (**i).get_x() && this->get_y() - (**i).get_y() == 1) || this->get_y() == 0) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->y)--;
					return;
				}
				continue;
			}
			else if (position == 2) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if ((this->get_y() == (**i).get_y() && (**i).get_x() - this->get_x() == 1) || this->get_x() == game.sizeX -1) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->x)++;
					return;
				}
				continue;
			}
			else if (position == 3) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if ((this->get_x() == (**i).get_x() && (**i).get_y() - this->get_y() == 1) || this->get_y() == game.sizeY -1) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->y)++;
					return;
				}
				continue;
			}
			else if (position == 4) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if ((this->get_y() == (**i).get_y() && this->get_x() - (**i).get_x() == 1) || this->get_x() == 0) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->x)--;
					return;
				}
				continue;
			}

		} while (true);
	}
	if (this->name == "vamp") {
		// check for attacks
		for (auto i = game.Warewolf.begin(); i != game.Warewolf.end(); ++i) {
			if (this->get_x() != (**i).get_x()) {
				if (this->get_y() != (**i).get_y()) //diff row and col
					continue;
				else if (abs(this->get_x() - (**i).get_x()) == 1) { //same row - neighboring col
					if (this->hit(**i, game)) return; //in 1 tick it only does 1 action
				}
			}
			else if (abs(this->get_y() - (**i).get_y()) == 1) { //same col - neighboring row 
				if (this->hit(**i, game)) return;
			}
		}
		// copy paste ^ same logic only for friendlys so it heals
		// check for heals
		for (auto i = game.Vampire.begin(); i != game.Vampire.end(); ++i) {
			if (this->get_x() != (**i).get_x()) {
				if (this->get_y() != (**i).get_y()) //diff row and col
					continue;
				else if (abs(this->get_x() - (**i).get_x()) == 1) { //same row - neighboring col
					if (this->heal(**i)) return; //in 1 tick it only does 1 action
				}
			}
			else if (abs(this->get_y() - (**i).get_y()) == 1) { //same col - neighboring row 
				if (this->heal(**i)) return;
			}
		}
		// move
		do {
			int position = rand() % 9; // 0-still 1-top 2-right 3-bottom 4-left
									   // TODO 5-1:30 6-4:30 7-7:30 8-10:30
			bool occupied = false;
			if (position == 0)
				return;
			else if (position == 1) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if ((this->get_x() == (**i).get_x() && this->get_y() - (**i).get_y() == 1) || this->get_y() == 0) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->y)--;
					return;
				}
				continue;
			}
			else if (position == 2) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if ((this->get_y() == (**i).get_y() && (**i).get_x() - this->get_x() == 1) || this->get_x() == game.sizeX-1) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->x)++;
					return;
				}
				continue;
			}
			else if (position == 3) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if ((this->get_x() == (**i).get_x() && (**i).get_y() - this->get_y() == 1) || this->get_y() == game.sizeY -1) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->y)++;
					return;
				}
				continue;
			}
			else if (position == 4) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if ((this->get_y() == (**i).get_y() && this->get_x() - (**i).get_x() == 1) || this->get_x() == 0) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->x)--;
					return;
				}
				continue;
			}
			else if (position == 5) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if ((this->get_y() - (**i).get_y() == 1 && (**i).get_x() - this->get_x() == 1) || this->get_x() == game.sizeX -1 || this->get_y() == 0) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->x)++;
					(this->y)--;
					return;
				}
				continue;
			}
			else if (position == 6) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if (((**i).get_y() - this->get_y() == 1 && (**i).get_x() - this->get_x() == 1) || this->get_x() == game.sizeX -1 || this->get_y() == game.sizeY - 1) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->x)++;
					(this->y)++;
					return;
				}
				continue;
			}
			else if (position == 7) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if (((**i).get_y() - this->get_y() == 1 && this->get_x() - (**i).get_x() == 1) || this->get_x() == 0 || this->get_y() == game.sizeY - 1) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->x)--;
					(this->y)++;
					return;
				}
				continue;
			}
			else if (position == 8) {
				for (auto i = game.All.begin(); i != game.All.end(); ++i) {
					if ((this->get_y() - (**i).get_y() == 1 && this->get_x() - (**i).get_x() == 1) || this->get_x() == 0 || this->get_y() == 0) {
						occupied = true;
						break;
					}
				}
				if (!occupied) {
					(this->x)--;
					(this->y)--;
					return;
				}
				continue;
			}
		} while (true);
	}
}

void deleteObj(std::vector<npc*> &vec, std::vector<Entity*> &vec2, npc* obj) {
	std::vector<npc*>::iterator it;
	it = std::find(vec.begin(), vec.end(), obj);
	std::vector<Entity*>::iterator it2;
	it2 = std::find(vec2.begin(), vec2.end(), obj);
	if (it != vec.end()) 
		vec.erase(it);

	if (it2 != vec2.end()) 
		vec2.erase(it2);

};

bool npc::hit(npc& enemy, Game &game) {
	if (attack < enemy.attack)
		return false;
	if (enemy.def <= attack) {
		enemy.hp -= attack - enemy.def;
		if (enemy.hp <= 0) {
			if (enemy.name == "vamp")
				deleteObj(game.Vampire, game.All, &enemy);
			else deleteObj(game.Warewolf, game.All, &enemy);
		}
	}
	return true;
	
}

bool npc::heal(npc& teammate) {
	int willheal = rand() % 2;
	if (willheal && potions > 0) {
		teammate.hp++;
		potions--;
		return true;
	}
	return false;
}

void npc::increaseHp() {
	this->hp++;
}

void Game::update() {
	for (auto i = Warewolf.begin(); i != Warewolf.end(); ++i) {
		(*i)->move(*this);
	}
	for (auto i = Vampire.begin(); i != Vampire.end(); ++i) {
		(*i)->move(*this);
	}
}

void Player::healTeam(Game& game) {
	if (strcmp(this->team, "ww") == 0) {
		for (auto i = game.Warewolf.begin(); i != game.Warewolf.end(); ++i) {
			(*i)->increaseHp();
		}
		this->potions--;
	}
	else if (strcmp(this->team, "vamp") == 0) {
		for (auto i = game.Vampire.begin(); i != game.Vampire.end(); ++i) {
			(*i)->increaseHp();
		}
		this->potions--;
	}
}

Player::Player(const char* team) {
	x = 0;
	y = 0;
	name = "player";
	this->team = team;
	potions = 1;
};

void Player::move(const char c, Game &game) {
	// h draw zwgrafizei me x pros ta katw enw 
	// to logic theorei to x pros ta deksia
	// gia afto 
	if (c == 'w' || c == 'W') {

		if (x == 0) return;
		for (auto i = game.All.begin(); i != game.All.end(); ++i) {
			if ((this->get_y() == (**i).get_y() && this->get_x() - (**i).get_x() == 1) || this->get_x() == 0) {
				return;
			}
		}
		x--;
	}
	else if (c == 'a' || c == 'A') {
		if (y== 0) return;
		for (auto i = game.All.begin(); i != game.All.end(); ++i) {
			if ((this->get_x() == (**i).get_x() && this->get_y() - (**i).get_y() == 1) || this->get_y() == 0) {
				return;
			}
		}
		y--;
	}
	else if (c == 'd' || c == 'D') {
		if (y == game.sizeX - 1) return;
		for (auto i = game.All.begin(); i != game.All.end(); ++i) {
			if ((this->get_x() == (**i).get_x() && (**i).get_y() - this->get_y() == 1) || this->get_y() == game.sizeY - 1) {
				return;
			}
		}
		y++;
	}
	else if (c == 's' || c == 'S') {
		if (x == game.sizeY - 1) return;
		for (auto i = game.All.begin(); i != game.All.end(); ++i) {
			if ((this->get_y() == (**i).get_y() && (**i).get_x() - this->get_x() == 1) || this->get_x() == game.sizeX - 1) {
				return;
			}
		}
		x++;
	}
	else if (c == 'q' || c == 'Q') {
		if (potions <= 0) return;
		this->healTeam(game);
		std::cout << "HEALED " << this->team;
	}
	else if (c == 'P' || c == 'p') system("pause");

	if (this->x == game.Potion->get_x() && this->y == game.Potion->get_y()) {
		this->potions++;
		game.Potion->set_x_y_name("panatha", '13', '1908'); // lazy 
	}
};