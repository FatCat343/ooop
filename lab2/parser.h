#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>

using namespace std;
class Parser {
public:
	Parser();
	~Parser();
	Parser(string);
	bool EndOfCom();
	bool EndOfFile();
	size_t getnum();
	string getcom();
	string getargs();
	void newline();
	size_t InstructionNum();
private:
	ifstream file;
	//string line;
	size_t num;
	string com;
	string args;
	int status;
};
