#include <iostream>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <cmath>
#include <complex>
//#include "Constants.h"
//#include "Ring.h"
#include "Matrix.h"
//#include "RationalNumber.h"
#include "polynom.h"


int main(int argc, char const *argv[])
{
	Polynom a;
	std::complex<double> z1(-6554,-4449);
	std::complex<double> z2(14245,-5796);
	std::complex<double> z3(-2562,12537);
	std::complex<double> z4(-4165,-4200);
	std::complex<double> z5(1610,-315);
	std::complex<double> z6(-105,252);
	std::complex<double> z7(-14,-21);
	std::complex<double> z8(1,0);
	std::vector<std::complex<double>> v1 = {z1,z2};
	std::vector<std::complex<double>> v2 = {z1, z2, z3, z4, z5, z6, z7, z8};
	std::vector<std::complex<double>> v3 = {z1, z2};
	std::vector<std::complex<double>> v4 = {z1, -z2};
	/*for(size_t j = 0; j < v.size(); ++j)
	{
		std::cout<< v[j];
	}*/
	ZeroCheck(z2);
	//std::cout<<z2<<"this is z2"<< std::endl;
	Polynom q1(v1);
	//std::cout<< q1;
	Polynom q2(v2);
	//std::cout<<q2;
	Polynom q3 = q1*q2;
	std::cout<<q3;
	std::vector<std::complex<double>> roots = (q2*q2).FindRoots();
	for(size_t j = 0; j < roots.size(); ++j)
	{
		std::cout<< roots[j]<<std::endl << (q2*q2).ValueInPoint(roots[j]) << "<- vALiNRoot"<<std::endl;
	}
	std::cout<<q2;
	return 0;
}