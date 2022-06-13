#pragma once

#include "pair.hpp"
#include "tree_iterator.hpp"

#define BLACK	0
#define RED		1

namespace ft {

template <class value_type>
struct node;

template <class value_type>
struct node_senti
{
	public:
	
		struct node<value_type> *left;
		struct node<value_type> *right;
		struct node<value_type>	*parent;
		// node_senti				*senti;
		int						color;

	public:

		node_senti() : left(NULL), right(NULL), parent(NULL), color(1) {}

};

template <class value_type>
struct node	: public node_senti<value_type>
{
	value_type	data;

	node() : node_senti<value_type>() {}

	node(const value_type & data) : node_senti<value_type>(), data(data) {}

	node(const node& other) { *this = other; }

	node&	operator=(const node& other) { this->left = other.left; this->right = other.right; this->parent = other.parent; this->color = other.color; data = other.data; return *this;}

	node *next()
	{
		node	*tmp = this;
		if (tmp->right != NULL)
		{
			tmp = tmp->right;
			while (tmp->left != NULL)
				tmp = tmp->left;
			return tmp;
		}
		else
		{
			while (tmp->parent != NULL && tmp == tmp->parent->right)
				tmp = tmp->parent;
			return tmp->parent;
		}
	}

	node *previous()
	{
		node	*tmp = this;
		if (tmp->left != NULL)
		{
			tmp = tmp->left;
			while (tmp->right != NULL)
				tmp = tmp->right;
			return tmp;
		}
		else
		{
			while (tmp->parent != NULL && tmp == tmp->parent->left)
				tmp = tmp->parent;
			return tmp->parent;
		}
	}

};

template<class value_type>
node<value_type>*	make_node(const value_type& data)
{
	node<value_type>	*new_node = new node<value_type>(data);
	return new_node;
}

template <class value_type, class Compare, class Alloc>
class RBtree
{
	public:

		typedef tree_iterator< node<value_type>*, node_senti<value_type>* >					iterator;
	
	private:
		Compare				_compare;
		Alloc				_alloc;
	
	public:
	
		ft::node<value_type>		*root;
		ft::node_senti<value_type>	*senti;

		RBtree() : root(NULL) { senti = new node_senti<value_type>();}

		void	insert(const value_type& value) // changer return ici 
		{
			ft::node<value_type>	*tmp = root;
			ft::node<value_type>	*y = NULL;

			if (root)
				root->parent = NULL;
			while (tmp != NULL)
			{
				y = tmp;
				if (_compare(value, tmp->data))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			tmp = make_node(value);
			tmp->parent = y;
			if (y == NULL)
			{
				root = tmp;
				root->color = 0;
			}
			else if (_compare(value, y->data))
				y->left = tmp;
			else
				y->right = tmp;
			fix_insert(tmp);
			senti->left = root;
			root->parent = static_cast<node<value_type>* >(senti);
		}

		void	fix_insert(node<value_type>* node)
		{
			ft::node<value_type>	*tmp = node;
			while (tmp->parent && tmp->parent->color == RED)
			{
				if (tmp->parent == tmp->parent->parent->left)
				{
					if (tmp->parent->parent->right && tmp->parent->parent->right->color == RED)
					{
						tmp->parent->parent->left->color = BLACK;
						tmp->parent->parent->right->color = BLACK;
						tmp->parent->parent->color = RED;
						tmp = tmp->parent->parent;
					}
					else if (tmp->parent->right && tmp == tmp->parent->right)
					{
						tmp = tmp->parent;
						left_rotation(tmp);
					}
					else
					{
						tmp->parent->color = BLACK;
						tmp->parent->parent->color = RED;
						right_rotation(tmp->parent->parent);
					}
				}
				else
				{
					if (tmp->parent->parent && tmp->parent->parent->left && tmp->parent->parent->left->color == RED)
					{
						tmp->parent->parent->left->color = BLACK;
						tmp->parent->parent->right->color = BLACK;
						tmp->parent->parent->color = RED;
						tmp = tmp->parent->parent;
					}
					else
					{
						if (tmp == tmp->parent->left)
						{
							tmp = tmp->parent;
							right_rotation(tmp);
						}
						tmp->parent->color = BLACK;
						tmp->parent->parent->color = RED;
						left_rotation(tmp->parent->parent);
					}
				}
				root->color = BLACK;
			}
		}

		void	left_rotation(node<value_type>* x)
		{
			node<value_type>	*y = x->right;
			x->right = y->left;
			if (y->left != NULL)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void	right_rotation(node<value_type>* x)
		{
			node<value_type>	*y = x->left;

			x->left = y->right;
			if (y->right != NULL)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		// node<value_type> *next(node<value_type>* node) {
		// 		if (node->right != NULL) {
		// 			node = node->right;
		// 			while (node->left != NULL) {
		// 				node = node->left;
		// 			}
		// 			return node;
		// 		}
		// 		else {
		// 			while (node->parent != NULL && node == node->parent->right) {
		// 				node = node->parent;
		// 			}
		// 			return node->parent;
		// 		}
		// 	}

		// node<value_type> *previous(node<value_type>* node) {
		// 	if (node->left != NULL) {
		// 		node = node->left;
		// 		while (node->right != NULL) {
		// 			node = node->right;
		// 		}
		// 		return node;
		// 	}
		// 	else {
		// 		while (node->parent != NULL && node == node->parent->left) {
		// 			node = node->parent;
		// 		}
		// 		return node->parent;
		// 	}
		// }

		node<value_type>	*first()
		{
			node<value_type>	*tmp = root;
			while (tmp->left)
				tmp = tmp->left;
			return tmp;
		}

		node<value_type>	*last()
		{
			node<value_type>	*tmp = root;
			while(tmp->right)
				tmp = tmp->right;
			return tmp;
		}

		iterator	begin()
		{
			return (iterator(first()));
		}

		iterator	end()
		{
			iterator it(last());
			++it;
			return (it);
		}

};

}