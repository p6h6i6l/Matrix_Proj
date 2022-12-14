
class Polynom;	
void ZeroCheck(std::complex<double> &number);
std::complex<double> ValueInPoint(Polynom & pol, std::complex<double> point);
std::complex<double> DerivativeInPoint(Polynom & pol, std::complex<double> point);
template <typename T>
void out_vector(std::vector<T>& vect);

class Polynom
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
	Polynom()
	{
		degree = 0;
		coefs.push_back(ComplexZero);
	}

	Polynom(std::complex<double> a)
	{
		degree = 0;
		coefs.push_back(a);
	}

	Polynom(long long a)
	{
		degree = 0;
		coefs.push_back(std::complex<double>(a,0));
	}

	Polynom(std::vector<std::complex<double>>& coefs_, size_t degree_)
	{
		coefs = coefs_;
		degree = degree_;
	}


	Polynom(std::vector<std::complex<double>>& coefs_)
	{
		coefs = coefs_;
		degree = coefs_.size()-1;
	}


	Polynom operator + (const Polynom& another) const
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



	Polynom operator * (const Polynom& another)
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

		
	Polynom operator - (const Polynom& another)
	{
		return (*this + Polynom(-1)*another);
	}

	Polynom operator / (const Polynom& another){
		std::vector<Polynom> tmp = DivideTwoPolynom(*this, another);

		return tmp[0];
	}


	std::complex<double> DerivativeInPoint(std::complex<double> point)
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

	std::complex<double> ValueInPoint( std::complex<double> point)
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

	std::vector<std::complex<double>> FindRoots()
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
						//std::cout<< helping_sum2 << "<---- this is helping_sum2"<<std::endl;
					}

					//out_vector<std::complex<double>>(roots);
					//std::cout << q << std::endl;

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
		std::cout<< "This is number of iterations ---->" << q << std::endl;
		return roots;

	}

	/*std::complex<double> FindMaxRoot(std::vector<std::complex<double>>& roots)
	{
		size_t max_index = 0;
		for(int i = 0; i < roots.size(); ++i)
		{
			if (std::abs(roots[i]) > std::abs(roots[max_index]))
				max_index = i;
		}
		return roots[max_index];
	}*/

	bool CheckNumberLikeARoot(std::complex<double> root)
	{
		std::complex<double> tmp = this->ValueInPoint(root);
		if(std::abs(tmp) < checking_roots_epsilon)
				return true;
		return false;
	}

	bool CheckArrayLikeARoots(const std::vector<std::complex<double>>& roots)
	{
		for(size_t i = 0; i < roots.size(); ++i)
		{
			if(!CheckNumberLikeARoot(roots[i]))
				return false;
		}
		return true;
	}

	Polynom DivideToRoot(std::complex<double> root)
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


	~Polynom()
	{

	}

	void out()
	{
		for(size_t j = 0; j < degree+1; ++j)
		{
			std::cout << coefs[j] << " ";
		}
		std::cout<<std::endl;
	}
};

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
	if(std::abs(number.real()) < epsilon)
		number = std::complex<double>(0, number.imag());
	if(std::abs(number.imag()) < epsilon)
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

template <typename T>
void out_vector(std::vector<T>& vect)
{
	for(size_t i = 0 ; i < vect.size(); ++i)
		std::cout<< vect[i]<<std::endl;
	std::cout<< std::endl;
	return;
}


