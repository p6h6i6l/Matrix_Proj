#include "polynom.h"	
	Polynom::Polynom()
	{
		degree = 0;
		coefs.push_back(ComplexZero);
	}

	Polynom::Polynom(std::complex<double> a)
	{
		degree = 0;
		coefs.push_back(a);
	}

	Polynom::Polynom(long long a)
	{
		degree = 0;
		coefs.push_back(std::complex<double>(a,0));
	}

	Polynom::Polynom(std::vector<std::complex<double>>& coefs_, size_t degree_)
	{
		coefs = coefs_;
		degree = degree_;
	}


	Polynom::Polynom(std::vector<std::complex<double>>& coefs_)
	{
		coefs = coefs_;
		degree = coefs_.size()-1;
	}


	Polynom Polynom:: operator + (const Polynom& another) const
	{
		std::vector<std::complex<double>>tmp;
		size_t j = std::min(coefs.size(), another.coefs.size());
		for(size_t k = 0; k < j; ++k)
		{
			tmp.push_back(coefs[k] + another.coefs[k]);
		}
		if(j == coefs.size())
		{
			for(size_t k = j; k < another.coefs.size(); ++k )
				tmp.push_back(another.coefs[k]);
		}
		else
		{
			for(size_t k = j; k < coefs.size(); ++k )
				tmp.push_back(coefs[k]);
		}
		ZeroCheck(tmp[tmp.size()-1]);
		while(tmp[tmp.size()-1] == ComplexZero && tmp.size() != 0)
		{
			auto q = tmp.end();
			tmp.erase(q-1);
		}
		if(tmp.size() == 0 )
		{
			Polynom q(ComplexZero);
			return q;
		}
		Polynom q(tmp);
		return q;
	}



	Polynom Polynom:: operator * (const Polynom& another)
	{
		std::complex<double> sum = ComplexZero;
		std::vector<std::complex<double>> tmp;
		for(size_t j = 0; j < degree + another.degree+1; ++j)
		{
			for(size_t k = 0 ; k < j+1; ++k)
			{
				if(k > coefs.size()-1 || j-k > another.coefs.size()-1)
					continue;
				sum = sum + coefs[k]*another.coefs[j-k];
				ZeroCheck(sum);
			}
			tmp.push_back(sum);
			sum = ComplexZero;
		}
		return tmp;
	}

		
	Polynom Polynom:: operator - (const Polynom& another)
	{
		return (*this + Polynom(-1)*another);
	}

	Polynom Polynom:: operator / (const Polynom& another){
		std::vector<Polynom> tmp = DivideTwoPolynom(*this, another);

		return tmp[0];
	}


	std::complex<double> Polynom:: DerivativeInPoint(std::complex<double> point)
	{
		if(degree == 0)
			return ComplexZero;
		std::complex<double> der = ComplexZero;

		for(size_t i = 1; i < degree +1; ++i)
		{
			der += (coefs[i]*std::complex<double>(i,0))*std::pow(point, i-1);
		}
		return der;
	}

	std::complex<double> Polynom::ValueInPoint( std::complex<double> point)
	{
		if(point == ComplexZero)
			return coefs[0];
		std::complex<double> val = ComplexZero;
		for(size_t i = 0; i < degree+1 ; ++i)
		{
			val += coefs[i] * std::pow(point,i);
		}
		return val;
	}

	std::vector<std::complex<double>> Polynom:: FindRoots()
	{
		long long q = 0;
		std::vector<std::complex<double>> roots;
		std::complex<double> temp;
		std::complex<double> helping_sum2(0,0);
		if(degree == 0)
			return roots;
		double helping_sum = 0;
		double  root_border = 0;
		for(int i = 0; i < degree; ++i)
		{
			helping_sum+= abs(coefs[i]/coefs[degree]);

		}
		if(helping_sum > 1)
			root_border = helping_sum;
		else
			root_border = 1;

		for(size_t i = 0 ; i < degree; ++i)
		{
			temp = std::complex<double>(root_border*cos(2*pi/(i+1))
				+distribution_roots_epsilon, 
				root_border*sin(2*pi/(i+1)) - distribution_roots_epsilon);
			roots.push_back(temp);
		}

		while(!CheckArrayLikeARoots(roots))
		{
			if(q <= number_of_steps*std::pow(degree, 3))
			{
				++q;
				for(size_t i = 0; i < roots.size(); ++i)
				{
					if(CheckNumberLikeARoot(roots[i]))
					{
						continue;
					}

					for(size_t k = 0; k < roots.size(); ++k)
					{
						if( k == i)
							continue;
						helping_sum2 += std::complex<double>(1,0)/(roots[i]-roots[k]);
					}
					roots[i] = roots[i] -  ((this->ValueInPoint(roots[i])/this->DerivativeInPoint(roots[i]))/
					(std::complex<double>(1,0)
						- (this->ValueInPoint(roots[i]) / this->DerivativeInPoint( roots[i]))*helping_sum2));
					helping_sum2 = ComplexZero;

				}
			}
			else
			{
				std::cerr<<"Process of finding roots was breaked because number of iterations is more than "
				<< number_of_steps*std::pow(degree,2) << std::endl;
				break;
			}
		}
		for(size_t i = 0; i < roots.size(); ++i)
		{
			ZeroCheck(roots[i]);
		}
		return roots;

	}

	bool Polynom:: CheckNumberLikeARoot(std::complex<double> root)
	{
		std::complex<double> tmp = this->ValueInPoint(root);
		if(std::abs(tmp) < checking_roots_epsilon)
				return true;
		return false;
	}

	bool Polynom:: CheckArrayLikeARoots(const std::vector<std::complex<double>>& roots)
	{
		for(size_t i = 0; i < roots.size(); ++i)
		{
			if(!CheckNumberLikeARoot(roots[i]))
				return false;
		}
		return true;
	}

	Polynom Polynom:: DivideToRoot(std::complex<double> root)
	{
		if(degree == 0)
			return *this;
		std::vector<std::complex<double>> answer_coefs;
		answer_coefs.insert(answer_coefs.begin(),coefs[degree]);
		for(size_t i = 1; i < degree; ++i)
		{
			answer_coefs.insert(answer_coefs.begin(),root * answer_coefs[0] + coefs[degree-i]);
		}
		return Polynom(answer_coefs);
	}


	Polynom:: ~Polynom()
	{

	}

