#include "LinearAlgebra.h"

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
	std::complex<double> z9(2,0);
	std::complex<double> z10(7,0);
	std::complex<double> z11(-2,0);
	std::complex<double> z12(5,0);
	std::complex<double> z0(0,0); 
	std::complex<double> z13 (18,0);
	std::complex<double> z14 (15,0);
	std::complex<double> z15 (-1,0);
	std::vector<std::complex<double>> v1 = {z1,z2};
	std::vector<std::complex<double>> v2 = {z1, z2, z3, z4, z5, z6, z7, z8};
	std::vector<std::complex<double>> v3 = {z1, z2};
	std::vector<std::complex<double>> v4 = {z1, -z2};
	std::vector<std::complex<double>> v5 = {z8, z9, z8};
	std::vector<std::complex<double>> v6 = {z8, z8};
	std::vector<std::complex<double>> v7 = {z8, z11, z8, z10, z8};
	std::vector<std::complex<double>> v8 = {z9, z0, z12, z8};
	std::vector<std::complex<double>> v9 = {ComplexZero, z13, z14, z15};
	Polynom q100(v9);
	std::vector<std::complex<double>> tmp = q100.FindRoots();
	std::cout<<q100;
	for(int i = 0; i < tmp.size(); i++)
		std::cout<<tmp[i] << std::endl;
	std::cout<<"^------ roots";

	ZeroCheck(z2);
	Polynom q1(v1);
	Polynom q2(v2);
	Polynom q3 = q1*q2;
    Polynom q4(v7);
    Polynom q5(v8);
    std::vector<Polynom> tmp1 = DivideTwoPolynom(q4,q5);
    Polynom tmp2 = q4/q5;
    out_vector<Polynom>(tmp1);
    Matrix<double> a1(5,5);
    Matrix<double> b1(5,1);
    a1.GaussMethod(b1);
    std::string str = "test.txt";
    Matrix<std::complex<double>> A(str);
    std::cout<<A << "<---- THIS IS A" << std::endl;
    A.ToJordanForm();
    std::cout<<A;
	return 0;
}