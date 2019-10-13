#include "RNA.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

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

RNA::RNA() { 
	rna = new char [1];
	usedlen = 0;
	totallen = 4;
}
RNA::RNA(const RNA& orig) { 
	size_t max = orig.totallen / amountofnukl;
	rna = new char[max + 1];
	for (size_t i = 0; i < max; i++) {
		rna[i] = orig.rna[i];
	}
	usedlen = orig.usedlen;
	totallen = orig.totallen;
}

RNA::RNA(size_t length, char nukl= 'A') { //0 - adenin, 1 - guanin, 2 - citasin, 3 - uracil checked
	size_t arsize = (length) / amountofnukl;
	if ((length) % amountofnukl != 0) arsize++;
	rna = new char[arsize];
	totallen = arsize * amountofnukl;
	usedlen = length;
	int* code = new int[2];
	convert(code, nukl);
	size_t i = 0;
	int spacecount = amountofnukl;
	size_t charcount = 0;
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
	rna[charcount] = rna[charcount] << (spacecount * 2);
	delete[] code;
}

RNA::~RNA() { 
	//std::cout << "destructor finished\n";
	delete[] rna;
}

void RNA::place(size_t index, char nukl) {
	size_t charnum = (index - 1) / amountofnukl;
	size_t pos = (index - 1) % amountofnukl;
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

char RNA::get(size_t index) const {
	size_t charnum = (index - 1) / amountofnukl;
	size_t pos = (index - 1) % amountofnukl;
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

RNA RNA::operator+(const RNA & added) {
	size_t i = 1;
	if (added.usedlen + usedlen > totallen) {
		RNA result(added.usedlen + usedlen);
		for (i = 0; i < totallen/4; i++) {
			result.rna[i] = rna[i];
		}
		i = 1;
		for (i; i <= added.usedlen; i++) {
			char nukl = added.get(i);
			result.place(i + usedlen, nukl);
		}
		return result;
	}
	else {
		RNA result(*this);
		i = 1;
		for (i; i <= added.usedlen; i++) {
			char nukl = added.get(i);
			result.place(i + usedlen, nukl);
		}
		return result;

	}
}
RNA RNA::operator+(char nukl) { //strategy of adding : *2
	if (usedlen < totallen) {
		RNA result(*this);
		result.place(usedlen + 1, nukl);
		result.usedlen++;
		return result;
	}
	else {
		RNA result(totallen * 2);
		size_t arsize = totallen / amountofnukl;
		for (size_t i = 0; i < arsize; i++) {
			result.rna[i] = this->rna[i];
		}
		result.place(usedlen + 1, nukl);
		result.usedlen = usedlen ++;
		return result;
	}
}
bool RNA::operator==(const RNA & another) {
	if (usedlen != another.usedlen) return 0;
	else {
		size_t i = 0;
		for (i; i < totallen / amountofnukl; i++) {
			if (rna[i] != another.rna[i]) return 0;
		}
	}
	return 1;
}

bool RNA::operator!=(const RNA& another) {
	if (*this == another) return 0;
	else return 1;
}

RNA RNA::split(size_t index) {
	size_t charnum = (index - 1) / amountofnukl;
	size_t pos = (index - 1) % amountofnukl;
	RNA second(usedlen - index);
	size_t i = 0;
	for (i; i < usedlen - index; i++) {
		char nukl = get(i + index + 1);
		second.place(i + 1, nukl);
	}
	usedlen = index;
	return second;
}

bool RNA::iscomplementary(RNA & another) {
	if (usedlen != another.usedlen) return 0;
	else {
		size_t i = 0;
		int* code1 = new int[2];
		int* code2 = new int[2];
		for (i; i < usedlen; i++) {
			char nukl1 = get(i + 1);
			char nukl2 = another.get(i + 1);
			convert(code1, nukl1);
			convert(code2, nukl2);
			if (2 * code1[0] + code1[1] + 2 * code2[0] + code2[1] != amountofnukl-1) return 0;
		}
		delete[] code1;
		delete[] code2;
	}
	return 1;
}

RNA RNA::operator!() { 
	size_t i;
	RNA second(usedlen);
	int* code = new int[2];
	for (i = 0; i < usedlen; i++) {
		char nukl = get(i + 1);
		convert(code, nukl);
		int reversecode = ((amountofnukl - 1) - (code[0] * 2 + code[1]));
		code[0] = reversecode / 2;
		code[1] = reversecode % 2;
		nukl = convert(code);
		second.place(i + 1, nukl);
	}
	delete[] code;
	return second;
}

char RNA::operator[](size_t index) const {
	if (index > usedlen) index = 1;
	size_t charnum = (index - 1) / amountofnukl;
	size_t pos = (index - 1) % amountofnukl;
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

RNA& RNA::operator=(const RNA & second) {
	//std::cout << "= get " << second.usedlen << "\n";
	if (*this == second) return *this;
	else {
		if (totallen != second.totallen){
			delete[] rna;
			char *array = new char[second.totallen / amountofnukl];
			rna = array;
			totallen = second.totallen;
		}
		usedlen = second.usedlen;
		size_t arsize = totallen / amountofnukl;
		for (size_t i = 0; i < arsize; i++) {
			rna[i] = second.rna[i];
		}
		//std::cout << "= returned " << usedlen << "\n";
		return *this;
	}
}
Reference::Reference(RNA & rna1, size_t indx) {
	index = indx;
	link = &rna1;
	//std::cout << "ref constructor finished\n";
}

Reference::~Reference() { 
	//std::cout << "ref destructor finished\n";
}

Reference& Reference::operator=(Reference second) { 
	(*link).place(index, (second.link)->get(second.index));
	return *this;
}

Reference& Reference::operator=(char nukl) { 
	(*link).place(index, nukl);
	return *this;
}

Reference RNA::operator[](size_t index) {
	if (index > usedlen) index = 1;
	Reference nukl(*this, index);
	return nukl;
}

Reference::operator char() {
	char nukl = (*link).get(index);
	return nukl;
}

