#pragma once

#include "map.hpp"
#include "tree.hpp"

#define BLACK	0
#define RED		1

namespace ft {

template <class value_type>
void	montree(const node<value_type>* node)
{
	montree("", node, false);
}

template <class value_type>
void	montree(const std::string& prefix, const node<value_type>* node, bool isLeft)
{
	if (node != NULL)
	{
		std::cout << prefix;
		std::cout << (isLeft ? "├──" : "└──");

		if (node->color == 1)
			std::cout << "\033[31m" << node->data.first << "\033[0m" << std::endl;
		else
			std::cout << node->data.first << std::endl;
		montree(prefix + (isLeft ? "│   " : "    "), node->left, true);
		montree(prefix + (isLeft ? "│   " : "    "), node->right, false);
	}
}

}