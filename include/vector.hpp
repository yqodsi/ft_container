#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "ft_container.hpp"

namespace ft
{

    template <class T, class Alloc = std::allocator<T>>
    class vector
    {
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef size_t size_type;
        // typedef std::size::ptrdiff_t difference_type;
        // typedef value_type &reference;
        // typedef const value_type &const_reference;
        // typedef std::allocator_traits<Allocator>::pointer pointer;
        // typedef std::reverse_iterator<iterator> reverse_iterator;
        // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    public:
        explicit vector(const allocator_type &alloc = allocator_type())
            : _size(0), _capacity(0), _alloc(alloc), _arr(nullptr) {}

        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type())
            : _size(n), _capacity(n), _alloc(alloc)
        {
            if (n)
            {
                _arr = _alloc.allocate(n);
                for (size_t i = 0; i < n; i++)
                    _alloc.construct(_arr + i,val);
            }
			else
				_arr = nullptr;
        }

    private:
        size_type _size;
        size_type _capacity;
        allocator_type _alloc;
        value_type *_arr;
    };
}

#endif