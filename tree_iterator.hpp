#pragma once

#include "../vector/iterator_traits.hpp" // include iterator_traits
#include "tree.hpp"

namespace ft {

template <class T>
class	tree_iterator
{
	public:

		typedef typename iterator_traits<T>::value_type			value_type;
		typedef typename iterator_traits<T>::difference_type	difference_type;
		typedef typename iterator_traits<T>::pointer			pointer;
		typedef typename iterator_traits<T>::reference			reference;
		typedef typename iterator_traits<T>::iterator_category	iterator_category;

		pointer		current;
		pointer		root;
		bool		out;

		// Constructeur=======================================================================================

		tree_iterator() : current(NULL), root(NULL) ,out(0) {}

		tree_iterator(pointer gang)
		{
			pointer root = gang;
			while (root->parent)
				root = root->parent;
			current = gang;
			out = 0;
		}

		template <typename Iterator>
		tree_iterator(const tree_iterator<Iterator>& other) { current = other.current; root = other.root; out = other.out; }

		pointer base() const { return current; }

		// Operateur=========================================================================================

		tree_iterator&	operator=(const tree_iterator& other)
		{
			current = other.current;
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

		reference	operator*() const { return *(this->current); }

		pointer		operator->() const { return (this->current); }

		// Operateur d'incrementation=====================================================================

		tree_iterator&	operator++()
		{
			std::cout << "okokoko" << std::endl;
			if (current == last()) //icicicicicicicicicicicicicicicicicicicici
			{
				std::cout << "okokoko" << std::endl;
				++current; 
			}
			else
				current = current->next();
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
			if (current == (last().current)++)
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

		pointer	last()
		{
			pointer tmp = root;
			while (tmp->right)
				tmp = tmp->right;
			return tmp;			
		}

};












}