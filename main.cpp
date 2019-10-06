#include "RNA.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int main() {
	RNA rna1(1000, 'C');
	RNA rna2(499, 'C');
	RNA rna4(10, 'A');
	//std::cout << 1;
	//RNA rna3 = rna2 + rna2 + 'C' + 'C';
	//rna2[5] = 'A';
	//rna1[5] = 'U';
	//if (rna1 == rna2) std::cout << 1;
	//rna1 = rna2 + 'C';
	RNA rna3(!(rna1 + rna2) + rna4 + 'G');
	rna4 = !rna3;
	if (rna3.iscomplementary(rna4)) cout << rna3[1400];
	//rna4 = rna3 + 'C';
	//rna2[201] = 'C';
 	//rna2[100] = 'C';
	//rna2[200] = rna2[100];
	//std::cout << rna3.get(200) << rna3.get(201) << rna3.get(202) << rna3.get(203) << "\n";
	//std::cout << (ref1.link)->totallen;
	//rna2.place(203, 'C');
	//std::cout << rna3[1303] << "\n";
	//for (int i = 0; i < 8; i++)
	//	std::cout << ((rna2.split(20).rna[0] >> i) & 1) << "\n";


}