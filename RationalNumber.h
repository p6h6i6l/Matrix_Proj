#ifndef RATIONAL_H
#define RATIONAL_H



#include<iostream>
class Rational;
std::ostream& operator<<(std::ostream &os, const Rational& r);
long long gcd( long long a,long long b);

class Rational
{
private:
	long long numerator;
	long long denumerator;
	friend std::ostream& operator<<(std::ostream &os, const Rational& r);
	friend double abs(const Rational& obj);
public:
	void divide();
	Rational();
	Rational(long long a);
	Rational(long long numerator_, long long denumerator_);
	Rational(const Rational& another);
	Rational& operator = (const Rational& another );
	Rational operator + (const Rational& another);
	Rational operator * (const Rational& another);
	Rational operator / (const Rational& another);
	Rational operator - (const Rational& another);
	~Rational();	
};

long long gcd( long long a,long long b);
std::ostream& operator<<(std::ostream &os, const Rational& r);
double abs(const Rational& obj);

#endif