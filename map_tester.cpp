#include <fstream>
#include <iostream>

// #ifdef STD
	// #include <map>
	// #include <utility>
	// namespace ft = std;
// #else
// #endif

#include "map.hpp"
#include "utils.hpp"

int	main()
{
	ft::map<std::string, int>	test;

	ft::pair<std::string, int> m("m", 1);
	ft::pair<std::string, int> f("f", 2);
	ft::pair<std::string, int> c("c", 4);
	ft::pair<std::string, int> d("d", 4);
	ft::pair<std::string, int> e("e", 4);
	ft::pair<std::string, int> u("u", 4);
	ft::pair<std::string, int> p("p", 4);
	ft::pair<std::string, int> l("l", 4);
	ft::pair<std::string, int> a("a", 4);
	ft::pair<std::string, int> g("g", 4);
	ft::pair<std::string, int> n("n", 4);
	ft::pair<std::string, int> o("o", 4);
	ft::pair<std::string, int> q("q", 4);
	ft::pair<std::string, int> r("r", 4);
	
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

	// ft::montree(test.tree.root);

	ft::map<std::string, int>::iterator	yes = test.end();
	// ++yes;
	// --yes;
	// --yes;
	// ++yes;

	// std::cout << yes->first << std::endl;

	

	
}