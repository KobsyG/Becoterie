#pragma once

#include "map.hpp"
#include "tree.hpp"

#define BLACK	0
#define RED		1

namespace ft {

	//Sert juste pour la fonctions qui print l'arbre
	struct Trunk
	{
		Trunk *prev;
		std::string str;
	
		Trunk(Trunk *prev, std::string str)
		{
			this->prev = prev;
			this->str = str;
		}
	};

	void showTrunks(Trunk *p)
			{
				if (p == nullptr)
					return;
				showTrunks(p->prev);
				std::cout << p->str;
			}
			
	template <class value_type>
	void printTree(node<value_type>* root, Trunk *prev, bool isLeft)
	{
		if (root == nullptr)
			return;
		std::string prev_str = "    ";
		Trunk *trunk = new Trunk(prev, prev_str);
	
		printTree(root->right, trunk, true);
	
		if (!prev)
			trunk->str = "———";
		else if (isLeft)
		{
			trunk->str = "┌———";
			prev_str = "    |";
		}
		else {
			trunk->str = "└──";
			prev->str = prev_str;
		}
	
		showTrunks(trunk);
		if (root->color == RED)
			std::cout << "\033[31m" << root->data.first << "\033[0m" << std::endl;
		else
			std::cout << root->data.first << std::endl;
			
		if (prev) {
			prev->str = prev_str;
		}
		trunk->str = "    |";
	
		printTree(root->left, trunk, false);
	}

}