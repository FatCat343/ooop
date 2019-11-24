#include "parser.h"

Parser::Parser() {}
Parser::~Parser() {}
Parser::Parser(string filename) {
	file.open(filename);
	status = -1;
}

bool Parser::EndOfCom() {
	if (status == 1) return 1;
	else return 0;
}

bool Parser::EndOfFile() {
	if (file.eof) return 1;
	else return 0;
}
void Parser::newline() {
	string line;
	getline(file, line);//check on eof
	if (line == "desc" || line == "csed") {
		if (line == "desc") status = 0;
		else status = 1;
	}
	else {
		if (status == 0) {
			size_t start = 0, finish;
			while (line[finish] != ' ') finish++;
			string data = line.substr(start, finish - start);
			num = stoi(data); // convert to char* and convert to int
			start = finish;
			while (line[finish] != ' ') finish++;
			com = line.substr(start, finish - start);
			start = finish;
			args = line.substr(start, line.length - start);
		}
		if (status == 1);// return error
	}
}

size_t Parser::getnum() {
	return num;
}

string Parser::getcom() {
	return com;
}

string Parser::getargs() {
	return args;
}
size_t Parser::InstructionNum() {
	string data, space;
	file >> data;
	if (!(file.eof)) file >> space;
	size_t number = stoi(data);
	return number;
}