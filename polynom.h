
class Polynom
{
public:
	std::vector<std::complex<double>> coefs;
	size_t degree;
	Polynom(){}


	Polynom(std::complex<double> a)
	{
		degree = 1;
		coefs.push_back(a);
	}
	Polynom(std::vector<std::complex<double>>& coefs_, size_t degree_)
	{
		coefs = coefs_;
		degree = degree_;
	}


	Polynom(std::vector<std::complex<double>>& coefs_)
	{
		coefs = coefs_;
		degree = coefs_.size();
	}


	Polynom operator + (const Polynom& another)
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

		while(tmp[tmp.size()-1] == ComplexZero && tmp.size() != 0)
		{
			auto q = tmp.end();
			tmp.erase(q-1);
		}

		Polynom q(tmp);
		return q;
	}

	Polynom operator * (const Polynom& another)
	{
		std::complex<double> sum(0,0);
		std::vector<std::complex<double>> tmp;
		for(size_t j = 0; j < degree + another.degree; ++j)
		{
			for(size_t k = 0 ; k < j; ++k)
			{

			}
			tmp.push_back()
		}
	}

	~Polynom()
	{

	}


	void out()
	{
		for(size_t j = 0; j < degree; ++j)
		{
			std::cout << coefs[j] << " ";
		}
		std::cout<<std::endl;
	}
};
