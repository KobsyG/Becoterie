#pragma once

#include "pair.hpp"
#include "../utils.hpp"

#define BLACK	0
#define RED		1

namespace ft {

	template <class value_type>
	struct node
	{
		value_type	data;
		struct node<value_type> *left;
		struct node<value_type> *right;
		struct node<value_type>	*parent;
		int						color;

		node(const value_type & data) : data(data), color(1), left(NULL), right(NULL), parent(NULL) {}

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

	template< class _Pair >
	class	tree_iterator
	{
		public:


			typedef 		_Pair 									value_type;
			typedef 		_Pair&									reference;
			typedef 		_Pair*									pointer;

			typedef typename std::ptrdiff_t 						difference_type;
			typedef std::bidirectional_iterator_tag					category;

			typedef tree_iterator<_Pair>	 						_Self;
			typedef ft::node<_Pair>* 								_Node_ptr;


			_Node_ptr		current;
			_Node_ptr		senti;

			// Constructeur=======================================================================================

			tree_iterator() : current(), senti() {}

			tree_iterator(_Node_ptr gang)
			{
				/* if (gang == NULL)
				{
					tree_iterator();
					return;
				} */
				senti = gang;
				while (senti->parent)
					senti = senti->parent;
				current = gang;
			}


			pointer base() const { return current; }

			// Operateur=========================================================================================

			tree_iterator&	operator=(const _Self& other)
			{
				current = other.current;
				senti = other.senti;
				return (*this);
			}

			// Operateur de comparaison==========================================================================

			bool	operator==(const tree_iterator & other) const { return (this->current == other.current); }

			bool	operator!=(const tree_iterator & other) const { return (this->current != other.current); }

			bool	operator<(const tree_iterator & other) const
			{
				if ( this->current < other.current)
					return true;
				return false;
			}

			bool	operator>(const tree_iterator & other) const
			{
				if ( this->current > other.current)
					return true;
				return false;
			}

			bool	operator<=(const tree_iterator & other) const
			{
				if ( this->current <= other.current)
					return true;
				return false;
			}

			bool	operator>=(const tree_iterator & other) const
			{
				if ( this->current >= other.current)
					return true;
				return false;
			}

			// Operateur de dereferencement====================================================================

			reference	operator*() const { return current->data; }

			pointer		operator->() const { return &current->data; }

			// Operateur d'incrementation=====================================================================

			tree_iterator&	operator++()
			{
				if (current != senti)
					current = current->next();
				if (current == NULL)
					current = senti;
				return *this;
			}

			tree_iterator	operator++(int)
			{
				tree_iterator	tmp = *this;
				++*this;
				return (tmp);
			}

			// // Operateur de decrementation=====================================================================

			tree_iterator&	operator--()
			{
				if (current == senti)
					current = last();
				else
					current = current->previous();
				return *this;
			}
			
			tree_iterator	operator--(int)
			{
				tree_iterator	tmp = *this;
				--*this;
				return tmp;
			}

			_Node_ptr	last()
			{
				_Node_ptr tmp = senti->left;
				while (tmp && tmp->right)
					tmp = tmp->right;
				return tmp;			
			}
	};

	template< class _Pair >
	class	const_tree_iterator
	{
		public:


			typedef 		_Pair 									value_type;
			typedef 		const _Pair&							reference;
			typedef 		const _Pair*							pointer;

			typedef 		tree_iterator<_Pair> 					iterator;
			typedef typename std::ptrdiff_t 						difference_type;
			typedef std::bidirectional_iterator_tag					category;

			typedef 		const_tree_iterator<_Pair>	 			_Self;
			typedef 		const ft::node<_Pair>* 					_Node_ptr;


			_Node_ptr		current;
			_Node_ptr		senti;

			// Constructeur=======================================================================================

			const_tree_iterator() : current(), senti() {}

			const_tree_iterator(_Node_ptr gang)
			{
			/* 	if (gang == NULL)
				{
					const_tree_iterator();
					return;
				} */
				senti = gang;
				while (senti->parent)
					senti = senti->parent;
				current = gang;
			}

			const_tree_iterator(const iterator other) { current = other.current; senti = other.senti; }

			pointer base() const { return current; }

			// Operateur=========================================================================================

			const_tree_iterator&	operator=(const const_tree_iterator& other)
			{
				current = other.current;
				senti = other.senti;
				return (*this);
			}

			// Operateur de comparaison==========================================================================

			bool	operator==(const const_tree_iterator & other) const { return (this->current == other.current); }

			bool	operator!=(const const_tree_iterator & other) const { return (this->current != other.current); }

			bool	operator<(const const_tree_iterator & other) const
			{
				if ( this->current < other.current)
					return true;
				return false;
			}

			bool	operator>(const const_tree_iterator & other) const
			{
				if ( this->current > other.current)
					return true;
				return false;
			}

			bool	operator<=(const const_tree_iterator & other) const
			{
				if ( this->current <= other.current)
					return true;
				return false;
			}

