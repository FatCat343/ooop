#include "parser.h"

Parser::~Parser() { file.close(); }
Parser::Parser() {
	file.open("workflow.txt");
	status = -1;
}

bool Parser::EndOfCom() {
	if (status == 1) return 1;
	else return 0;
}

bool Parser::EndOfFile() {
	if (file.eof()) return 1;
	else return 0;
}
void Parser::newline() {
	string line;
	getline(file, line);//check on eof
	cout << line << endl;
	if (line == "desc" || line == "csed") {
		if (line == "desc") status = 0;
		else status = 1;
	}
	else {
		if (status == 0) {
			size_t start = 0, finish = 0;
			size_t words = 0;
			string data;
			while ((finish <= line.length()) && (words < 2)) {
				if (line[finish] == ' ') {
					data = line.substr(start, finish - start);
					words++;
					if (words == 1) {
						num = stoi(data);
						finish = finish + 2;
					}
					if (words == 2) com = data;
					cout << "data is " << data << endl;
					finish++;
					start = finish;
				}
				else finish++;
			}
			if (start <= line.length()) {
				data = line.substr(start, line.length() - start);
				if (words == 2) args = data;
				if (words == 1) com = line.substr(start, line.length() - start);
			}
			//size_t start = 0, finish = 0;
			//while (line[finish] != ' ') finish++;
			//string data = line.substr(start, finish - start);
			//num = stoi(data); // convert to char* and convert to int
			//start = finish + 3;
			//finish = start;
			//while ((line[finish] != ' ') && (line[finish] != '\n')) finish++;
			//com = line.substr(start, finish - start);
			//start = finish + 1;
			//finish = start;
			//cout << line.length() << "   " << finish << endl;
			//if (line.length() > start) args = line.substr(start, line.length() - start);
			//else args.clear();
		}
		if (status == 1) cout << "misssed end of command";// return error
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
	if (!(file.eof())) file >> space;
	size_t number = stoi(data);
	return number;
}