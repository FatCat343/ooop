#pragma once
#define amountofnukl 4
#define _CRT_SECURE_NO_WARNINGS

class RNA;

class Reference {
public:
	Reference(RNA&, unsigned int);
	~Reference();
	Reference& operator=(Reference);
	Reference& operator=(char);
	operator char();
private:
	RNA* link;
	unsigned int index;
};

class RNA{
public:
	friend class Reference;
	RNA();
	RNA(unsigned int , char);
	RNA(RNA &);
	~RNA();
	RNA operator+(const RNA &); //соединение 2 цепочек
	RNA operator+(char);
	bool operator==(RNA &); //сравнение
	void place(unsigned int , char);
	//void add(char);
	char get(unsigned int) const;
	RNA split(unsigned int);
	bool iscomplementary(RNA &);
	RNA operator!();
	char operator[](unsigned int) const; //same as get
	Reference operator[](unsigned int);
	RNA operator=(const RNA&);
private:
	char* rna;
	unsigned int usedlen;
	unsigned int totallen;
};







