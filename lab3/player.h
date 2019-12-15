#pragma once
#include <cstring>
#include <string>
#include "time.h"
#include <iostream>
//#include "strategy.h"
using namespace std;

//class strategy {
//public:
//	virtual void place_ships() = 0;
//	virtual void attack(player&, int, int) = 0;
//};

class player {
protected:
	char* ship_deck;
	char* battle_deck;
	int status; //1 for wineer, 2 for loser, 0 for not stated

public:
	//friend class strategy;
	player();
	~player() {
		delete[] ship_deck;
		delete[] battle_deck;
	}
	virtual void place_ships() = 0;
	virtual void attack(player&) = 0;
	bool finish();
	int getstatus();
	char hit(int); //answer is the place empty
};


class manual : public player {
public:
	virtual void place_ships();
	virtual void attack(player&);
};

class clever : public player {
public:
	virtual void place_ships();
	virtual void attack(player&);
};
 
class random : public player {
public:
	virtual void place_ships();
	virtual void attack(player&); //coordinates + plyer_id
};