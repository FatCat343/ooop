#include "worker.h"

void readfile::ability(string args) {
	ifstream file;
	string s;
	file.open(args);
	//check if file opened
	while (!file.eof()) {
		file >> s;
		data = data + s;
	}
	file.close();
}

void writefile::ability(string args) {
	fstream file;
	file.open(args);
	file << data;
}

void grep::ability(string args) {

}

void sort::ability(string args) {

}

void replace::ability(string args) {
	string from, to;
	char* input = args.c_str;
	from = strtok(input, " ");
	to = strtok(input, " ");

	size_t start = 0;
	while (start >= data.length - from.length) {
		start = data.find(from, start);
		data.replace(start, from.length, to);
		start = start + to.length;
	}
}

void dump::ability(string args) {

}