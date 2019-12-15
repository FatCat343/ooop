#include "player.h"

//void manual::attack(player& enemy) {
//	int coordinate;
//	cout << "enter coordinate to attack, f.e. 08" << endl;
//	cin >> coordinate;
//	if ((coordinate >= 100) || (coordinate < 0)) throw exception("wrong coordinate to attack");
//
//	char res = enemy.hit(coordinate);
//	if (res == 0) cout << "miss" << endl;
//	if (res == 1) cout << "hit" << endl;
//	if (res == 2) cout << "kill" << endl;
//}
//
//void clever::attack(player& enemy) {
//	int coordinate = -1;
//	for (int i = 0; i < 100; i++) {
//		if (battle_deck[i] == 2) {
//			coordinate = i;
//			break;
//		}
//	}
//	if (coordinate == -1 {
//		for (i = 0; i < 100; i++) {
//			if (battle_deck[i] == 0) {
//				coordinate = i;
//					break;
//			}
//		}
//	}
//
//}