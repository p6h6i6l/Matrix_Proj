using namespace std;
template <typename T>
class Matrix
{
public: 
size_t length; 
size_t wight;
std::vector< std::vector <T> > Head;

	Matrix()
	{
		length = 1;
		wight = 1;
		T tmp = T(0);
		std::vector<T> a;
		a.push_back(tmp);
		Head.push_back(a);
	}


	Matrix(size_t wight_, size_t length_)
	{
		std::random_device r;
 		std::default_random_engine e1(r());
		std::uniform_int_distribution<int> uniform_dist(0, 5);

		length = length_;
		wight = wight_;
		std::vector<T> str;
		for (size_t i =0; i < wight; i++)
		{	
			for(size_t k = 0; k < length; k++)
			{	
				str.push_back(T(uniform_dist(e1), uniform_dist(e1)));
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


	Matrix operator - (const Matrix& another) const
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
				tmp_str.push_back(Head[i][j] - another.Head[i][j]);
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


	Matrix& SwapLines (size_t first, size_t second)
	{
		std::vector<T>tmp;
		tmp = Head[first];
		Head[first] = Head[second];
		Head[second] = tmp;
		return *this;
	}


	Matrix& SwapColumns (size_t first, size_t second)
	{
		for (int i = 0; i < wight; i++)
		{
			std::swap(Head[i][first-1],Head[i][second-1]);
		}
		return *this;
	}


	Matrix& SumFirstToSecond (size_t first, size_t second)
	{
		for (int i = 0; i < wight; i++)
		{
			Head[second][i] = Head[second][i] + Head[first][i];
		}
		return *this;
	}


	Matrix& MultiplyByConstant (T constant, size_t line)
	{
		for (int i = 0; i < length; i++)
		{
			Head[line][i] = constant * Head[line][i];
		}
		return *this;
	}


	Matrix& SunMultipledFirstToSecond(size_t first, size_t second, T constant)
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
					sum = sum + Head[0][i]*((Submatrix(1, i+1)).Det());
				}else{
					sum = sum -Head[0][i]*((Submatrix(1, i+1)).Det());
				}
			}
			return sum;
		}
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
					SwapLines(a,j);
					b.SwapLines(a,j);
					b.MultiplyByConstant(T(1)/(Head[a][i]), a);
					MultiplyByConstant(T(1)/(Head[a][i]), a);
					for(size_t k = a+1; k < wight; k++)
					{
						b.SunMultipledFirstToSecond(a,k, T(-1)*Head[k][i]);
						SunMultipledFirstToSecond(a,k, T(-1)*Head[k][i]);
						std::cout << *this;
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
					if(std::abs(Head[i][j]) > epsilon )
					{
						for (size_t k = i-1; k+1 >0; k--)
						{
							b.SunMultipledFirstToSecond(i,k, T(-1)*Head[k][j]);
							SunMultipledFirstToSecond(i,k, T(-1)*Head[k][j]);
							std::cout<<*this;
						}
						break;
					}
				}
			}
			//sort_columns(b);
		return *this;
	}


	Matrix& GaussMethod(Matrix &b){
		//Приведение к почти верхнетреугольному виду
		ToUpTringled(b);

		//Перестановка столбцов:
		int count = 0;
		int swap_column = 1;
		std::vector<std::vector<size_t>> swap;
		while (count < wight)
		{
			if (std::abs(Head[count][count])<epsilon and (count + swap_column)<length )
			{
				SwapColumns(count+1, count + swap_column+1);
				std::vector<size_t> transposition;
				transposition.push_back(count);
				transposition.push_back(count + swap_column);
				swap.push_back(transposition);
				std::cout<<"Swapped column " << count << "and column " << count + swap_column <<std::endl;
				swap_column+=1;
				transposition.clear();
			}else{
				count++;
				swap_column = 1;
			}
		}
		//Приведение к единичному виду
		ToLed(b);

		//Выписываем ФСР 
		std::cout<<"FSS: " << std::endl;
		size_t t = 0;
		std::vector<std::vector<T>> FSS;
		while(t<wight and std::abs(Head[t][t]) > epsilon)	{t++;} 
		for (size_t i = 0; i<length; i++)
		{
			std::vector<T> FSS_str;
			if(i<t){
				for(size_t j = t; j < length; j++)
				{
					FSS_str.push_back(T(-1)*Head[i][j]);
				}
			}else{
				for(size_t j = t; j < length; j++)
				{
					FSS_str.push_back(T((i==j)));
				}
			}
			FSS.push_back(FSS_str);
		}
		Matrix FSS_matrix = Matrix(length, length-t, FSS);
		std::cout<< FSS_matrix;
		for (size_t i = 0; i<swap.size(); i++)
		{
			std::cout << "good1"<<std::endl;
			FSS_matrix.SwapLines(swap[i][0], swap[i][1]);
			std::cout << "good2"<<std::endl;
		}

		std::cout<< FSS_matrix;
		std::cout<<"FSS all:" << std::endl;

		//Проверка на совместность СЛУ и вывод частного решения
		std::cout<< "Partial solution: " << std::endl;
		t = 0;
		size_t flag = 0;
		while(t < wight and std::abs(Head[t][t]) > epsilon){t++;}
		for (size_t i = t; t<wight; t++){
			if (abs(b.Head[t][0])>epsilon){
				std::cout<< "System can't be solved :(" << std::endl;
				flag = 1;
				t = wight;
			}
		}
		if (flag == 0){
			std::vector<std::vector<T>> new_b_Head;
			for (size_t j = 0; j<length; j++)
			{
				if(j<t){
					(new_b_Head).push_back({b.Head[j][0]});
				}else{
					(new_b_Head).push_back({0});
				}
			}
			std::cout<< Matrix(length, 1, new_b_Head);
		}
		return *this;
	}


	std::vector<Matrix<T>> ToJordanForm()
	{
		Matrix<Polynom> q = ToCharPolynom(*this);
	}


	~Matrix(){}
	

};


template <typename T>
Matrix<Polynom> ToCharPolynom( const Matrix<T>& b){
		std::vector< std::vector< Polynom > > Head_polynom;
		for (size_t i = 0; i<b.wight; i++)
		{
			std::vector<Polynom> polynom_str;
			for (size_t j = 0; j<b.length; j++)
			{
				if (i==j)
				{
					std::vector<std::complex<double>> elem = {b.Head[i][j], -1};
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

template <typename T>
std::ostream& operator<<(std::ostream &os, const Matrix<T>& M)
{
	for(size_t i = 0; i < M.wight; ++i)
	{
		for(size_t j = 0; j < M.length; ++j)
		{
			os<< M.Head[i][j] << "     ";
		}
		os<<std::endl;
	}
	os<<std::endl;
	return os;
}