#include "player.h"


void ship_delete(char battle_deck[], int coordinate) {
	if (((coordinate >= 10) && (battle_deck[coordinate - 10] == 2)) || ((coordinate <= 89) && (battle_deck[coordinate + 10] == 2))) { //vertical
		int start = coordinate, finish = coordinate;
		while ((start >= 10) && (battle_deck[start - 10] == 2)) {
			start = start - 10;
		}
		while ((finish <= 89) && (battle_deck[finish + 10] == 2)) {
			finish = finish + 10;
		}
		for (int i = start; i <= finish; i = i + 10) {
			battle_deck[i] = 3;
		}
	}

	if (((coordinate % 10 >= 1) && (battle_deck[coordinate - 1] == 2)) || ((coordinate % 10 <= 98) && (battle_deck[coordinate + 1] == 2))) { //horizontal
		int start = coordinate, finish = coordinate;
		while ((start % 10 >= 1) && (battle_deck[start - 1] == 2)) {
			start = start - 1;
		}
		while ((finish % 10 <= 98) && (battle_deck[finish + 1] == 2)) {
			finish = finish + 1;
		}
		for (int i = start; i <= finish; i = i + 1) {
			battle_deck[i] = 3;
		}
	}
	battle_deck[coordinate] = 3;
}

void place_ship(char ship_deck[], int coordinate, string orient, int towers) {
	if ((coordinate > 99) || (coordinate < 0)) throw exception("wrong coordinate value. expect from 0 to 99");
	if (orient == "vertical") {
		if (coordinate / 10 > 10 - towers) throw exception("not enough space for the ship");
		for (int i = 0; i < towers; i++) {
			if (ship_deck[coordinate + 10 * i] == 1) throw exception("this space is not free");
			if (((coordinate + 10 * i) % 10 <= 8) && (ship_deck[coordinate + i * 10 + 1] == 1)) throw exception("can not be placed near another ship");
			if (((coordinate + 10 * i) % 10 >= 1) && (ship_deck[coordinate + i * 10 - 1] == 1)) throw exception("can not be placed near another ship");
			if (((coordinate + 10 * i) / 10 <= 8) && (ship_deck[coordinate + i * 10 + 10] == 1)) throw exception("can not be placed near another ship");
			if (((coordinate + 10 * i) / 10 >= 1) && (ship_deck[coordinate + i * 10 - 10] == 1)) throw exception("can not be placed near another ship");

		}
		for (int i = 0; i < towers; i++) {
			ship_deck[coordinate + 10 * i] = 1;
		}
	}
	else {
		if (orient == "horizontal") {
			if (coordinate % 10 > 10 - towers) throw exception("not enough space for the ship");
			for (int i = 0; i < towers; i++) {
				if (ship_deck[coordinate + 10 * i] == 1) throw exception("this space is not free");
				if (((coordinate + i) % 10 <= 8) && (ship_deck[coordinate + i + 1] == 1)) throw exception("can not be placed near another ship");
				if (((coordinate + i) % 10 >= 1) && (ship_deck[coordinate + i - 1] == 1)) throw exception("can not be placed near another ship");
				if (((coordinate + i) / 10 <= 8) && (ship_deck[coordinate + i + 10] == 1)) throw exception("can not be placed near another ship");
				if (((coordinate + i) / 10 >= 1) && (ship_deck[coordinate + i - 10] == 1)) throw exception("can not be placed near another ship");

			}
			for (int i = 0; i < towers; i++) {
				ship_deck[coordinate + i] = 1;
			}
		}
		else throw exception("wrong orientation type");
	}
}

player::player() {
	ship_deck = new char[100];
	battle_deck = new char[100];
	for (int i = 0; i < 99; i++) {
		ship_deck[i] = 0;
		battle_deck[i] = 0;
	}
	status = 0;
}

bool player::finish() {
	if (status > 0) return 1;
	else return 0;
}

int player::getstatus() {
	return status;
}

char player::hit(int coordinate) {
	int orient = 0; //1 for vert, 2 for hor
	char result;
	char not_damaged = 0;
	if (ship_deck[coordinate] == 0) return 0;
	if (ship_deck[coordinate] == 1) {
		ship_deck[coordinate] = 2;
		
		//check for losing
		int exist = 0;
		for (int i = 0; i <= 99; i++) {
			if (ship_deck[i] == 1) exist++;
		}
		if (exist == 0) status = 2;

		if (((coordinate >= 10) && (ship_deck[coordinate - 10] != 0)) || ((coordinate <= 89) && (ship_deck[coordinate + 10] != 0))) {
			orient = 1;
			int start = coordinate, finish = coordinate;
			while ((start >= 10) && (ship_deck[start - 10] != 0)) {
				start = start - 10;
			}
			while ((finish <= 89) && (ship_deck[finish + 10] != 0)) {
				finish = finish + 10;
			}
			for (int i = start; i <= finish; i = i + 10) {
				if (ship_deck[i] != 2) not_damaged++;
			}
			cout << start << finish << endl;
			if (not_damaged == 0) return 2;
			else return 1;
		}

		if (((coordinate % 10 >= 1) && (ship_deck[coordinate - 1] != 0)) || ((coordinate % 10 <= 8) && (ship_deck[coordinate + 1] != 0))) {
			orient = 2;
			int start = coordinate, finish = coordinate;
			while ((start % 10 >= 1) && (ship_deck[start - 1] != 0)) {
				start = start - 1;
			}
			while ((finish % 10 <= 98) && (ship_deck[finish + 1] != 0)) {
				finish = finish + 1;
			}
			for (int i = start; i <= finish; i = i + 1) {
				if (ship_deck[i] != 2) not_damaged++;
			}
			if (not_damaged == 0) return 2;
			else return 1;
		}

		return 2; // no if was triggered  -  solo ship 
	}
}
void manual::attack(player& enemy) {
	int coordinate;
	cout << "enter coordinate to attack, f.e. 08" << endl;
	cin >> coordinate;
	if ((coordinate >= 100) || (coordinate < 0)) throw exception("wrong coordinate to attack");
	if (battle_deck[coordinate] == 0) battle_deck[coordinate] = 1;
	else {
		cout << "already attacked that check" << endl;
		return;
	}

	char res = enemy.hit(coordinate);
	
	if (res == 0) cout << "miss" << endl;
	if (res == 1) cout << "hit" << endl;
	if (res == 2) cout << "kill" << endl;

	if (res == 2) {
		ship_delete(battle_deck, coordinate);
	}

	if (res == 1) {
		battle_deck[coordinate] = 2;
	}
}

