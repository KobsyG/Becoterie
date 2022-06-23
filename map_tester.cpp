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
	//test.insert(ft::pair<std::string, int>("n", 4));
	test.insert(ft::pair<std::string, int>("o", 4));
	test.insert(ft::pair<std::string, int>("q", 4));
	//test.insert(ft::pair<std::string, int>("r", 4));
	test.insert(ft::pair<std::string, int>("s", 4));
	
	test.end();
	test.find("a");

	

	//ft::printTree(test._tree.root, nullptr, false);


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

	ft::map<std::string, int>::const_iterator cend = test.begin();
	std::cout << cend->first << std::endl;


	//ft::printTree(test._tree.root, nullptr, false);
	
	// std::cout << "erase c" << std::endl;
	test.erase("c");
	// //ft::printTree(test._tree.root, nullptr, false);
	
	// std::cout << "erase s" << std::endl;
	test.erase("s");
	// //ft::printTree(test._tree.root, nullptr, false);

	// std::cout << "erase f" << std::endl;
	test.erase("f");
	// //ft::printTree(test._tree.root, nullptr, false);
	
	//std::cout << "erase b" << std::endl;
	std::cout << test.erase("b") << std::endl;
	
	// ft::printTree(test._tree.root, nullptr, false);
	// std::cout << "erase g" << std::endl;
	std::cout << test.erase("g") << std::endl;
	// //ft::printTree(test._tree.root, nullptr, false);
	// ft::printTree(test._tree.root, nullptr, false);

	// std::cout << "erase m" << std::endl;
	std::cout << test.erase("m") << std::endl;
	// //ft::printTree(test._tree.root, nullptr, false);

	// std::cout << "erase n" << std::endl;
	std::cout << test.erase("n") << std::endl;
	// //ft::printTree(test._tree.root, nullptr, false);

	// std::cout << "erase p" << std::endl;
	std::cout << test.erase("p") << std::endl;
	//ft::printTree(test._tree.root, nullptr, false);

	std::cout << "erase d" << std::endl;
	std::cout << test.erase("d") << std::endl;
	//ft::printTree(test._tree.root, nullptr, false);

	test.erase(test.begin());
	//ft::printTree(test._tree.root, nullptr, false);

	std::cout << test.size() << std::endl;
}