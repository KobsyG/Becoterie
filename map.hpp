#pragma once

#include <functional>
#include "pair.hpp"
#include <iostream>
#include "tree.hpp"
#include "../iterator.hpp"
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
			typedef typename 	ft::reverse_iterator<iterator> 																			reverse_iterator;
			typedef typename 	ft::reverse_iterator<const_iterator> 																	const_reverse_iterator;


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

			map (const map& x) : _alloc(x._alloc), _compare(key_compare()), _tree(x._tree), _size(x._size) {
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

			reverse_iterator rbegin() {
				return reverse_iterator(end());
			}

			reverse_iterator rend() {
				return reverse_iterator(begin());
			}


		
			//Modifiers=======================================================================================================

			ft::pair<iterator, bool>	insert (const value_type& value)
			{
				if (find(value.first) != end()) 
					return ft::make_pair(find(value.first), false);
					
				const ft::pair<iterator, bool>	ret = _tree.insert(value);

				if (ret.second)
					_size++;
				return ret;
			}

			iterator insert (iterator position, const value_type& value)
			{
				if (begin() == end())
					return(insert(value).first);
				else if (position == end())
					position--;
				ft::pair<iterator, bool> ret;
				iterator tmp = position;
				iterator same = find(value.first);
				if (same != end())
					return (same);
				if (_compare(value.first, position->first)) {
					tmp--;
					while (tmp.current && _compare(value.first, tmp->first)) {
						tmp--;
						position--;
					}
				}
				else {
					tmp++;
					while (tmp != end() && !_compare(value.first, tmp->first)) {
						tmp++;
						position++;
					}
				}
				ret = _tree.insert(value, position.current);
				if (ret.second)
					_size++;
				return ret.first;
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
					iterator next = first;
					next++;
					_size -= _tree.erase(first.current->data.first);
					first = next;
				}
			}

			void swap (map& x) {
				std::swap(_size, x._size);
				std::swap(_tree.root, x._tree.root);
				std::swap(_tree.senti, x._tree.senti);
				std::swap(_compare, x._compare);
				std::swap(_alloc, x._alloc);
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

			mapped_type& at (const key_type& k) {
				iterator it = find(k);
				if (it == end())
					throw std::out_of_range("map::at");
				return it.current->data.second;
			}

			const mapped_type& at (const key_type& k) const {
				iterator it = find(k);
				if (it == end())
					throw std::out_of_range("map::at");
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

			ft::pair<iterator, iterator> equal_range(const key_type& key) {
				return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
				return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
			}

			//Allocator=======================================================================================================

			allocator_type get_allocator() const { return _alloc; }
	};

	//Comparison operators=================================================================================================

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator==(const map<_Key, _Tp, _Compare, _Alloc>& _l, const map<_Key, _Tp, _Compare, _Alloc>& _r) { return _l.size() == _r.size() && _l._tree == _r._tree; }

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator<(const map<_Key, _Tp, _Compare, _Alloc>& _l, const map<_Key, _Tp, _Compare, _Alloc>& _r) {
		return _l._tree < _r._tree;
	}

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator!=(const map<_Key, _Tp, _Compare, _Alloc>& _l,const map<_Key, _Tp, _Compare, _Alloc>& _r) { return !(_l == _r); }

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator>(const map<_Key, _Tp, _Compare, _Alloc>& _l, const map<_Key, _Tp, _Compare, _Alloc>& _r) {
		return _r < _l;
	}

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator<=(const map<_Key, _Tp, _Compare, _Alloc>& _l, const map<_Key, _Tp, _Compare, _Alloc>& _r) { return !(_r < _l); }

	template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
	bool operator>=(const map<_Key, _Tp, _Compare, _Alloc>& _l, const map<_Key, _Tp, _Compare, _Alloc>& _r) { return !(_l < _r); }

	//Swap==================================================================================================================

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}