			bool	operator>=(const const_tree_iterator & other) const
			{
				if ( this->current >= other.current)
					return true;
				return false;
			}

			// Operateur de dereferencement====================================================================

			reference	operator*() const { return current->data; }

			pointer		operator->() const { return &current->data; }

			// Operateur d'incrementation=====================================================================

			const_tree_iterator& operator++() {
				if (current != senti) {
					if (current->right != NULL) {
						current = current->right;
						while (current->left != NULL) {
							current = current->left;
						}
					}
					else {
						_Node_ptr _y = current->parent;
						while (_y != NULL && current == _y->right) {
							current = _y;
							_y = _y->parent;
						}
						current = _y;
					}
				}
				if (current == NULL) {
					current = senti;
				}
				return *this;
			}

			const_tree_iterator	operator++(int)
			{
				const_tree_iterator	tmp = *this;
				++*this;
				return (tmp);
			}

			// // Operateur de decrementation=====================================================================

			_Node_ptr maximum(_Node_ptr node) {
				while (node->right != NULL)
					node = node->right;
				return node;
			}

			const_tree_iterator&	operator--()
			{
				if (current == senti) {
					current = maximum(senti->left);
				}
				else if (current->left != NULL) {
					current = current->left;
					while (current->right != NULL) {
						current = current->right;
					}
				}
				else {
					_Node_ptr _y = current->parent;
					while (_y != NULL && current == _y->left) {
						current = _y;
						_y = _y->parent;
					}
					current = _y;
				}
				return *this;
				/* if (current == senti)
					current = last();
				else
					current = current->previous();
				return *this; */
			}
			
			const_tree_iterator	operator--(int)
			{
				const_tree_iterator	tmp = *this;
				--*this;
				return tmp;
			}

