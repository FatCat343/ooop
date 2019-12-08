#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <map>
#include <fstream>
using namespace std;
class validator {
public:
	virtual void input_validation(string) = 0;
};

class read_validator : public validator {
public:
	virtual void input_validation(string);
};

class write_validator : public validator {
public:
	virtual void input_validation(string);
};

class grep_validator : public validator {
public:
	virtual void input_validation(string);
};

class sort_validator : public validator {
public:
	virtual void input_validation(string) {};
};

class dump_validator : public validator {
public:
	virtual void input_validation(string) ;
};

class replace_validator : public validator {
public:
	virtual void input_validation(string);
};