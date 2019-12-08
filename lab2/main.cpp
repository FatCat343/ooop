#include <iostream>
#include "worker.h"
#include "parser.h"
#include <map>
using namespace std;

int main() {
	map<string, worker*> workers;
	map<size_t, string> workflow;
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
		if (pars.getstatus() == 0) {
			size_t num = pars.getnum();
			string name = pars.getcom();
			string args = pars.getargs();
			cout << name << "-" << args << "-" << endl;
			try {
				if (workflow.end() != workflow.find(num)) throw num;
			}
			catch (int num) {
				cout << "Number" << num << "was used several times" << endl;
			}
			workflow[num] = name;
			arguments[num] = args;
		}
		//cout << "parametres are : " << num  << " , "<< name << " , " << args << endl;
	}
	string text;
	size_t iteration = 0;
	while (!pars.EndOfFile()) {
		size_t instruction = pars.InstructionNum();
		cout << instruction << endl; 
		try {
			if ((workflow[instruction] == "readfile") && (iteration != 0)) throw instruction;
			if ((workflow[instruction] == "writefile") && (!(pars.EndOfFile()))) throw instruction;
			if (workflow.find(instruction) == workflow.end()) throw instruction; //existing of instruction
		}
		catch (int x){
			cout << "wrong accessing to file in" << x << "line" << endl; 
		}
		text = workers[workflow[instruction]]->ability(text, arguments[instruction]);
		
		cout << text << endl;
		cout << endl;
		iteration++;

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