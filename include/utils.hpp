#ifndef UTILS_HPP
#define UTILS_HPP


namespace ft{
	template <typename T>
	// T min(T a, T b)
	typename ft::enable_if<ft::is_integral<T>::value, T>::type min(T a, T b)
	{
		return (a < b ? a : b);
	}
}

#endif