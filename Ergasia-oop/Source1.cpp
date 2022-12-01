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
		All.push_back(new Entity("tree", sizeX, sizeY));
		All.push_back(new Entity("limnh", sizeX, sizeY));
	}
	int num_of_npc_per_team = lround(sizeX * sizeY / 15);
	for (int i = 0; i < num_of_npc_per_team; i++) {
		Warewolf.push_back(new npc("ww", sizeX, sizeY));
		Vampire.push_back(new npc("vamp", sizeX, sizeY));
		All.push_back(new npc("ww", sizeX, sizeY));
		All.push_back(new npc("vamp", sizeX, sizeY));
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
	if (it != vec.end()) {
		vec.erase(it);
		std::cout << "erased an enemy";
	}
	std::vector<Entity*>::iterator it2;
	it2 = std::find(vec2.begin(), vec2.end(), obj);
	if (it2 != vec2.end()) {
		vec2.erase(it2);
		std::cout << "erased an enemy 2";
	}

};

bool npc::hit(npc& enemy, Game &game) {
	if (attack < enemy.attack)
		return false;
	if (enemy.def <= attack) {
		std::cout << "HIT A " << enemy.name;
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

void Game::update() {
	for (auto i = Warewolf.begin(); i != Warewolf.end(); ++i) {
		(*i)->move(*this);
	}
	for (auto i = Vampire.begin(); i != Vampire.end(); ++i) {
		(*i)->move(*this);
	}
}