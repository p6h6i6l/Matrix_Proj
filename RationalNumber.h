class Rational;
std::ostream& operator<<(std::ostream &os, const Rational& r);
long long gcd( long long a,long long b);

class Rational
{
private:
	long long numerator;
	unsigned long long denumerator;
	friend std::ostream& operator<<(std::ostream &os, const Rational& r);
public:

	void out()
	{
		std::cout<< numerator << std::endl << denumerator << std::endl;
	}


	void divide()
	{
		long long gcd_a_b = gcd(abs(numerator), abs(denumerator));
		if( gcd != 0 )
		{
			numerator = numerator / gcd_a_b;
			denumerator = denumerator / gcd_a_b;
		}
		return;
	}
	Rational()
	{
		numerator = 0;
		denumerator = 1;
	}
	Rational(long long a)
	{
		numerator = a;
		denumerator = 1;
	}
	Rational(long long numerator_, long long denumerator_)
	{
		try
		{
			if( denumerator_ <= 0)
			{
				numerator = 1;
				denumerator = 1;
				throw 0;
			}
			numerator = numerator_;
			denumerator = denumerator_;
			divide();
		}

		catch(int a)
		{	
			if(a == 0)
				std::cerr << "denumerator must be more than zero, your number is 1/1"<< std::endl;
		}
	}

	Rational(const Rational & another):numerator(another.numerator), denumerator(another.denumerator)
	{
		divide();
	}


	Rational& operator = (const Rational& another )
	{
		if (&another  == this)
			return * this;
		Rational t(another);
		std::swap(t.numerator, numerator);
		std::swap(t.denumerator, denumerator);
		return *this;
	}

	Rational operator + (const Rational& another)
	{
		Rational tmp(numerator*another.denumerator + another.numerator*denumerator, 
			denumerator*another.denumerator);

		return tmp;
	}

	Rational operator * (const Rational& another)
	{
		Rational tmp(numerator*another.numerator, denumerator*another.denumerator);
		return tmp;
	}

	Rational operator / (const Rational& another)
	{
		Rational tmp(numerator*another.denumerator, denumerator*another.numerator);
		return tmp;
	}

	~Rational()
	{
		return;
	}
	
};

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