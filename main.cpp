#include "ft_container.hpp"
#include <vector>
#include <string>
#include <iostream>
#ifndef TL
#define TL std
#endif

template <typename T>
void print_vector(TL::vector<T> const &v, std::string dil = " ")
{
    std::cout << "s = " << v.size() << ", c = " << v.capacity() << "\t";
    if (v.size())
    {
        for (size_t i = 0; i < v.size(); i++)
        {
            std::cout << v[i] << dil;
        }
    }
    std::cout << std::endl;
}

template <typename T>
void print_value(T const &val)
{
    std::cout << val << std::endl;
}

int main(int argc, char const *argv[])
{
    try
    {
        TL::vector<int> v1(3, 4);
        v1.push_back(6);
        v1.push_back(11);
        v1.push_back(12);
        v1.push_back(13);
        print_vector(v1);
        v1.resize(17, 33);
        print_vector(v1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
