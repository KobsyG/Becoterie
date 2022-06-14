#pragma once

#include <functional>
#include "pair.hpp"
#include <iostream>
#include "map_iterator.hpp"
#include "tree.hpp"
#include "tree_iterator.hpp"

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





		typedef std::size_t																						size_type;
		typedef std::ptrdiff_t																					difference_type;
		typedef	Compare																							key_compare;
		typedef Compa<Compare>																					value_compare;
		typedef Alloc																							allocator_type;
		typedef value_type&																						reference;
		typedef const value_type&																				const_reference;
		typedef typename Alloc::pointer																			pointer;
		typedef typename Alloc::const_pointer																	const_pointer;
		typedef map_iterator<pointer, typename RBtree<value_type, key_compare, value_compare, allocator_type>::iterator >		iterator;		
		typedef map_iterator<const_pointer, typename RBtree<value_type, key_compare, value_compare, allocator_type>::iterator>	const_iterator;


		// typedef ft::reverse_iterator<iterator>			reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

/* 	private: */

		// pointer			c; // gang ... noeud

		RBtree<value_type, key_compare, value_compare ,allocator_type>	tree;
		allocator_type													_alloc;
		size_type														_size;
		key_compare														_compare;

	public:

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _compare(comp) {}

		// template <class InputIt>
		// map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) // gang ... enableif ?
		// {

		// }

		~map() {} // destroy/deallocate

		// map&	operator=(const map& x)
		// {

		// }

		//Iterators=======================================================================================================

		iterator		begin() { return iterator(tree.begin()); }

		const_iterator	begin() const { return const_iterator(tree.begin()); }

		iterator	end() { return iterator(tree.end()); }

	
		//Modifiers=======================================================================================================

		/* ft::pair<iterator, bool> */void	insert(const value_type& value) // gang ... changer pointer par iterator
		{
			// gang ... check if key already exist
			tree.insert(value);
		}

		void insert (iterator position, const value_type& val) {
			tree.insert(position.current, val);
		 //gang ... return un iterator à l'endroit ou il a ete inseré ou l'endroit ou il existe déjà
		}

		// template<class InputIterator>
		// void	insert(InputIterator first, InputIterator last)
		// {
			
		// }

		//Capacity=======================================================================================================

		bool	empty() const
		{
			if (_size == 0)
				return true;
			return false;
		}

		size_type	size() const { return _size; }





		//Operations=======================================================================================================

		iterator find(const key_type& k)
		{
			return iterator(tree.find(k));
		}

		const_iterator find(const key_type& k) const
		{
			return const_iterator(tree.find(k));
		}







};

}