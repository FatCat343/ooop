#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <sstream>

#include "validator.h"
using namespace std;

class worker {
//protected:
//	string data;
public:
	virtual string ability(string, string) = 0;
};

class readfile_worker : public worker {
public:
	//friend class read_validator;
	virtual string ability(string, string);

};

class writefile_worker : public worker {
public:
	//friend class write_validator;
	virtual string ability(string, string);
	
};

class grep_worker : public worker {
public:
	virtual string ability(string, string);
	//class grep_validator;
};

class sort_worker : public worker {
public:
	virtual string ability(string, string);
	//class sort_validator;
};

class replace_worker : public worker {
public:
	virtual string ability(string, string);
	//class replace_validator;
};

class dump_worker : public worker {
public:
	virtual string ability(string, string);
	//class dump_validator;
};

//template <typename T>
//class Factory {
//public:
//	Factory() {};
//	~factory() {};
//	T& Create() {
//		return new T;
//	}
//};