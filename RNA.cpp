#include "RNA.h"
#include <stdio.h>
#include <string.h>

//char convert(int*);
//void convert(int*, char);

void RNA::add(char nukl) { //strategy of adding : *2
	if (usedlen < totallen) RNA::place(usedlen, nukl);
	else {
		char* array = new char[2 * (totallen / amountofnukl)];
		strcpy(array, rna);
		delete[] rna;
		char* rna = array;
		RNA::place(usedlen, nukl);
		totallen = totallen * 2;
	}
	usedlen++;
}

RNA::RNA() {
	rna = new char;
	usedlen = 0;
	totallen = 0;
	lastindex = 0;
}
RNA::RNA(RNA& orig) {
	unsigned int max = orig.totallen / amountofnukl;
	rna = new char[max + 1];
	for (unsigned int i = 1; i <= max; i++) {
		rna[i] = orig.rna[i];
	}
	usedlen = orig.usedlen;
	totallen = orig.totallen;
	lastindex = orig.lastindex;
}

RNA::RNA(unsigned int length, char nukl= 'A') { //0 - adenin, 1 - guanin, 2 - citasin, 3 - uracil
	unsigned int arsize = length / amountofnukl;
	if (length % amountofnukl != 0) arsize++;
	rna = new char[arsize+1];
	totallen = arsize * amountofnukl;
	usedlen = length;
	lastindex = 0;
	int* code = new int[2];
	convert(code, nukl);
	unsigned int i = 0;
	int spacecount = amountofnukl;
	unsigned int charcount = 0;
	rna[charcount] = 0;
	for (i; i < usedlen; i++) { //filling with nukleotide
		if (spacecount <= 0) {
			charcount++;
			spacecount = amountofnukl;
			rna[charcount] = 0;
		}
		rna[charcount] = (((rna[charcount] << 1) + code[0]) << 1 )+ code[1];
		spacecount--;
	}
	delete[] code;
}

RNA::~RNA() {
	delete[] rna;
}

void RNA::place(unsigned int index, char nukl) {
		unsigned int charnum = (index - 1) / amountofnukl;
		unsigned int pos = (index - 1) % amountofnukl;
		int* code = new int[2];
		convert(code, nukl);
		char copy = rna[charnum];
		char mask1 = 0, mask2 = 0;
		int i = 0;
		for (i; i < 8; i++) {
			mask1 = mask1 << 1;
			mask2 = mask2 << 1;
			if ((i == 2 * pos) || (i == 2 * pos + 1)) {
				mask1 = mask1 + 0;
				if (i == 2 * pos) mask2 = mask2 + code[0];
				if (i == 2 * pos + 1) mask2 = mask2 + code[1];
			}
			else {
				mask1 = mask1 + 1;
				mask2 = mask2 + 0;
			}

		}
		copy = copy & mask1;
		copy = copy | mask2;
		rna[charnum] = copy;
		delete[] code;
	
}

char RNA::get(unsigned int index) {
	unsigned int charnum = (index - 1) / amountofnukl;
	unsigned int pos = (index - 1) % amountofnukl; //-1??
	char copy = rna[charnum];
	int move = amountofnukl - pos - 1;
	copy = copy >> move * 2;
	int* code = new int[2];
	code[1] = copy & 00000001;
	code[0] = (copy >> 1) & 00000001;
	char nukl = convert(code);
	delete[] code;
	return nukl;
}

void RNA::operator+(RNA & added) {
	if (added.usedlen + usedlen > totallen) {
		char* array = new char[usedlen + added.usedlen];
		strcpy(array, rna);
		delete[] rna;
		char* rna = array;
	}
	unsigned int i = 0;
	for (i; i < added.usedlen; i++) RNA::add(added.rna[i]);
	added.~RNA();
}

bool RNA::operator==(RNA & another) {
	if (usedlen != another.usedlen) return 1;
	else {
		unsigned int i = 0;
		for (i; i <= (usedlen - 1) / amountofnukl; i++) {
			if (rna[i] != another.rna[i]) return 1;
		}
	}
	return 0;
}

RNA RNA::split(unsigned int index) {
	unsigned int charnum = (index - 1) / amountofnukl;
	unsigned int pos = (index - 1) % amountofnukl;
	RNA second(usedlen - index);
	unsigned int i = 0;
	for (i; i < usedlen - index; i++) {
		char nukl = get(i + index + 1);
		second.place(i + index + 1, nukl);
	}
	usedlen = index;
	second.totallen = (usedlen - index) / amountofnukl;
	if ((usedlen - index) % amountofnukl != 0) second.totallen++;
	second.usedlen = usedlen - index;
	return second;
}

bool RNA::iscomplementary(RNA & another) {
	if (usedlen != another.usedlen) return 1;
	else {
		unsigned int i = 0;
		int* code1 = new int[2];
		int* code2 = new int[2];
		for (i; i <= (usedlen - 1) / amountofnukl; i++) {
			char nukl1 = get(i + 1);
			char nukl2 = another.get(i + 1);
			convert(code1, nukl1);
			convert(code2, nukl2);
			if (2 * code1[0] + code1[1] != 2 * code2[0] + code2[1]) return 1   ;
		}
	}
	return 0;
}

RNA RNA::operator!() {
	unsigned int i;
	RNA second(usedlen);
	for (i = 0; i < usedlen; i++) {
		char nukl = get(i + 1);
		int* code = new int[2];
		convert(code, nukl);
		int reversecode = ((amountofnukl - 1) - (code[0] * 2 + code[1]));
		code[0] = reversecode / 2;
		code[1] = reversecode % 2;
		nukl = convert(code);
		second.place(i + 1, nukl);
	}
	return second;
}

char RNA::operator[](unsigned int index) const {
	unsigned int charnum = (index - 1) / amountofnukl;
	unsigned int pos = (index - 1) % amountofnukl; //-1??
	char copy = rna[charnum];
	int move = amountofnukl - pos - 1;
	copy = copy >> move;
	int* code = new int[2];
	code[1] = copy & 00000001;
	code[0] = (copy >> 1) & 00000001;
	char nukl = convert(code);
	delete[] code;
	return nukl;
}

char& RNA::operator[](unsigned int index) {
	unsigned int charnum = (index - 1) / amountofnukl;
	unsigned int pos = (index - 1) % amountofnukl;
	lastindex = index;
	char nukl = get(index);
	return nukl;
}

//RNA& RNA::operator=(char& nukl) {
//	unsigned int charnum = (lastindex - 1) / amountofnukl;
//	unsigned int pos = (lastindex - 1) % amountofnukl;
//	place(lastindex, nukl);
//	return *this;
//}
//char& operator=(char& nukl1, )
char convert(int* code) {
	if (code[0] == 0 && code[1] == 0) return 'A';
	if (code[0] == 0 && code[1] == 1) return 'G';
	if (code[0] == 1 && code[1] == 0) return 'C';
	if (code[0] == 1 && code[1] == 1) return 'U';
}

void convert(int* code, char nukl) {
	if (nukl == 'A') {
		code[0] = 0;
		code[1] = 0;
	}
	if (nukl == 'G') {
		code[0] = 0;
		code[1] = 1;
	}
	if (nukl == 'C') {
		code[0] = 1;
		code[1] = 0;
	}
	if (nukl == 'U') {
		code[0] = 1;
		code[1] = 1;
	}
}