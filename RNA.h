#pragma once
#define amountofnukl 4
//#define _CRT_SECURE_NO_WARNINGS

class RNA;

class Reference {
public:
	Reference(RNA&, size_t);
	~Reference();
	Reference& operator=(Reference);
	Reference& operator=(char);
	operator char();
private:
	RNA* link;
	size_t index;
};

class RNA{
public:
	friend class Reference;
	RNA();
	RNA(size_t, char);
	RNA(const RNA &);
	~RNA();
	RNA operator+(const RNA &); //соединение 2 цепочек
	RNA operator+(char);
	bool operator==(const RNA &); //сравнение
	bool operator!=(const RNA&);
	void place(size_t, char);
	//void add(char);
	char get(size_t) const;
	RNA split(size_t);
	bool iscomplementary(RNA &);
	RNA operator!();
	char operator[](size_t) const; //same as get
	Reference operator[](size_t);
	RNA& operator=(const RNA&);
private:
	char* rna;
	size_t usedlen;
	size_t totallen;
};







