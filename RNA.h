#pragma once
#define amountofnukl 4
class RNA
{
public:
	RNA(unsigned int);
	RNA(unsigned int , char);
	~RNA();
	void operator+(RNA); //соединение 2 цепочек
	bool operator==(RNA); //сравнение
	void place(unsigned int, char);
	void add(char);
	char get(unsigned int);
	RNA split(unsigned int);
	bool iscomplementary(RNA);
	RNA operator!();
private:
	char* rna;
	unsigned int usedlen;
	unsigned int totallen;
};

//char convert(int*);
//void convert(int*, char);






