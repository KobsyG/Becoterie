#include <fstream>
#include <iostream>

#include <map>

// #include "map.hpp"

int	main()
{
	std::map<std::string, int>	test;

	std::pair<std::string, int> m("m", 1);
	std::pair<std::string, int> f("f", 2);
	std::pair<std::string, int> c("c", 4);
	std::pair<std::string, int> d("d", 4);
	std::pair<std::string, int> e("e", 4);
	std::pair<std::string, int> u("u", 4);
	std::pair<std::string, int> p("p", 4);
	std::pair<std::string, int> l("l", 4);
	std::pair<std::string, int> a("a", 4);
	std::pair<std::string, int> g("g", 4);
	std::pair<std::string, int> n("n", 4);
	std::pair<std::string, int> o("o", 4);
	std::pair<std::string, int> q("q", 4);
	std::pair<std::string, int> r("r", 4);
	
	test.insert(m);
	test.insert(f);
	test.insert(e);
	test.insert(u);
	test.insert(p);
	test.insert(l);
	test.insert(a);
	test.insert(g);
	test.insert(n);
	test.insert(o);
	test.insert(q);
	test.insert(r);

	std::map<std::string, int>::iterator	yes;
	// --yes;
	// ++yes;
	// ++yes;
	// --yes;
	// --yes;
	// ++yes;

	// std::cout << yes->first << std::endl;

	

	
}