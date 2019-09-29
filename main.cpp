#include "RNA.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

int main() {
	RNA rna1(999, 'C');
	RNA rna2(1999, 'G');
	RNA rna4(10, 'A');
	
	RNA rna3;
	//rna1 = rna2 + 'C';
	rna3 = !(rna1 + rna2) + rna4;
	//rna4 = rna3 + 'C';
	//rna2[201] = 'C';
 	//rna2[100] = 'C';
	//rna2[200] = rna2[100];
	//std::cout << rna3.get(200) << rna3.get(201) << rna3.get(202) << rna3.get(203) << "\n";
	//std::cout << (ref1.link)->totallen;
	//rna2.place(203, 'C');
	std::cout << rna3[1303] << "\n";
	//for (int i = 0; i < 8; i++)
	//	std::cout << ((rna2.split(20).rna[0] >> i) & 1) << "\n";


}