#pragma once

#include <functional>
#include "pair.hpp"
#include <iostream>
#include "tree.hpp"

#include "utils.hpp"

namespace ft {

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator <ft::pair <const Key, T> > > // std::pair a faire
	class map
	{
		public:

			typedef Key																								key_type;
			typedef T																								mapped_type;
			typedef ft::pair<const Key, T>																			value_type;

			template <class Comparo>
				struct Compa
				{
					private:
						Comparo	comp;

					public:
							Compa() {}

							bool operator() (const value_type& x, const value_type& y) const {
								return comp(x.first, y.first);
							}
				};





			typedef 			std::size_t																								size_type;
			typedef 			std::ptrdiff_t																							difference_type;
			typedef				Compare																									key_compare;
			typedef 			Compa<Compare>																							value_compare;
			typedef 			Alloc																									allocator_type;
			typedef 			value_type&																								reference;
			typedef const 		value_type&																								const_reference;
			typedef typename 	Alloc::pointer																							pointer;
			typedef typename 	Alloc::const_pointer																					const_pointer;
			typedef typename 	RBtree<value_type, key_compare, value_compare>::iterator												iterator;		
			typedef typename 	RBtree<value_type, key_compare, value_compare>::const_iterator											const_iterator;


			// typedef ft::reverse_iterator<iterator>			reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			RBtree<value_type, key_compare, value_compare>					_tree;
	 	private:
		 
			allocator_type													_alloc;
			size_type														_size;
			key_compare														_compare;

		public:

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _compare(comp) {}

			template <class InputIt>
			map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) // gang ... enableif ?
			{
				insert(first, last);
			}

			map (const map& x) : _alloc(x._alloc), _compare(key_compare()), _tree(x._tree) {
			}

			~map() {
				clear();
				_tree._alloc.destroy(_tree.senti);
				_tree._alloc.deallocate(_tree.senti, sizeof(_tree.senti));
			}

			map&	operator=(const map& x)
			{
				clear();
				insert(x.begin(), x.end());
			}

			//Iterators=======================================================================================================

			iterator		begin() { return _tree.begin(); }

			const_iterator	begin() const { return _tree.begin(); }

			iterator	end() { return _tree.end(); }

			iterator	end() const { return _tree.end(); }

		
			//Modifiers=======================================================================================================

			ft::pair<iterator, bool>	insert (const value_type& value)
			{
				ft::pair<iterator, bool>	ret;

				if (find(value.first) != end()) {
					ret.first = _tree.find(value.first);
					ret.second = false;
					return ret;
				}
				_size++;
				ret.first = _tree.insert(value);
				ret.second = true;
				return ret;
			}

			iterator insert (iterator position, const value_type& value)
			{
				ft::pair<iterator, bool>	ret;
				iterator it = find(value.first);

				if (it != end())
					return it;
				_size++;
				return _tree.insert(position.current, value);
			}

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last) {
				while (first != last) {
	  				insert(*first);
	  				++first;
				}
  			}

			void erase (iterator position) {
				_size -= _tree.erase(position.current->data.first);
			}

			size_type erase (const key_type& k) {
				if (find(k) == end())
					return 0;
				_size--;
				return _tree.erase(k);
			}

			void erase (iterator first, iterator last) {
				while (first != last) {
					_size -= _tree.erase(first.current->data.first);
					first++;
				}
			}

			void swap (map& x) {
				std::swap(_tree, x._tree);
				std::swap(_size, x._size);
				std::swap(_compare, x._compare);
			}

			void clear() {
				_tree.clear();
				_size = 0;
			}
			

			//Capacity=======================================================================================================

			bool		empty() const{ return _size == 0; }
			size_type	size() const { return _size; }
			size_type	max_size() const { return _tree.max_size(); }

			//Element access=======================================================================================================

			mapped_type& operator[] (const key_type& k) {
				iterator it = find(k);
				if (it == end())
					it = insert(value_type(k, mapped_type())).first;
				return it.current->data.second;
			}

			//Observers=======================================================================================================

			key_compare		key_comp() const { return _compare; }
			value_compare	value_comp() const { return value_compare(_compare); }

			//Operations=======================================================================================================

			iterator find(const key_type& k)
			{
				return _tree.find(k);
			}

			const_iterator find(const key_type& k) const
			{
				return _tree.find(k);
			}

			size_type count (const key_type& k) const
			{
				if (_tree.find(k) == _tree.end())
					return 0;
				return 1;
			}

			iterator lower_bound (const key_type& k)
			{
				return _tree.lower_bound(k);
			}

			const_iterator lower_bound (const key_type& k) const
			{
				return _tree.lower_bound(k);
			}

			iterator upper_bound (const key_type& k)
			{
				return _tree.upper_bound(k);
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return _tree.upper_bound(k);
			}

			ft::pair<iterator, iterator> equal_range (const key_type& k)
			{
				return _tree.upper_bound(k);
			}

			//Allocator=======================================================================================================

			allocator_type get_allocator() const { return _alloc; }
	};

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}