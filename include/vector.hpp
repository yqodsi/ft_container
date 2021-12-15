#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "ft_container.hpp"

#ifndef nullptr
#define nullptr NULL
#endif

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
        typedef typename allocator_type::pointer pointer; // T*

        // typedef std::reverse_iterator<iterator> reverse_iterator;
        // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    public:
        struct iterator
        {
            iterator(value_type *ptr = nullptr) : m_ptr(ptr) {}
            ~iterator() {}
            iterator &operator=(iterator const &other)
            {
                if (*this == other)
                    return (*this);
                m_ptr = other.m_ptr;
                return (*this);
            }
            reference operator*() const { return *m_ptr; }
            pointer operator->() { return m_ptr; }
            reference operator[](size_type index) { return m_ptr[index]; }

            iterator &operator++()
            {
                m_ptr++;
                return *this;
            }
            iterator operator++(int)
            {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            iterator &operator--()
            {
                m_ptr--;
                return *this;
            }
            iterator operator--(int)
            {
                iterator tmp = *this;
                --(*this);
                return tmp;
            }

            iterator operator+(size_type index) { return iterator(m_ptr + index); }
            iterator operator-(size_type index) { return iterator(m_ptr - index); }
            size_type operator-(iterator it) { return (m_ptr - it.m_ptr); }

            bool operator==(const iterator &other) { return m_ptr == other.m_ptr; };
            bool operator!=(const iterator &other) { return m_ptr != other.m_ptr; };
            bool operator<(const iterator &other) { return m_ptr < other.m_ptr; };
            bool operator>(const iterator &other) { return m_ptr > other.m_ptr; };
            bool operator<=(const iterator &other) { return m_ptr <= other.m_ptr; };
            bool operator>=(const iterator &other) { return m_ptr >= other.m_ptr; };

        private:
            value_type *m_ptr;
        };
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

        iterator begin() { return iterator(_arr); }
        iterator end() { return iterator(_arr + _size); }

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
                    reserve(_capacity * 2); // linux reserve (n)
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

        void insert(iterator position, size_type n, const value_type &val)
        {
            if (n == 0)
                return;
            size_t shift_size = this->end() - position;        // the size behind the position
            size_t insert_position = position - this->begin(); // get_the index
            if (_size + n >= _capacity)
            {
                size_t i = 0;
                _capacity = _capacity * 2;
                if (_capacity < _size + n)
                    _capacity = _size + n;
                value_type *new_arr = _alloc.allocate(_capacity);
                // copy old data before the insert position
                for (i = 0; i < insert_position; i++)
                    _alloc.construct(new_arr + i, _arr[i]);

                for (size_t j = 0; j < n; j++)
                    _alloc.construct(new_arr + i++, val);

                for (; insert_position < _size; insert_position++)
                    _alloc.construct(new_arr + i++, _arr[insert_position]);

                for (size_t j = 0; j < _size; j++)
                    _alloc.destroy(_arr + j);

                _alloc.deallocate(_arr, _capacity);
                _arr = new_arr;
            }
            else
            {
                for (size_t i = 1; i <= shift_size; i++)
                    _alloc.construct(_arr + _size + n - i, _arr[_size - i]);
                for (size_t i = 0; i < n; i++)
                {
                    _alloc.destroy(_arr + insert_position);
                    _alloc.construct(_arr + insert_position, val);
                    insert_position++;
                }
            }
            _size += n;
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