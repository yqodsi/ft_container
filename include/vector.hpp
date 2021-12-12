#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "ft_container.hpp"

#define nullptr NULL

#define TBARZIT class Alloc = std::allocator<T>
namespace ft
{

    template <class T, TBARZIT>
    class vector
    {
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef size_t size_type;
        // typedef std::size::ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
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
                    _alloc.construct(_arr + i, val);
            }
            else
                _arr = nullptr;
        }

        reference at(size_type n)
        {
            if (n < 0 || n >= _size)
                throw OUT_OF_RANGE();
            return _arr[n];
        }

        reference back() { return (_arr[_size - 1]); }
        const_reference back() const { return (_arr[_size - 1]); }

        reference front() { return (_arr[0]); }
        const_reference front() const { return (_arr[0]); }

        void clear()
        {
            for (size_t i = 0; i < _size; i++)
                _alloc.destroy(_arr + i);
            _size = 0;
        }

        reference operator[](size_type n) { return _arr[n]; }
        const_reference operator[](size_type n) const { return _arr[n]; }

        vector &operator=(const vector &x)
        {
            if (this == &x)
                return *this;

            for (size_t i = 0; i < _size; i++)
                _alloc.destroy(_arr + i);

            _size = x.size();
            if (_capacity < x.size())
            {
                _alloc.deallocate(_arr, _capacity);
                _arr = _alloc.allocate(_size);
                _capacity = _size;
            }
            for (size_t i = 0; i < _size; i++)
                _alloc.construct(_arr + i, x[i]);
            return *this;
        }

        size_type size() const { return _size; }
        size_type capacity() const { return _capacity; }

        bool empty() const { return (_size == 0); }

        void reserve(size_type n)
        {
            if (n <= _capacity)
                return;
            else
            {
                value_type *new_arr = _alloc.allocate(n);
                for (size_t i = 0; i < _size; i++)
                {
                    _alloc.construct(new_arr + i, _arr[i]);
                    _alloc.destroy(_arr + i);
                }
                _alloc.deallocate(_arr, _capacity);
                _arr = new_arr;
                _capacity = n;
            }
        }

        void resize(size_type n, value_type val = value_type())
        {
            if (n < _size)
            {
                for (size_t i = n; i < _size; i++)
                    _alloc.destroy(_arr + i);
            }
            else if (n > _size)
            {
                if (n > _capacity)
                    reserve(n);
                for (size_t i = _size; i < n; i++)
                    _alloc.construct(_arr + i, val);
            }
            _size = n;
        }

        void push_back(const value_type &val)
        {
            if (_size == _capacity)
                reserve(_capacity == 0 ? 1 : _capacity * 2);
            _arr[_size++] = val;
        }

        void pop_back()
        {
            _alloc.destroy(_arr + _size - 1);
            _size--;
        }

    private:
        size_type _size;
        size_type _capacity;
        allocator_type _alloc;
        value_type *_arr;

        class OUT_OF_RANGE : public std::exception
        {
            virtual const char *what() const throw()
            {
                return "wazaaaa";
            }
        };
    };
}

#endif