#include "validator.h"

void read_validator::input_validation(string arguments) {
	ifstream file;
	file.open(arguments);
	try {
		if (!file.is_open()) throw exception("input file could not be opened");
	}
	catch (const exception err) {
		cout << err.what() << endl;
		throw exception();
	}
	file.close();
}

void write_validator::input_validation(string arguments) {
	ofstream file;
	file.open(arguments);
	try {
		if (!file.is_open()) throw exception("output file could not be opened");
	}
	catch (const exception err) {
		cout << err.what() << endl;
		throw exception();
	}
	file.close();
}

void replace_validator::input_validation(string arguments) {
	try {
		size_t start = 0;
		start = arguments.find(" ", start);
		if ((start == string::npos) || (start == arguments.length())) throw exception("not enough arguments in repkace block"); //1 arg out of 2
	}
	catch (const exception err) {
		cout << err.what() << endl;
		throw exception();
	}
}

void grep_validator::input_validation(string arguments) {
	try {
		if (arguments.length() == 0) throw exception("not enough arguments in grep block");
	}
	catch (const exception err) {
		cout << err.what() << endl;
		throw exception();
	}
}

void dump_validator::input_validation(string arguments) {
	ofstream file;
	file.open(arguments);
	try {
		if (!file.is_open()) throw exception("dump file could not be opened");
	}
	catch (const exception err) {
		cout << err.what() << endl;
		throw exception();
	}
	file.close();
}

 