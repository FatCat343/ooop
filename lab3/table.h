#pragma once
#include <iostream>

using namespace std;

class table {
private:
	size_t size;
	size_t* deck;

public:
	table() { deck = new size_t[10 * 10]; size = 10; }
	~table() { delete[] deck; }

};