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

			typedef Alloc																		allocator_type;

			typedef	typename value_type::first_type												key_type;
			typedef typename allocator_type::pointer											pointer;

			typedef tree_iterator< node<value_type>*, node_senti<value_type>* >					iterator;
			typedef tree_iterator< const node<value_type>*, node_senti<value_type>* >			const_iterator;

			

		
		private:
			key_compare			_key_comp;
			value_compare		_val_comp;
			Alloc				_alloc;

			pointer		make_node(const value_type& data)
			{
				pointer	tmp = _alloc.allocate(1);
				_alloc.construct(tmp, data);
				return tmp;
			}
		
		public:
		
			pointer 					root;
			ft::node_senti<value_type>	*senti;

			RBtree() : root(NULL) { senti = new node_senti<value_type>(); }



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
					root->color = 0;
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
					root->color = 0;
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

			void fix_erase(pointer node) {
				pointer s;
				while (node != root && node->color == BLACK)
				{
					if (node == node->parent->left)
					{
						s = node->parent->right;
						if (s->color == RED)
						{
							s->color = BLACK;
							node->parent->color = RED;
							left_rotation(node->parent);
							s = node->parent->right;
						}

						if (s->left->color == BLACK && s->right->color == BLACK) {
							s->color = RED;
							node = node->parent;
						} else {
							if (s->right->color == BLACK) {
								s->left->color = BLACK;
								s->color = RED;
								right_rotation(s);
								s = node->parent->right;
							}
							s->color = node->parent->color;
							node->parent->color = BLACK;
							s->right->color = BLACK;
							left_rotation(node->parent);
							node = root;
						}
					} else {
						s = node->parent->left;
						if (s->color == RED)
						{
							s->color = BLACK;
							node->parent->color = RED;
							right_rotation(node->parent);
							s = node->parent->left;
						}

						if (s->right->color == BLACK) {
							s->color = RED;
							node = node->parent;
						} else {
							if (s->left->color == BLACK) {
								s->right->color = BLACK;
								s->color = RED;
								left_rotation(s);
								s = node->parent->left;
							}
							s->color = node->parent->color;
							node->parent->color = BLACK;
							s->left->color = BLACK;
							right_rotation(node->parent);
							node = root;
						}
					}
					node->color = BLACK;
				}
			}

			void transplant(pointer a, pointer b) {
				if (a->parent == senti)
					root = b;
				else if (a == a->parent->left)
					a->parent->left = b;
				else
					a->parent->right = b;
				b->parent = a->parent;
			}

			size_t erase(key_type key) {
				pointer tmp = root;
				pointer x = NULL;
				pointer y = NULL;
				pointer z = NULL;

				iterator it = find(key);

				if (it == end()) // Si on trouve pas l'element return 0 pcq 0 elements effacés du coup
					return 0;

				z = tmp->data;
				y = z;
				int y_original_color = y->color;
				if (z->left == NULL) {
					x = z->right;
					transplant(z, z->right);
				} else if (z->right == NULL) {
					x = z->left;
					transplant(z, z->left);
				} else {
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else {
						transplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}

					transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				//destroy z ? voir quand on aura alloc et tout
				if (y_original_color == BLACK)
					fix_erase(x); // TODO
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
				
				// iterator it(last());
				// ++it;
				// return (it)
			}

			//find/erase========================================================================================

			iterator	find(const key_type& k)
			{
				node<value_type>	*tmp = root;
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
				node<value_type>	*tmp = root;
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