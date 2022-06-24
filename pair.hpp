#pragma once

namespace ft {

template <class T1, class T2>
struct  pair
{
	/* private: */

	public:

		typedef T1	first_type;
		typedef T2	second_type;

		T1	first;
		T2	second;

	public:

		pair() : first(first_type()), second(second_type()) {}

		pair(const T1& x, const T2& y) { first = x; second = y; }

		template <class U1, class U2>
		pair(const pair <U1, U2>& p) : first(p.first), second(p.second) {}

		pair&	operator=(pair& pr) { first = pr.first; second = pr.second; return *this; }

};

template <class T1, class T2>
bool	operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (lhs._first == rhs._first && lhs._second == rhs._second); }

template <class T1, class T2>
bool	operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs == rhs); }

template <class T1, class T2>
bool	operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

template <class T1, class T2>
bool	operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs<lhs); }

template <class T1, class T2>
bool	operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs<lhs; }

template <class T1, class T2>
bool	operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs<rhs); }

template <class T1, class T2>
pair<T1,T2>	make_pair(T1 x, T2 y) { return (pair<T1,T2>(x,y)); }

}