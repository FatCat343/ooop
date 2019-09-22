#pragma once
#define amountofnukl 4
#define _CRT_SECURE_NO_WARNINGS
class RNA
{
public:
	RNA();
	RNA(unsigned int , char);
	RNA(RNA &);
	~RNA();
	void operator+(RNA &); //соединение 2 цепочек
	bool operator==(RNA &); //сравнение
	void place(unsigned int , char);
	void add(char);
	char get(unsigned int);
	RNA split(unsigned int);
	bool iscomplementary(RNA &);
	RNA operator!();
	char operator[](unsigned int) const; //same as get
	char& operator[](unsigned int);
	//RNA& operator=(char&);
private:
	char* rna;
	unsigned int usedlen;
	unsigned int totallen;
	unsigned int lastindex;
};

char convert(int*);
void convert(int*, char);






