#pragma once

#include "iterator_traits.hpp" // include iterator_traits
#include "tree.hpp"

namespace ft {

template <class T, class node_senti>
class	tree_iterator
{
	public:

		typedef typename iterator_traits<T>::value_type			value_type;
		typedef typename iterator_traits<T>::difference_type	difference_type;
		typedef typename iterator_traits<T>::pointer			pointer;
		typedef typename iterator_traits<T>::reference			reference;
		typedef typename iterator_traits<T>::iterator_category	iterator_category;

		pointer		current;
		node_senti	senti;

		// Constructeur=======================================================================================

		tree_iterator() : current(NULL), senti(NULL) {}

		tree_iterator(pointer gang)
		{
			senti = gang;
			while (senti->parent)
			 	senti = senti->parent;
			current = gang;
		}

		template <typename Iterator>
		tree_iterator(const tree_iterator<Iterator, node_senti> other) { current = other.current; senti = other.senti; }

		pointer base() const { return current; }

		// Operateur=========================================================================================

		tree_iterator&	operator=(const tree_iterator& other)
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

		reference	operator*() const { return *(this->current); }

		pointer		operator->() const { return (this->current); }

		// Operateur d'incrementation=====================================================================

		tree_iterator&	operator++()
		{
			current = current->next();
			if (current == NULL)
				current = static_cast<pointer>(senti);
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

		pointer	last()
		{
			pointer tmp = senti->left;
			while (tmp && tmp->right)
				tmp = tmp->right;
			return tmp;			
		}

};












}