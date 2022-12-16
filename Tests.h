bool ChecKRootsFunction()
{
	bool returnable;
	std::cout << 1;
	size_t tests_cheked = 0;
	std::vector<std::complex<double>> v;
	std::random_device r1;
 	std::default_random_engine e1(r1());
	std::uniform_int_distribution<int> uniform_dist1(1, 50);
	std::random_device r2;
 	std::default_random_engine e2(r2());
	std::uniform_real_distribution<double> uniform_dist2(1, 10);
	for(size_t j = 0; j < number_of_cheking_roots; ++j)
	{
		//std::cout << 2;
		for (size_t i = 0; i < uniform_dist1(e1); ++i)
		{
			v.push_back(std::complex<double>(uniform_dist2(e2),uniform_dist2(e2)));
			//std::cout << 3;
		}
		//std::cout << 6;
		Polynom q(v);
		//std::cout<< q;
		std::vector<std::complex<double>> tmp = q.FindRoots();
		if(!q.CheckArrayLikeARoots(tmp))
		{
			//std::cout << 4;
			std::cout << "Finding roots breaked at the test " << tests_cheked;
			return false;
		}
		//std::cout << 5;
		++tests_cheked;
		v.clear();
	}
	std::cout << "Checked " << tests_cheked << " tests, everything is OK";
	return true;
}


bool GaussMethodCheck() // Тимур напишет
{
	return true;
}

