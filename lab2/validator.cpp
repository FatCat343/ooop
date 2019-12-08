#include "validator.h"

void read_validator::input_validation(string arguments) {
	ifstream file;
	file.open(arguments);
	try {
		if (!file.is_open()) throw 1;
	}
	catch (int x){
		cout << "file " << arguments << " could not be opened." << endl;
	}
	file.close();
}

void write_validator::input_validation(string arguments) {
	ofstream file;
	file.open(arguments);
	try {
		if (!file.is_open()) throw 1;
	}
	catch (int x) {
		cout << "file " << arguments << " could not be opened." << endl;
	}
	file.close();
}

void replace_validator::input_validation(string arguments) {
	try {
		size_t start = 0;
		start = arguments.find(" ", start);
		if ((start == string::npos) || (start == arguments.length())) throw 1; //1 arg out of 2
	}
	catch (int x) {
		cout << "not enough arguments in replace block" << endl;
	}
}

void grep_validator::input_validation(string arguments) {
	try {
		if (arguments.length() == 0) throw 1;
	}
	catch (int x) {
		cout << "not enough arguments in grep block" << endl;
		
	}
}

void dump_validator::input_validation(string arguments) {
	ofstream file;
	file.open(arguments);
	try {
		if (!file.is_open()) throw 1;
	}
	catch (int x) {
		cout << "file " << arguments << " could not be opened." << endl;
	}
	file.close();
}