std::vector<Polynom> DivideTwoPolynom(const Polynom& divisible,const Polynom& divisor)
	{
		int q = 0;
		std::vector<std::complex<double>> partial;
		std::vector<Polynom> answer;
		Polynom temp;
		Polynom f_1 = divisible;
		std::vector<std::complex<double>> temp_coefs;
		while(f_1.degree >= divisor.degree){
			for (size_t i = 0; i < f_1.degree - divisor.degree; i++){
				temp_coefs.push_back(ComplexZero);
			}
			temp_coefs.push_back(std::complex<double>(-1,0)*f_1.coefs[f_1.degree]/divisor.coefs[divisor.degree]);
			Polynom temp(temp_coefs);
			f_1 = f_1 + temp*divisor;
			partial.push_back(temp.coefs[temp.degree]);
			++q;
			temp_coefs.clear();
		}
		std::reverse(partial.begin(), partial.end());
		Polynom Partial(partial);
		Polynom r = divisible + (Partial * divisor);
		answer.push_back(Polynom(std::complex<double>(-1,0))*Partial);
		answer.push_back(r);
		return answer;
	}

void ZeroCheck(std::complex<double> &number)
{
	if(abs(number.real()) < epsilon)
		number = std::complex<double>(round(number.real()), number.imag());
	if(abs(number.imag()) < epsilon)
		number = std::complex<double>(number.real(), 0);
	return;
}


std::ostream& operator<<(std::ostream &os, const Polynom& r)
{
	for(int i = 0; i < r.degree+1; ++i)
	{
		if(i != r.degree)
		{
			os<< "(" << real(r.coefs[i]) << "+" << imag(r.coefs[i]) 
			<< "i)x^"<< i << " + ";
		}
		else
		{
			os<< "(" << real(r.coefs[i]) << "+" << imag(r.coefs[i]) 
			<< "i)x^"<< i;
		}
	}
	os<<std::endl;
	return os;
}


std::vector<std::vector<std::complex<double>>> multiplicity(const std::vector<std::complex<double>>& roots)
{
	std::vector<std::complex<double>> roots_copy = roots;
	std::vector<std::vector<std::complex<double>>> mult;
	for (size_t i = 0; i<roots_copy.size(); i++)
	{
		size_t count = 1;
		std::vector<std::complex<double>> str = {roots_copy[i], std::complex<double>(count)};
		for (size_t j = i+1; j-count+1<roots_copy.size(); j++)
		{ 
			if (std::abs(roots_copy[i] - roots_copy[j-count+1])<0.2)
			{
				auto begin = roots_copy.cbegin();
				roots_copy.erase(begin+j-count+1);
				count+=1;
				str[1] +=1;
			}
		}
		mult.push_back(str);
		str.clear();
	}
	return mult;
}