void clever::attack(player & enemy) {
	int coordinate = -1;
	int counter = 0;
	for (int i = 0; i < 100; i++) {
		if (battle_deck[i] == 2) break;
		counter++;
	}
	if (counter == 100) { //did not find damaged check
		for (int i = 0; i < 100; i++) {
			coordinate = i;
			if (battle_deck[i] == 0) break;
		}
	}
	else {
		coordinate = counter;
		int hor = coordinate;
		int vert = coordinate;
		while ((vert / 10 < 9) && (battle_deck[vert + 10] == 2)) vert = vert + 10;
		while ((hor % 10 < 9) && (battle_deck[hor + 1] == 2)) hor = hor + 1;
		if ((hor == coordinate) && (battle_deck[vert + 10] == 0)) coordinate = vert + 10;
		else coordinate = hor + 1;
	}

	char res = enemy.hit(coordinate);

	if (res == 2) {
		ship_delete(battle_deck, coordinate);
	}

	if (res == 1) {
		battle_deck[coordinate] = 2;
	}

	if (res == 0) {
		battle_deck[coordinate] = 1;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (battle_deck[j + 10 * i] == 1) cout << 1;
			if (battle_deck[j + 10 * i] == 0) cout << 0;
			if (battle_deck[j + 10 * i] == 2) cout << 2;
			if (battle_deck[j + 10 * i] == 3) cout << 3;
		}
		cout << endl;
	}
	cout << endl;
}

void random::attack(player& enemy) {

	int coordinate = rand() % 100;
	
	while (battle_deck[coordinate] != 0) {
		coordinate = rand() % 100;
	}
	
	char res = enemy.hit(coordinate);

	if (res == 2) {
		ship_delete(battle_deck, coordinate);
	}

	if (res == 1) {
		battle_deck[coordinate] = 2;
	}
	if (res == 0) {
		battle_deck[coordinate] = 1;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (battle_deck[j + 10 * i] == 1) cout << 1;
			if (battle_deck[j + 10 * i] == 0) cout << 0;
			if (battle_deck[j + 10 * i] == 2) cout << 2;
			if (battle_deck[j + 10 * i] == 3) cout << 3;
		}
		cout << endl;
	}
	cout << endl;

}


void manual::place_ships() {
	int coordinate;
	string orient;
	cout << "Format of sending coordinates : start position + orientation(vertical or horizontal)" << endl;
	
	for (int i = 1; i < 5; i++) {
		for (int j = 0; j < i; j++) {
			cout << "Place" << 5 - i << "tower ship" << endl;
			cin >> coordinate >> orient;
			place_ship(ship_deck, coordinate, orient, 5-i);
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (ship_deck[j + 10 * i] == 1) cout << 1;
			else cout << 0;
		}
		cout << endl;
	}
}

void random::place_ships() {
	int coordinate;
	string orient;
	int temp = 5;

	for (int i = 1; i < 5; i++) {
		for (int j = 0; j < i; j++) {
			temp = 5;
			while (temp == 5) {
				temp = rand() % 2;
				if (temp == 0) orient = "horizontal";
				else orient = "vertical";
				coordinate = rand() % 100;
				//cout << orient << coordinate << endl;
				try {
					place_ship(ship_deck, coordinate, orient, 5 - i);
				}
				catch (exception err) {
					temp = 5;
				}
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (ship_deck[j + 10 * i] == 1) cout << 1;
			else cout << 0;
		}
		cout << endl;
	}
}
void clever::place_ships() {
	for (int i = 0; i < 10; i++) {
		ship_deck[i * 10] = 1;
		ship_deck[i * 10 + 2] = 1;
	}
	ship_deck[20] = 0;
	ship_deck[50] = 0;
	ship_deck[62] = 0;
	ship_deck[22] = 0;
	
	ship_deck[99] = 1;
	ship_deck[9] = 1;
	for (int i = 0; i < 2; i++) {
		int coord = rand() % 6 + 10*(rand() % 3) + 20 + 30*i;
		ship_deck[coord] = 1;
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (ship_deck[j + 10 * i] == 1) cout << 1;
			else cout << 0;
		}
		cout << endl;
	}
}
