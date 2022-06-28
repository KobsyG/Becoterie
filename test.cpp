#include "map.hpp"
#include <map>

void printContent(ft::map<int, char> map){
	for(auto it = map.begin(); it != map.end(); ++it){
		std::cout << it->first << " " << it->second << " ";
	}
	std::cout << std::endl;
}

void printContent(std::map<int, char> map){
	for(auto it = map.begin(); it != map.end(); ++it){
		std::cout << it->first << " " << it->second << " ";
	}
	std::cout << std::endl;
}

/* int main() {
	std::map<int, char> m;
	m.insert(std::make_pair(8, 'a'));
	m.insert(std::make_pair(10, 'b'));
	m.insert(std::make_pair(3, 'c'));
	m.insert(std::make_pair(1, 'd'));
	m.insert(std::make_pair(6, 'e'));
	m.insert(std::make_pair(4, 'f'));
	m.insert(std::make_pair(7, 'g'));
	m.insert(std::make_pair(14, 'h'));
	m.insert(std::make_pair(13, 'i'));
	std::map<int, char> m2(m);
	//m.insert(std::make_pair(1, 'w'));
	printContent(m);
	printContent(m2);
	std::cout << (m < m2) << std::endl;
	std::cout << (m <= m2) << std::endl;
	std::cout << (m > m2) << std::endl;
	std::cout << (m >= m2) << std::endl;
} */

int main() {
	ft::map<int, char> m;
	m.insert(ft::make_pair(8, 'a'));
	m.insert(ft::make_pair(10, 'b'));
	m.insert(ft::make_pair(3, 'c'));
	m.insert(ft::make_pair(1, 'd'));
	m.insert(ft::make_pair(6, 'e'));
	m.insert(ft::make_pair(4, 'f'));
	m.insert(ft::make_pair(7, 'g'));
	m.insert(ft::make_pair(14, 'h'));
	m.insert(ft::make_pair(13, 'i'));
	ft::map<int, char> m2(m);
	std::cout << (m == m2) << std::endl;
	std::cout << (m != m2) << std::endl;
	ft::pair<ft::map<int, char>::iterator, bool> pair = m.insert(ft::make_pair(1, 'w'));
	std::cout << "inserted: " << pair.second << std::endl;
	ft::map<int, char>::iterator it = m.find(1);
	std::cout << "found: " << it->second << std::endl;
	ft::printTree(m._tree.root, nullptr, false);
	ft::printTree(m2._tree.root, nullptr, false);
	printContent(m);
	printContent(m2);
	std::cout << (m < m2) << std::endl;
	std::cout << (m <= m2) << std::endl;
	std::cout << (m > m2) << std::endl;
	std::cout << (m >= m2) << std::endl;

	std::map<int, char> m3;
	m3.insert(std::make_pair(1, 'd'));
	m3.insert(std::make_pair(1, 'w'));
	std::map<int, char>::iterator it2 = m3.find(1);
	std::cout << "found: " << it2->second << std::endl;
}