			_Node_ptr	last()
			{
				_Node_ptr tmp = senti->left;
				while (tmp && tmp->right)
					tmp = tmp->right;
				return tmp;			
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

			typedef tree_iterator<value_type>											iterator;
			typedef const_tree_iterator<value_type>										const_iterator;

			

			allocator_type		_alloc;
		
		private:
			key_compare			_key_comp;
			value_compare		_val_comp;

			pointer		make_node(const value_type& data)
			{
				pointer	tmp = _alloc.allocate(1);
				_alloc.construct(tmp, data);
				return tmp;
			}

			void _delete_node(pointer x) {
				if (x != NULL) {
					_alloc.destroy(x);
					_alloc.deallocate(x, 1);
					x = NULL;
				}
			}

			void _delete_tree(pointer x) {
				if (x != NULL) {
					_delete_tree(x->left);
					_delete_tree(x->right);
					_delete_node(x);
					senti->left = senti;
				}
			}

			pointer _copy_tree(pointer x) {
				if (x == NULL) 
					return NULL;
				pointer y = make_node(x->data);
				y->color = x->color;
				y->left = _copy_tree(x->left);
				if (y->left != NULL) {
					y->left->parent = y;
				}
				y->right = _copy_tree(x->right);
				if (y->right != NULL) {
					y->right->parent = y;
				}
				return y;
			}

			friend bool operator==(const RBtree& _l, const RBtree& _r) {
				return ft::equal(_l.begin(), _l.end(), _r.begin(), _r.end());
			}

			friend bool operator<(const RBtree& _l, const RBtree& _r) {
				return ft::lexicographical_compare(_l.begin(), _l.end(), _r.begin(), _r.end());
			}

			friend bool operator!=(const RBtree& _l, const RBtree& _r) { return !(_l == _r); }

			friend bool operator>(const RBtree& _l, const RBtree& _r) { return _r < _l; }

			friend bool operator<=(const RBtree& _l, const RBtree& _r) { return !(_r < _l); }

			friend bool operator>=(const RBtree& _l, const RBtree& _r) { return !(_l < _r); }
		
		public:
		
			pointer 					root;
			pointer						senti;

			RBtree() : root(NULL) {
				senti = _alloc.allocate(1);
				_alloc.construct(senti, value_type());
				senti->parent = NULL;
			}

			RBtree(const RBtree& other) : root(NULL) {
				root = _copy_tree(other.root);
 				_val_comp = other._val_comp;
				_key_comp = other._key_comp;
				senti = _alloc.allocate(1);
				_alloc.construct(senti, value_type());
				root->parent = senti;
				if (root != NULL)
					senti->left = root;
			}

			//insert==========================================================================================

			ft::pair<iterator, bool>	insert(const value_type& value) // changer return ici 
			{
				return (insert(value, root));
			}

			ft::pair<iterator, bool>	insert(const value_type& value, pointer start)
			{
				pointer	tmp = start;
				pointer y = NULL;

				if (root)
					root->parent = NULL;
				while (tmp != NULL)
				{
					if (!_val_comp(tmp->data, value) && !_val_comp(value, tmp->data)) {
						return (ft::make_pair(iterator(tmp), false));
					}
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
				if (tmp->parent->parent)
					fix_insert(tmp);
				senti->left = root;
				root->parent = senti;
				return make_pair(iterator(tmp), true);
			}

			// iterator insert(iterator position, const value_type& val) {
			// 	pointer node = position.current;
			// 	pointer tmp = node;

			// 	// Check si il est a un endroit valide, sinon on appelle le insert normal à la place
			// 	if (tmp->parent && tmp->parent->right)
			// 		if (tmp->parent->right == tmp && _val_comp(val, tmp->data)) // Si il est a droite mais qu'il est plus petit
			// 			return insert(val);
		
			// 	if (tmp->parent && tmp->parent->left)
			// 		if (tmp->parent->left == tmp && _val_comp(tmp->data, val)) // Si il est a gauche mais qu'il est plus grand
			// 			return insert(val);

			// 	pointer y = NULL;
			// 	while (tmp != NULL)
			// 	{
			// 		y = tmp;
			// 		if (_val_comp(val, tmp->data))
			// 			tmp = tmp->left;
			// 		else
			// 			tmp = tmp->right;
			// 	}
			// 	tmp = make_node(val);
			// 	tmp->parent = y;
			// 	if (y == NULL)
			// 	{
			// 		root = tmp;
			// 		root->color = BLACK;
			// 	}
			// 	else if (_val_comp(val, y->data))
			// 		y->left = tmp;
			// 	else
			// 		y->right = tmp;
			// 	fix_insert(tmp);
			// 	senti->left = root;
			// 	root->parent = senti;
			// 	return iterator(tmp);
			// }

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
					// std::cout << key << ": case 1" << std::endl;
					if (node->parent && node->parent->left && node->parent->left == node)
						node->parent->left = NULL;
					else if (node->parent && node->parent->right && node->parent->right == node)
						node->parent->right = NULL;
					if (node == root)
						root = NULL;
				} else if (node->right && !node->left) { // Case 2: node only has right child
					// std::cout << key << ": case 2" << std::endl;
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
					// std::cout << key << ": case 3" << std::endl;
					node->left->parent = node->parent;
					if (node->parent->right && node->parent->right == node)
						node->parent->right = node->left;
					else if (node->parent->left && node->parent->left == node)
						node->parent->left = node->left;
					if (node == root)
						root = node->left;
				} else { // Case 4: node has right and left childs
					// std::cout << key << ": case 4" << std::endl;
					pointer successor = minimum(node->right);
					pointer tmp = node->right;

					// if right subtree doesnt have left branch
					if (tmp->left == NULL) {
						tmp->left = node->left;
						node->left->parent = tmp;
						tmp->parent = node->parent;
						if (node->parent == senti) {
							root = tmp;
							senti->left = root;
						}
						else {
							if (node->parent->left == node)
								node->parent->left = tmp;
							else
								node->parent->right = tmp;
						}
					} else {

						if (successor->parent->left && successor->parent->left == successor)
							successor->parent->left = NULL;
						else if (successor->parent->right && successor->parent->right == successor)
							successor->parent->right = NULL;

						//if successor has a right child
						if (successor->right) {
							if (successor == node->right) {
								successor->right->parent = successor->parent;
								successor->parent->left = successor->right;
							} else {
								successor->right->parent = successor->parent;
								successor->parent->left = successor->right;
							}
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
				}
				_alloc.destroy(node);
				_alloc.deallocate(node, sizeof(value_type));
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

			pointer				first() const
			{
				pointer				tmp = root;
				if (tmp == NULL) // if empty, return end
					return senti;
				while (tmp && tmp->left)
					tmp = tmp->left;
				return tmp;
			}

			pointer				last()
			{
				pointer				tmp = root;
				while(tmp && tmp->right)
					tmp = tmp->right;
				return tmp;
			}

			iterator	begin()
			{
				return (iterator(first()));
			}

			const_iterator	begin() const
			{
				return (const_iterator(first()));
			}

			iterator	end()
			{
				return iterator(senti);
			}

			const_iterator	end() const
			{
				return const_iterator(senti);
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
				iterator it = begin();
				for (; it != end() && _key_comp(it->first, k); ++it);
				return it;
			}

			const_iterator	lower_bound(const key_type& k) const
			{
				const_iterator it = begin();
				for (; it != end() && _key_comp(it->first, k); ++it);
				return it;
			}

			iterator	upper_bound(const key_type& k)
			{
				iterator it = begin();
				for (; it != end() && !_key_comp(k, it->first); it++);
				return it;
			}

			const_iterator	upper_bound(const key_type& k) const
			{
				const_iterator it = begin();
				for (; it != end() && !_key_comp(k, it->first); it++);
				return it;
			}

			pair<iterator, iterator>	equal_range(const key_type& k)
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}


			void clear() {
				_delete_tree(root);
				root = NULL;
			}

			size_t	max_size() const { return _alloc.max_size(); }
	};
	
}