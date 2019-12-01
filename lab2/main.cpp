#include <iostream>
#include "worker.h"
#include "parser.h"
#include <map>
using namespace std;

int main() {
	map<string, worker*> workers;
	map<size_t, worker*> workflow;
	map<size_t, string> arguments;
	
	workers["readfile"] = new readfile_worker;
	workers["writefile"] = new writefile_worker;
	workers["grep"] = new grep_worker;
	workers["sort"] = new sort_worker;
	workers["replace"] = new replace_worker;
	workers["dump"] = new dump_worker;

	Parser pars;
	pars.newline();
	while (!pars.EndOfCom()) {
		pars.newline();
		size_t num = pars.getnum();
		string name = pars.getcom();
		string args = pars.getargs();
		
		workflow[num] = workers[name];
		arguments[num] = args;

		cout << "parametres are : " << num  << " , "<< name << " , " << args << endl;
	}
	string text;
	while (!pars.EndOfFile()) {
		size_t instruction = pars.InstructionNum();
		cout << instruction << endl; 

		text = workflow[instruction]->ability(text, arguments[instruction]);
		
		cout << text << endl;
		cout << endl;


	}

	return 0;
	//ifstream file;
	//file.open("workflow.txt");
	//string line;
	//if (file) {
	//	while (getline(file, line)) {
	//		cout << line << endl;
	//	}
	//}
	//else cout << "enable to open file" << endl;
	//file.close();

}