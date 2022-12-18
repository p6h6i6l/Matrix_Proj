
template <typename T>
class Matrix final 
{
private:
	size_t length; 
	size_t wight;
	std::vector< std::vector <T> > Head;
template <typename Q>
friend 
Matrix<Polynom> ToCharPolynom( const Matrix<Q>& b);
template <typename V>
friend
std::ostream& operator<<(std::ostream &os, const Matrix<V>& M);

public:

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
		std::uniform_int_distribution<int> uniform_dist(0, 7);

		length = length_;
		wight = wight_;
		std::vector<T> str;
		for (size_t i =0; i < wight; i++)
		{	
			for(size_t k = 0; k < length; k++)
			{	
				str.push_back(T(uniform_dist(e1)));
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

	Matrix(size_t wight_, size_t length_, T i)
	{
		length = length_;
		wight = wight_;
		std::vector<std::vector<T>> b;
		for(size_t k = 0; k<wight; k++)
		{	
			std::vector<T> b_str;
			for (size_t m = 0; m<wight; m++)
			{
				if (m==k){
					b_str.push_back(i);
				}else{
					b_str.push_back(i);
				}
			}
			b.push_back(b_str);
		}
	}


	Matrix(const Matrix<T> &another)
	{
		length = another.length;
		wight = another.wight;
		for (size_t i = 0; i < wight; i++)
		{
			std::vector<T> Head_str;
			for (size_t j = 0; j < length; j++)
			{
				Head_str.push_back(another.Head[i][j]);
			}
			Head.push_back(Head_str);
			Head_str.clear();
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
		try
		{
			if(wight != another.wight || length != another.length){
				std::cout<< "Matrix has different sizes. Can't sum." << std::endl;
				throw 2;
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
		catch(int a)
		{
			std::cerr <<"Wrong size. Error code 2" << std::endl;
		}
	}


	Matrix operator - (const Matrix& another) const
	{
		try
		{
			if(wight != another.wight || length != another.length){
				throw 2;
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
		catch(int a)
		{
			std::cerr <<"Wrong size. Error code 2" << std::endl;
		}
	}


	Matrix operator * (const Matrix& another) const
	{
		try
		{
			if(length != another.wight)
				throw 2;
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
		catch(int a)
		{
			std::cerr <<"Wrong size. Error code 2" << std::endl;
		}
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

	Matrix& ChangeColumns (Matrix& column, size_t n)
	{
		if (wight != column.wight or n> length)
		{
			std::cout<<"Column size wrong. Can't push back.";
			return *this;
		}
		for (size_t i = 0; i<wight; i++)
		{
			for (size_t j = 0; j<column.length; j++)
			{
				Head[i][j+n-1] = column.Head[i][j];
			}
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
		try{
		//Защита от дурачка
		if (wight != length){
			throw 0;
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
		catch(int a)
		{
			std::cerr<<"NOT SQUARED MATRIX. ERROR CODE 1"<<std::endl;
		}
		return T(0);
	}

	Matrix Column(size_t n)
	{
		Matrix<T> column(wight, 1);
		for(size_t i = 0; i<wight; i++)
		{
			column.Head[i][0] = Head[i][n];
		}
		return column;
	}

	bool CheckLineToZero (const Matrix& matrix, size_t n)
	{
		for (size_t i = 0; i<length; i++)
		{
			if (abs(Head[n][i])>gauss_epsilon ){return false;}
		}
		return true;

	}

	bool CheckToZero ()
	{
		for (size_t i = 0; i<wight; i++)
		{
			if(!CheckLineToZero(*this, i)){return false;}
		}
		return true;
	}

	Matrix& ZeroLinesSwap(Matrix& b)
	{
		size_t swap = wight-1;
		for (size_t i = 0; i<wight; i++)
		{
			if (CheckLineToZero(*this, i))
			{
				while (CheckLineToZero(*this, swap) and swap > i)
				{
					swap-=1;
				}
				SwapLines(i, swap);
				b.SwapLines(i, swap);
			}
		}
		return *this;
	}

	bool CheckColumnToZero(const Matrix& matrix, size_t n){
		for (size_t i = 0; i<length; i++)
		{
			if (abs(Head[i][n])>gauss_epsilon ){return false;}
		}
		return true;
	}

	Matrix& RemoveZeroColumns()
	{
		for (size_t i = 0; i<length; i++)
		{
			if (CheckColumnToZero(*this, i))
			{
				length-=1;
				for (size_t j = 0; j<wight; j++)
				{
					auto begin = Head[j].cbegin();
					Head[j].erase(begin + i);
				}
			}
		}
	}

	Matrix& ToUpTringled(Matrix& b)
	{
		size_t a = 0;
		for(size_t i = 0; i < length; i++)
		{
			for(int j = 0 ; j < wight; j++)
			{
				if(	abs(Head[j][i]) > gauss_epsilon and j >=a)
				{
					//std::cout << "come " <<i << j << std::endl<< *this;
					SwapLines(a,j);
					b.SwapLines(a,j);
					b.MultiplyByConstant(T(1)/(Head[a][i]), a);
					MultiplyByConstant(T(1)/(Head[a][i]), a);
					for(size_t k = a+1; k < wight; k++)
					{
						b.SunMultipledFirstToSecond(a,k, T(-1)*Head[k][i]);
						SunMultipledFirstToSecond(a,k, T(-1)*Head[k][i]);
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
					if(abs(Head[i][j]) > gauss_epsilon )
					{
						for (size_t k = i-1; k+1 >0; k--)
						{
							b.SunMultipledFirstToSecond(i,k, T(-1)*Head[k][j]);
							SunMultipledFirstToSecond(i,k, T(-1)*Head[k][j]);
							//std::cout<<*this;
						}
						break;
					}
				}
			}
			//sort_columns(b);
		return *this;
	}

	Matrix& GaussMethod(Matrix &b)
	{
		try
		{
			if((*this).CheckToZero())
			{
				*this = Matrix<T>(wight, length, T(1));
				return *this;
			}
			ZeroLinesSwap(b);
			//std::cout<<*this;
			Matrix<T> a_copy = *this;
			if(wight != b.wight)
				throw 2;
			ToUpTringled(b);
			//std::cout<<"after to up tringled"<< std::endl << *this;

			//Перестановка столбцов:
			int count = 0;
			int swap_column = 1;
			std::vector<std::vector<size_t>> swap;
			while (count < wight)
			{
				//std::cout<<"transposition"<< count<< std::endl;
				if (abs(Head[count][count]) < gauss_epsilon and (count + swap_column)<length )
				{
					SwapColumns(count+1, count + swap_column+1);
					std::vector<size_t> transposition;
					transposition.push_back(count);
					transposition.push_back(count + swap_column);
					swap.push_back(transposition);
					//std::cout<<"Swapped column " << count << "and column " << count + swap_column <<std::endl;
					swap_column+=1;
					transposition.clear();
					//std::cout<<"transposition"<< std::endl << *this;
				}
				else
				{
					count++;
					swap_column = 1;
				}
			}
			//std::cout<<*this;
			//Приведение к единичному виду
			ToLed(b);
			//std::cout<<"after to led"<< std::endl << *this;

			//Выписываем ФСР 
			std::cout<<"FSS: " << std::endl;
			size_t t = 0;
			std::vector<std::vector<T>> FSS;
			while(t<wight and abs(Head[t][t]) > gauss_epsilon)	{t++;} 
			for (size_t i = 0; i<length; i++)
			{
				std::vector<T> FSS_str;
				if(i<t)
				{
					for(size_t j = t; j < length; j++)
					{
						FSS_str.push_back(T(-1)*Head[i][j]);
					}
				}
				else
				{
					for(size_t j = t; j < length; j++)
					{
						FSS_str.push_back(T((i==j)));
					}
				}
				FSS.push_back(FSS_str);
			}
			Matrix FSS_matrix = Matrix(length, length-t, FSS);
			for (size_t i = 0; i<swap.size(); i++)
			{
				FSS_matrix.SwapLines(swap[i][0], swap[i][1]);
			}
			std::cout<< FSS_matrix;
			std::cout<<"FSS all:" << std::endl;
			//Проверка на совместность СЛУ и вывод частного решения
			std::cout<< "Partial solution: " << std::endl;
			t = 0;
			size_t flag = 0;
			while(t < wight and std::abs(Head[t][t]) > gauss_epsilon){t++;}
			for (size_t i = t; t<wight; t++)
			{
				if (abs(b.Head[t][0])> gauss_epsilon)
				{
					std::cout<< "System can't be solved :(" << std::endl;
					flag = 1;
					t = wight;
				}
			}
			if (flag == 0)
			{
				std::vector<std::vector<T>> new_b_Head;
				for (size_t j = 0; j<length; j++)
				{
					if(j<t)
					{
						(new_b_Head).push_back({b.Head[j][0]});
					}else{
						(new_b_Head).push_back({0});
					}
				}
				std::cout<< Matrix(length, 1, new_b_Head);
			}
			*this = FSS_matrix;
			return *this;
		}
		catch (int  a)
		{
			std::cerr <<"Wrong size. Error code 2" << std::endl;
		}

		return *this;
	}


	void ToJordanForm()
	{
		Matrix<T> copy(*this);
		Matrix<std::complex<double>> S(wight, wight);
		Matrix<std::complex<double>> JNF(wight, wight);
		Matrix<T> b(wight, wight);
		for(size_t k = 0; k<wight; k++)
		{	
			for (size_t m = 0; m<wight; m++)
			{
				if (m==k){
					JNF.Head[k][m] = 1;
					b.Head[k][m]= 1;
				}else{
					JNF.Head[k][m] = 0;
					b.Head[k][m]= 0;
				}
			}
		}
		std::cout<<b;

		//Находим характеристический многочлен
		Matrix<Polynom> q = ToCharPolynom(*this);
		Polynom char_polynom = q.Det();
		std::cout<< char_polynom;
		std::vector<std::complex<double>> roots = char_polynom.FindRoots();
		std::cout<< "ROOTS" << std::endl << roots;
		std::vector<std::vector<std::complex<double>>> mult = multiplicity(roots);
		for (size_t i = 0; i<mult.size(); i++){
			out_vector<std::complex<double>>(mult[i]);
		}

		//Считаем собственные векторы 
		size_t basis = 0;
		for (size_t i = 0; i < mult.size(); i++)
		{
			Matrix<T> copy_i = copy;
			for(size_t k = 0; k<wight; k++){copy_i.Head[k][k]-=mult[i][0];}
			std::cout<<"Gauss Method" << std::endl;
			Matrix<std::complex<double>> FSS_i = copy_i.GaussMethod(b);

			//Ищем присоединенные векторы, если это нужно
			if (FSS_i.length < abs(mult[i][1]))
			{
				std::cout<<"TOOOOOOOOO "<<i<<std::endl;
				Matrix<std::complex<double>> pool = b*FSS_i;
				std::cout<< "POOL" <<pool;
				Matrix<std::complex<double>> add_vectors(FSS_i.length, FSS_i.length);

				for (size_t j = 0; j < FSS_i.length; j++)
				{
					for (size_t k = 0; k < FSS_i.length; k++)
					{
						add_vectors.Head[j][k] = pool.Head[wight-FSS_i.length+j][k];
					} 	
				}
				std::cout<<add_vectors;

				Matrix<std::complex<double>>  Linear_coombinations = FSS_i*add_vectors;
				std::vector<Matrix<T>> solutions;

				std::cout<< "LINEAR COOMBINATIONS"<<Linear_coombinations;
				for (size_t l = 0; l<Linear_coombinations.length; l++)
				{
					if((Linear_coombinations.Column(l)).CheckToZero())
					{
						solutions.push_back(FSS_i.Column(l));
					}else{
						solutions.push_back(Linear_coombinations.Column(l));
					}
				}
				Linear_coombinations.RemoveZeroColumns();
				//std::cout<< "LINEAR COOMBINATIONS"<<solutions[];

				std::cout<< "BEFORE FOR"<< std::endl <<S ;
				std::cout<< "BEFOR FOR"<< std::endl <<JNF ;
				for (size_t column = 0; column<solutions.size(); column++)
				{

					size_t zero = FSS_i.length;

					S.ChangeColumns(solutions[column], basis + 1);
					JNF.Head[basis][basis] = mult[i][0];
					basis+=1;
					std::cout<< "IN FOR"<< std::endl <<S ;
					std::cout<< "IN FOR"<< std::endl <<JNF ;

					while(zero == FSS_i.length)
					{
						std::cout<< "come to while"<< solutions[column]<< std::endl;
						zero = 0;

						Matrix<T> copy_2 = copy;
						for(size_t k = 0; k<wight; k++){copy_2.Head[k][k]-=mult[i][0];}

						copy_2.GaussMethod(solutions[column]);
						std::cout<< "come to while: after gauss method"<< solutions[column]<< std::endl;
						for (size_t v = 0; v<FSS_i.length; v++)
						{
							std::vector<std::vector<std::complex<double>>> elem = (solutions[column]).Head;
							if (abs(elem[wight-v-1][0])<gauss_epsilon){zero+=1;}
						}
						std::cout<< "check zero "<< zero <<std::endl;

						if (zero == FSS_i.length)
						{
							S.ChangeColumns(solutions[column], basis + 1);
							JNF.Head[basis][basis] = mult[i][0];
							JNF.Head[basis-1][basis] = 1;
							basis+=1;
							std::cout<< "FFFFFFFFFFFFFFFFFFFFFF" << basis << std::endl <<S ;
							std::cout<< "FFFFFFFFFFFFFFFFFFFFFF"<< std::endl <<JNF ;
						}

					}
				}

			}else{
				S.ChangeColumns(FSS_i, basis + 1);
				for (size_t l = 0; l<FSS_i.length; l++)
				{
					JNF.Head[l+basis][l+basis] = mult[i][0];
				}
				basis+=1;
				std::cout<< "FFFFFFFFFFFFFFFFFFFFFF"<<S ;
				std::cout<< "FFFFFFFFFFFFFFFFFFFFFF"<<JNF ;
			}
			std::cout<<"Gauss Method END" << std::endl;
		}
		std::cout<< "MATRIX TO JNF"<< std::endl << S ;
		std::cout<< "JNF"<< std::endl <<JNF ;

	}


	~Matrix(){}
	

};


template <typename T>
Matrix<Polynom> ToCharPolynom( const Matrix<T>& b){
	try
	{
		if(b.length != b.wight)
			throw 1;
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
	catch(int a)
	{
		std::cerr<<"NOT SQUARED MATRIX. ERROR CODE 1, RETURNED EPMTY MATRIX"<<std::endl;
	}
	Matrix<Polynom> q; 
	return q;
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