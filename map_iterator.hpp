#pragma once

#include "../vector/iterator_traits.hpp" // include iterator_traits

namespace ft {

template <class Value, class Tree_iterator>
class	map_iterator
{
	public:

		typedef typename iterator_traits<Value>::value_type			value_type;
		typedef typename iterator_traits<Value>::pointer			pointer;
		typedef typename iterator_traits<Value>::reference			reference;
		typedef typename iterator_traits<Value>::difference_type	difference_type;
		typedef typename iterator_traits<Value>::iterator_category	iterator_category;

		Tree_iterator current;

		// Constructeur=======================================================================================

		map_iterator() { current = NULL; }

		map_iterator(Tree_iterator gang) { current = gang; }

		template <typename Iterator>
		map_iterator(const map_iterator<Value, Iterator>& other) { current = other.current; }

		pointer base() const { return current; }

		// Operateur=========================================================================================

		map_iterator&	operator=(const map_iterator& other)
		{
			current = other.current;
			return (*this);
		}

		// Operateur de comparaison==========================================================================

		bool	operator==(const map_iterator & other) const { return (this->current == other.current); }

		bool	operator!=(const map_iterator & other) const { return (this->current != other.current); }

		bool	operator<(const map_iterator & other) const
		{
			if ( this->current < other.current)
				return true;
			return false;
		}

		bool	operator>(const map_iterator & other) const
		{
			if ( this->current > other.current)
				return true;
			return false;
		}

		bool	operator<=(const map_iterator & other) const
		{
			if ( this->current <= other.current)
				return true;
			return false;
		}

		bool	operator>=(const map_iterator & other) const
		{
			if ( this->current >= other.current)
				return true;
			return false;
		}

		// Operateur de dereferencement====================================================================

		reference	operator*() const { return (*current).data; } // .data pour bien renvoyer la paire

		pointer		operator->() const { return &(*current).data	; }

		// Operateur d'incrementation=====================================================================

		map_iterator&	operator++()
		{
			++current;
			return *this;
		}

		map_iterator	operator++(int)
		{
			map_iterator	tmp = *this;
			++*this;
			return (tmp);
		}

		// // Operateur de decrementation=====================================================================

		map_iterator&	operator--()
		{
			--current;
			return *this;
		}

		map_iterator	operator--(int)
		{
			map_iterator	tmp = *this;
			--*this;
			return tmp;
		}

};












}