
template <typename T>
class Matrix
{
public: 
size_t length; 
size_t wight;
std::vector< std::vector <T> > Head;

	Matrix()
	{
		length = 0;
		wight = 0;
		std::vector< std::vector<T> > Head;
	}

	Matrix(size_t wight_, size_t length_)
	{
		std::random_device r;
 		std::default_random_engine e1(r());
		std::uniform_int_distribution<int> uniform_dist(0, 100);

		length = length_;
		wight = wight_;
		std::vector<T> str;
		for (size_t i =0; i < wight; i++)
		{	
			for(size_t k = 0; k < length; k++)
			{	
				str.push_back(uniform_dist(e1));
			}
			Head.push_back(str);
			str.clear();
		}
	}

	Matrix(size_t wight_, size_t length_, std::vector< std::vector<T> > pool)
	{
		length = length_;
		wight = wight_;
		Head = pool;
	}


	Matrix(const Matrix &another)
	{
		length = another.length;
		wight = another.wight;
		std::vector< std::vector<T> > Head;
		for (size_t i = 0; i < wight; i++)
		{
			for (size_t j = 0; j < length; j++)
			{
				Head[i][j] = another.Head[i][j];
			}
		}
	}


	Matrix& operator = (const Matrix& another)
	{
		if (&another == this)
			return *this;
		Matrix t(another);
		std::swap(wight, t.wight);
		std::swap(length, t.length);
		std::swap(Head, t.Head);
		return *this;
	}

	Matrix operator + (const Matrix& another) const
	{
		if(wight != another.wight || length != another.length){
			std::cout<< "Matrix has different sizes. Can't sum." << std::endl;
			return *this;
		}
		std::vector<std::vector<T>> tmp;
		for (size_t i = 0; i < wight; i++)
		{	
			std::vector<T> tmp_str;
			for (size_t j = 0; j < length; j++)
			{
				tmp_str.push_back(Head[i][j] + another.Head[i][j]);
			}
			tmp.push_back(tmp_str);
		}	
		return Matrix(wight, length, tmp);
	}

	Matrix operator * (const Matrix& another) const
	{
		if(length != another.wight){
			std::cout<< "Matrix has different sizes. Can't multiply." << std::endl;
			return *this;
		}
		std::vector<std::vector<T>> tmp;
		for (size_t i = 0; i < wight; i++)
		{	
			std::vector<T> tmp_str;
			for (size_t j = 0; j < length; j++)
			{
				T sum = 0;
				for (size_t k = 0; k<length; k++){
					sum += Head[i][k] * another.Head[k][j];
				}
				tmp_str.push_back(sum);
			}
			tmp.push_back(tmp_str);
		}	
		return Matrix(wight, another.length, tmp);
	}


	Matrix(Matrix&& obj)
	{
		Head = obj.Head;
		length = obj.length;
		wight = obj.wight;
		(obj.Head).clear();
	} 


	Matrix& operator= (Matrix&& obj)
	{
		Matrix t(std::move(obj));
		std::swap(wight, t.wight);
		std::swap(length, t.length);
		std::swap(Head, t.Head);
		return *this;
	}


	Matrix& swap_lines (size_t first, size_t second)
	{
		std::vector<T>tmp;
		tmp = Head[first];
		Head[first] = Head[second];
		Head[second] = tmp;
		return *this;
	}


	Matrix& swap_columns (size_t first, size_t second)
	{
		for (int i = 0; i < length; i++)
		{
			std::swap(Head[i][first],Head[i][second]);
		}
		return *this;
	}


	Matrix& sum_first_to_second (size_t first, size_t second)
	{
		for (int i = 0; i < wight; i++)
		{
			Head[second][i] = Head[second][i] + Head[first][i];
		}
		return *this;
	}


	Matrix& multiply_by_constant (T constant, size_t line)
	{
		for (int i = 0; i < length; i++)
		{
			Head[line][i] = constant * Head[line][i];
		}
		return *this;
	}


	Matrix& sum_multiplied_first_to_second(size_t first, size_t second, T constant)
	{
		T t[length];
		for (int i = 0 ; i < length; i++)
		{
			t[i] = constant*Head[first][i];
			Head[second][i] = t[i] + Head[second][i];
		}
		return *this;
	}

