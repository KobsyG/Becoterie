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

	template <class value_type, class key_compare, class value_compare, class Alloc = std::allocator<ft::node<value_type> > >
	class RBtree
	{
		public:

			typedef Alloc																allocator_type;
			typedef	typename value_type::first_type										key_type;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;

			typedef tree_iterator<pointer, node_senti<value_type>* >					iterator;
			typedef tree_iterator<const_pointer, node_senti<value_type>* >				const_iterator;

			

			allocator_type		_alloc;
		
		private:
			key_compare			_key_comp;
			value_compare		_val_comp;

			pointer		make_node(const value_type& data)
			{
				pointer	tmp = _alloc.allocate(1);
				std::cout << "alloc " << tmp << std::endl;
				_alloc.construct(tmp, data);
				return tmp;
			}
		
		public:
		
			pointer 					root;
			pointer						senti;

			RBtree() : root(NULL) {
				senti = _alloc.allocate(1);
				_alloc.construct(senti, value_type());
			}



			//insert==========================================================================================

			iterator	insert(const value_type& value) // changer return ici 
			{
				pointer	tmp = root;
				pointer y = NULL;

				if (root)
					root->parent = NULL;
				while (tmp != NULL)
				{
					y = tmp;
					if (_val_comp(value, tmp->data))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				tmp = make_node(value);
				tmp->parent = y;
				if (y == NULL)
				{
					root = tmp;
					root->color = BLACK;
				}
				else if (_val_comp(value, y->data))
					y->left = tmp;
				else
					y->right = tmp;
				fix_insert(tmp);
				senti->left = root;
				root->parent = static_cast<node<value_type>* >(senti);
				return iterator(tmp);
			}

			iterator insert(iterator position, const value_type& val) {
				pointer node = position.current;
				pointer tmp = node;

				// Check si il est a un endroit valide, sinon on appelle le insert normal à la place
				if (tmp->parent && tmp->parent->right)
					if (tmp->parent->right == tmp && _val_comp(val, tmp->data)) // Si il est a droite mais qu'il est plus petit
						return insert(val);
		
				if (tmp->parent && tmp->parent->left)
					if (tmp->parent->left == tmp && _val_comp(tmp->data, val)) // Si il est a gauche mais qu'il est plus grand
						return insert(val);

				pointer y = NULL;
				while (tmp != NULL)
				{
					y = tmp;
					if (_val_comp(val, tmp->data))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				tmp = make_node(val);
				tmp->parent = y;
				if (y == NULL)
				{
					root = tmp;
					root->color = BLACK;
				}
				else if (_val_comp(val, y->data))
					y->left = tmp;
				else
					y->right = tmp;
				fix_insert(tmp);
				senti->left = root;
				root->parent = static_cast<ft::node<value_type>* >(senti);
				return iterator(tmp);
			}

			void	fix_insert(node<value_type>* node)
			{
				pointer tmp = node;
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

			//erase==========================================================================================

			void delete_fixup(pointer node) {
				
			}

			void transplant(pointer a, pointer b) {
				if (a->parent == senti)
					root = b;
				else if (a == a->parent->left) {
					std::cout << a->parent->left->data.first << " = " << b << std::endl;
					a->parent->left = b;
				}
				else {
					std::cout << a->parent->right->data.first << " = " << b << std::endl;
					a->parent->right = b;
				}
				if (b)
					b->parent = a->parent;
			}

			size_t erase(const key_type& key) {
				pointer node = find_ptr(key);
				
				if (!node) return 0;

				if (!node->right && !node->left) { // Case 1: leaf
					std::cout << key << ": case 1" << std::endl;
					if (node->parent && node->parent->left && node->parent->left == node)
						node->parent->left = NULL;
					else if (node->parent && node->parent->right && node->parent->right == node)
						node->parent->right = NULL;
					if (node == root)
						root = NULL;
				} else if (node->right && !node->left) { // Case 2: node only has right child
					std::cout << key << ": case 2" << std::endl;
					node->right->parent = node->parent;
					if (node->parent->right && node->parent->right == node) {
						node->parent->right = node->right;
					}
					else if (node->parent->left && node->parent->left == node) {
						node->parent->left = node->right;
					}
					if (node == root)
						root = node->right;
				} else if (!node->right && node->left) { // Case 3: node only has left child
					std::cout << key << ": case 3" << std::endl;
					node->left->parent = node->parent;
					if (node->parent->right && node->parent->right == node)
						node->parent->right = node->left;
					else if (node->parent->left && node->parent->left == node)
						node->parent->left = node->left;
					if (node == root)
						root = node->left;
				} else { // Case 4: node has right and left childs
					std::cout << key << ": case 4" << std::endl;
					pointer successor = minimum(node->right);
					pointer tmp = node->right;

					if (successor->parent->left && successor->parent->left == successor)
						successor->parent->left = NULL;
					else if (successor->parent->right && successor->parent->right == successor)
						successor->parent->right = NULL;

					//if successor has a right child
					if (successor->right) {
						successor->right->parent = successor->parent;
						successor->parent->left = successor->right;
					}

					successor->parent = node->parent;
					if (node->parent->right && node->parent->right == node)
						node->parent->right = successor;
					else if (node->parent->left && node->parent->left == node)
						node->parent->left = successor;
					if (successor != tmp) {
						successor->right = tmp;
						tmp->parent = successor;
					}
					successor->left = node->left;
					node->left->parent = successor;

					if (root == node)
						root = successor;
				}
				_alloc.destroy(node);
				std::cout << "dealloc " << node << std::endl;
				_alloc.deallocate(node, sizeof(value_type));
				std::cout << node << std::endl;
				return 1;
			}

			//min/max from node==========================================================================================

			pointer minimum(pointer node) {
				while (node->left != NULL) {
					node = node->left;
				}
				return node;
			}

			pointer maximum(pointer node) {
				while (node->right != NULL) {
					node = node->right;
				}
				return node;
			}

			//rotate===========================================================================================

			void	left_rotation(pointer x)
			{
				pointer y = x->right;
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

			void	right_rotation(pointer x)
			{
				pointer y = x->left;

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

			//first/last/iterators===========================================================================

			node<value_type>	*first()
			{
				node<value_type>	*tmp = root;
				while (tmp && tmp->left)
					tmp = tmp->left;
				return tmp;
			}

			node<value_type>	*last()
			{
				node<value_type>	*tmp = root;
				while(tmp && tmp->right)
					tmp = tmp->right;
				return tmp;
			}

			iterator	begin()
			{
				return (iterator(first()));
			}

			iterator	end()
			{
				return iterator(senti);
			}

			//find/erase========================================================================================

			pointer	find_ptr(const key_type& k)
			{
				pointer tmp = root;
				while (tmp != NULL && tmp->data.first != k)
				{
					if (_key_comp(k, tmp->data.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (tmp == NULL)
					return NULL;
				return tmp;
			}

			iterator	find(const key_type& k)
			{
				pointer tmp = root;
				while (tmp != NULL && tmp->data.first != k)
				{
					if (_key_comp(k, tmp->data.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (tmp == NULL)
					return end();
				return iterator(tmp);
			}

			const_iterator	find(const key_type& k) const
			{
				pointer tmp = root;
				while (tmp != NULL && tmp->data.first != k)
				{
					if (_key_comp(k, tmp->data.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (tmp == NULL)
					return end();
				return const_iterator(tmp);
			}

			//bounds/range===========================================================================================

			iterator	lower_bound(const key_type& k) //fonctionne en theorie mais a tester plus en details
			{
				node<value_type>	*tmp = root;
				while (tmp != NULL)
				{
					if (tmp->data.first == k)
						return iterator(tmp);
					else if (tmp->parent != senti && _key_comp(k, tmp->parent->data.first) && !_key_comp(k, tmp->data.first))
						return iterator(tmp->next());
					if (_key_comp(k, tmp->data.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return iterator(root);
			}

			const_iterator	lower_bound(const key_type& k) const
			{
				node<value_type>	*tmp = root;
				while (tmp != NULL)
				{
					if (tmp->data.first == k)
						return const_iterator(tmp);
					else if (tmp->parent != senti && _key_comp(k, tmp->parent->data.first) && !_key_comp(k, tmp->data.first))
						return const_iterator(tmp);
					if (_key_comp(k, tmp->data.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return const_iterator(tmp);
			}

			iterator	upper_bound(const key_type& k)
			{
				node<value_type>	*tmp = root;
				while (tmp != NULL)
				{
					//if (tmp->parent != senti)
					//std::cout << k << " " << tmp->parent->data.first << " " << tmp->data.first << " " << !_key_comp(k, tmp->parent->data.first) << " " <<  _key_comp(k, tmp->data.first) << std::endl;
					if (tmp->data.first == k)
						return iterator(tmp->next());
					else if (tmp->parent != senti && _key_comp(k, tmp->parent->data.first) && !_key_comp(k, tmp->data.first)){
						//std::cout << k << " " << tmp->parent->data.first << " " << tmp->data.first << std::endl;
						return iterator(tmp->next());
					}
					if (_key_comp(k, tmp->data.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				std::cout << "alo" << std::endl;
				return end();
			}

			const_iterator	upper_bound(const key_type& k) const
			{
				node<value_type>	*tmp = root;
				while (tmp != NULL)
				{
					if (tmp->data.first == k)
						return const_iterator(tmp->next());
					else if (tmp->parent != NULL && _key_comp(k, tmp->parent->data.first) && !_key_comp(k, tmp->data.first))
						return const_iterator(tmp->next());
					if (_key_comp(k, tmp->data.first))
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				return const_iterator(root);
			}

			pair<iterator, iterator>	equal_range(const key_type& k)
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}
	};
	
}