
#include "player.h"

player* init(string config) {
	if (config == "manual") player *p = new manual;
	else {
		if (config == "clever") player * p = new clever;
		else {
			if (config == "random") player * p = new random;
			else throw exception("wrong type of player");
		}
	}
}

int main() {
	srand(time(NULL));
	string config1, config2;
	cin >> config1 >> config2;
	player* p1, * p2;
	try {
		p1 = init(config1);
		p2 = init(config2);
		cout << "start!" << endl;
		p1->place_ships();
		cout << endl;
		p2->place_ships();
		cout << "ships placed" << endl;

		int counter = 0;
		while ((!p1->finish()) && (!p2->finish())) {
			p1->attack(*p2);
			if (!p2->finish()) p2->attack(*p1);
			cout << "Turn number:" << counter << endl;
			counter++;
		}
	}
	catch (exception err) {
		cout << err.what() << endl;
		return 0;
	}
	if (p1->getstatus() == 2) cout << "player 2 win";
	else cout << "player 1 win";
	return 0;
}