	Matrix Submatrix(size_t line, size_t column)
	{
		std::vector< std::vector<T> > Head_minor = Head;
		auto begin = Head_minor.cbegin();
		Head_minor.erase(begin + line - 1);
		for (size_t i = 0; i<length-1; i++)
		{
			auto begin1 = Head_minor[i].cbegin();
			Head_minor[i].erase(begin1 + column - 1);
		}
		return Matrix(wight-1, length-1, Head_minor);
	}

	T Det()
	{
		//Защита от дурачка
		if (wight != length){
			std::cout << "This matrix doesn't have determinant" << std::endl;
			std::exit(0);
		}
		if (wight == 2){
			return Head[0][0]*Head[1][1] - Head[1][0]*Head[0][1];
		}else{
			T sum;
			for (size_t i= 0; i < length; i++){
				if ((i+2)%2 == 0){
					sum += Head[0][i]*((Submatrix(1, i+1)).Det());
				}else{
					sum += -Head[0][i]*((Submatrix(1, i+1)).Det());
				}
			}
			return sum;
		}
	}

	void out_matrix()
	{
		for(size_t i = 0; i < wight; i++)
		{
			for( size_t j = 0 ; j < length; j++)
			{
				std::cout<< Head[i][j] << "      ";
			}
			std::cout << std::endl;
		}
		std::cout<<std::endl;
		return;
	}


	Matrix& ToUpTringled(Matrix& b)
	{
		size_t a = 0;
		for(size_t i = 0; i < length; i++)
		{
			for(int j = 0 ; j < wight; j++)
			{
				if(std::abs(Head[j][i]) > epsilon and j >=a)
				{
					swap_lines(a,j);
					b.swap_lines(a,j);
					b.multiply_by_constant(T(1)/(Head[a][i]), a);
					multiply_by_constant(T(1)/(Head[a][i]), a);
					for(size_t k = a+1; k < wight; k++)
					{
						b.sum_multiplied_first_to_second(a,k, -Head[k][i]);
						sum_multiplied_first_to_second(a,k, -Head[k][i]);
						out_matrix();
					}
					a++;
					break;
				}
			}
		}
		return *this;
	}


	Matrix& ToLed(Matrix &b)
	{
		for(size_t i = wight - 1; i+1 > 0; i--)
			{
				for (size_t j = 0; j < length; j++)
				{
					if(std::abs(Head[i][j] > epsilon ))
					{
						for (size_t k = i-1; k+1 >0; k--)
						{
							b.sum_multiplied_first_to_second(i,k, -Head[k][j]);
							sum_multiplied_first_to_second(i,k, -Head[k][j]);
							out_matrix();
						}
						break;
					}
				}
			}
			//sort_columns(b);
		return *this;
	}

	/*Matrix& GaussMethod(Matrix &b){
		ToUpTringled(b);
		ToLed(b);
		int flag = 0;
		for (size_t i = wight-1; i+1>0; i--)
		{
			if ( std::abs(b.Head[i][0]) < epsilon){
				for (size_t j = 0; j < length; j++){
					if (std::abs(Head[i][j]) > epsilon){flag++;}
				}
			}
		}
		if (flag != 0){
			std::cout<<"can't be solved :(";
		}else{
			for  (size_t i =0; i<wight; i++){
				std::cout<< b.Head[i][0] << std::endl;
			}
		}
		return *this;
	}*/

	~Matrix(){}
	

};

template <typename T>
Matrix<Polynom> ToCharPolynom( Matrix<T>& b){
		std::vector< std::vector< Polynom > > Head_polynom;
		for (size_t i = 0; i<b.wight; i++)
		{
			std::vector<Polynom> polynom_str;
			for (size_t j = 0; j<b.length; j++)
			{
				if (i==j)
				{
					std::vector<std::complex<T>> elem = {b.Head[i][j], -1};
					polynom_str.push_back(Polynom(elem));
				}else
				{
				polynom_str.push_back(Polynom(b.Head[i][j]));
				}
			}
			Head_polynom.push_back(polynom_str);
		}
		return Matrix<Polynom>(b.wight, b.length, Head_polynom);
	}