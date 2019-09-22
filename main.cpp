#include "RNA.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

int main() {
	RNA rna1(999, 'G');
	RNA rna2(rna1);
	//rna2[200] = 'C';
	std::cout << rna2.get(200);
	//std::cout << rna2.rna[200];

}