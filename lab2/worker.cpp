#include "worker.h"

string readfile_worker::ability(string data, string args) {
	ifstream file;
	string text;
	string line;
	file.open(args);
	//check if file opened
	while (!file.eof()) {
		getline(file, line);
		data = data + line + "\n";
	}
	file.close();
	return data;
}

string writefile_worker::ability(string data, string args) {
	fstream file;
	file.open(args);
	file << data;
	return data;
}

string grep_worker::ability(string data, string args) {
	string line;
	
	char * newdata = const_cast<char*>(data.c_str());
	//strcpy(newdata, data.c_str());
	//cout << data << endl;
	istringstream stream(newdata);
	data.clear();
	//const char delim[2] = "\n";
	//cout << "start" << endl;
	//size_t start = 0;
	//start = data.find('\n', start);


	//line = strtok(newdata, delim);
	//cout << newdata << endl;
	while (getline(stream, line)) {
		//cout << line << endl;
		size_t index = line.find(args);
		
		if (index < string::npos) data = data + line + "\n";
		//line = strtok(NULL, "\n");
	}
	return data;
}

string sort_worker::ability(string data, string args) {
	vector <string> text;
	string line;
	//cout << data << endl;
	char* newdata = const_cast<char*>(data.c_str());
	//strcpy(newdata, data.c_str());
	istringstream stream(newdata);
	data.clear();

	//while (newdata != NULL) {
	//	line = strtok(newdata, "\n");
	//	text.push_back(line);
	//}
	//cout << "dhgfhjd" << endl;
	while (getline(stream, line)) {
		cout << "dhgfhjd" << endl;
		text.push_back(line);
	}
	std::sort(text.begin(), text.end(), less<string>());
	size_t length = text.size();
	for (size_t i = 0; i < length; i++) {
		data = data + text[i] + "\n";
	}
	return data;
}

string replace_worker::ability(string data, string args) {
	string from, to;
	char* newdata = const_cast<char*>(args.c_str());
	//strcpy(newdata, data.c_str());
	from = strtok(newdata, " ");
	to = strtok(NULL, " ");
	//cout << from << "   " << to << endl;
	size_t start = 0;
	while (start <( data.length() - from.length())) {
		start = data.find(from, start);
		cout << start << " && " << data.length() << endl;
		if (start >= data.length()) break;
		data.replace(start, from.length(), to);
		start = start + to.length();
	}
	return data;
}

string dump_worker::ability(string data, string args) {
	fstream file;
	file.open(args);
	file << data;
	data.clear();
	return data;
}

