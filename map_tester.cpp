#include <fstream>
#include <iostream>

// #ifdef STD
	// #include <map>
	// #include <utility>
// #else
// #endif

	// namespace ft = std;

#include "map.hpp"
#include "utils.hpp"

int	main()
{
	ft::map<std::string, int>	test;

	test.insert(ft::pair<std::string, int>("m", 1));
	test.insert(ft::pair<std::string, int>("f", 2));
	test.insert(ft::pair<std::string, int>("c", 4));
	test.insert(ft::pair<std::string, int>("d", 4));
	test.insert(ft::pair<std::string, int>("e", 4));
	test.insert(ft::pair<std::string, int>("u", 4));
	test.insert(ft::pair<std::string, int>("p", 4));
	test.insert(ft::pair<std::string, int>("l", 4));
	test.insert(ft::pair<std::string, int>("a", 4));
	test.insert(ft::pair<std::string, int>("g", 4));
	test.insert(ft::pair<std::string, int>("n", 4));
	test.insert(ft::pair<std::string, int>("o", 4));
	test.insert(ft::pair<std::string, int>("q", 4));
	test.insert(ft::pair<std::string, int>("r", 4));
	test.insert(ft::pair<std::string, int>("s", 4));
	
	test.end();
	test.find("a");

	

	ft::montree(test._tree.root);


	ft::map<std::string, int>::iterator test1;
	ft::map<std::string, int>::iterator test2;

	test1 = test.find("r");
	test2 = test.find("b");

	test1 = test.lower_bound("u");
	std::cout << "lower " << test1->first << std::endl;

	std::cout << test1->first << std::endl;
	std::cout << (test2 == test.end()) << std::endl;

	std::cout << (--test2)->first << std::endl;


	ft::map<std::string, int>::iterator	yes = test.end();

	--yes;
	--yes;
	--yes;

	std::cout << yes->first << std::endl;
}