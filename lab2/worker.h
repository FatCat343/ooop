#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>

using namespace std;

class worker {
protected:
	string data;
public:
	virtual void ability(string) = 0;
};

class readfile : public worker {
public:
	virtual void ability(string);
};

class writefile : public worker {
public:
	virtual void ability(string);
};

class grep : public worker {
public:
	virtual void ability(string);
};

class sort : public worker {
public:
	virtual void ability(string);
};

class replace : public worker {
public:
	virtual void ability(string);
};

class dump : public worker {
public:
	virtual void ability(string);
};