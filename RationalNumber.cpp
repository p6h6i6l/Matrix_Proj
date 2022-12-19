#include "RationalNumber.h"

	void Rational::divide()
	{
		if(numerator == 0)
		{
			denumerator = 1;
			return;
		}

		long long gcd_a_b = gcd(std::abs(numerator), std::abs(denumerator));
		if( gcd != 0 )
		{
			numerator = numerator / gcd_a_b;
			denumerator = denumerator / gcd_a_b;
		}
		return;
	}
	Rational::Rational()
	{
		numerator = 0;
		denumerator = 1;
	}
	Rational::Rational(long long a)
	{
		numerator = a;
		denumerator = 1;
	}
	Rational::Rational(long long numerator_, long long denumerator_)
	{
		try
		{
			if( denumerator_ == 0)
			{
				numerator = 1;
				denumerator = 1;
				throw 0;
			}
			if(denumerator_ < 0 )
			{
				//std::cout << "Yes";
				numerator = -numerator_;
				denumerator = -denumerator_;
				divide();
				return;
			}
			else
			{
				numerator = numerator_;
				denumerator = denumerator_;
				divide();
				return;
			}
		}

		catch(int a)
		{	
			if(a == 0) 
			{
				std::cerr << "denumerator must be non zero, your number is 1/1"<< std::endl;
			}
		}
	}

	Rational::Rational(const Rational& another):numerator(another.numerator), denumerator(another.denumerator)
	{
		divide();
	}


	Rational& Rational ::operator = (const Rational& another )
	{
		if (&another  == this)
			return * this;
		Rational t(another);
		std::swap(t.numerator, numerator);
		std::swap(t.denumerator, denumerator);
		return *this;
	}

	Rational Rational :: operator + (const Rational& another)
	{
		Rational tmp(numerator*another.denumerator + another.numerator*denumerator, 
			denumerator*another.denumerator);

		return tmp;
	}

	Rational Rational :: operator * (const Rational& another)
	{
		Rational tmp(numerator*another.numerator, denumerator*another.denumerator);
		return tmp;
	}

	Rational Rational :: operator / (const Rational& another)
	{
		Rational tmp(numerator*another.denumerator, denumerator*another.numerator);
		return tmp;
	}

	Rational Rational :: operator - (const Rational& another)
	{
		Rational tmp(numerator*another.denumerator - another.numerator*denumerator, 
			denumerator*another.denumerator);

		return tmp;
	}

	Rational::~Rational()
	{
		return;
	}
	

long long gcd( long long a,long long b)
{
    while (a && b)
        if (a > b) a%=b;
        else b%=a;
    return a+b;
}

std::ostream& operator<<(std::ostream &os, const Rational& r)
{
	return os << r.numerator << "/" << r.denumerator;
}

double abs(const Rational& obj)
{
	double tmp1(obj.numerator);
	double tmp2(obj.denumerator);
	return std::abs(tmp1/tmp2);
}