#ifndef POLYNOM_H
#define POLYNOM_H


#include "SomeLibs.h"
#include "Constants.h"
class Polynom;	
void ZeroCheck(std::complex<double> &number);
std::complex<double> ValueInPoint(Polynom & pol, std::complex<double> point);
std::complex<double> DerivativeInPoint(Polynom & pol, std::complex<double> point);
template <typename T>
void out_vector(std::vector<T>& vect)
{
	for(size_t i = 0 ; i < vect.size(); ++i)
		std::cout<< vect[i]<<std::endl;
	std::cout<< std::endl;
	return;
}

class Polynom final
{
private:
	std::vector<std::complex<double>> coefs;
	size_t degree;
	friend std::ostream& operator<<(std::ostream &os, const Polynom& r);
	template <typename T>
	friend
	void out_vector(std::vector<T>& vect);
	friend
	std::vector<Polynom> DivideTwoPolynom(const Polynom& divisible,const Polynom& divisor);
public:
	Polynom();
	Polynom(std::complex<double> a);
	Polynom(long long a);
	Polynom(std::vector<std::complex<double>>& coefs_, size_t degree_);
	Polynom(std::vector<std::complex<double>>& coefs_);
	Polynom operator + (const Polynom& another) const;
	Polynom operator * (const Polynom& another);
	Polynom operator - (const Polynom& another);
	Polynom operator / (const Polynom& another);
	std::complex<double> DerivativeInPoint(std::complex<double> point);
	std::complex<double> ValueInPoint( std::complex<double> point);
	std::vector<std::complex<double>> FindRoots();
	bool CheckNumberLikeARoot(std::complex<double> root);
	bool CheckArrayLikeARoots(const std::vector<std::complex<double>>& roots);
	Polynom DivideToRoot(std::complex<double> root);
	~Polynom();
};

std::vector<Polynom> DivideTwoPolynom(const Polynom& divisible,const Polynom& divisor);
std::ostream& operator<<(std::ostream &os, const Polynom& r);
std::vector<std::vector<std::complex<double>>> multiplicity(const std::vector<std::complex<double>>& roots);


#endif // POLYNOM_H