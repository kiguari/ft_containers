#ifndef FT_IS_INTEGRAL_HPP
#define FT_IS_INTEGRAL_HPP

#include <iostream>
// #include <type_traits>

namespace ft
{
template< class T >
struct is_integral
{
    static const bool res = false;
    // static const void message()
    // {
    //     std::cout << "ft_is_integral dont know this type" << std::endl;
    // }
};

// template<>
// struct is_integral<bool>
// {
//     static const bool res = true;
// };
template<>
struct is_integral<char>
{
    static const bool res = true;
    // static const void message()
    // {
    //     std::cout << "ft_is_integral know this type - char" << std::endl;
    // }
};
template<>
struct is_integral<wchar_t>
{
    static const bool res = true;
};
template<>
struct is_integral<short>
{
    static const bool res = true;
};
template<>
struct is_integral<int>
{
    static const bool res = true;
};
template<>
struct is_integral<long>
{
    static const bool res = true;
};
template<>
struct is_integral<long long>
{
    static const bool res = true;
};
template<>
struct is_integral<signed char>
{
    static const bool res = true;
};
template<>
struct is_integral<unsigned char>
{
    static const bool res = true;
};
template<>
struct is_integral<unsigned short int>
{
    static const bool res = true;
};
template<>
struct is_integral<unsigned int>
{
    static const bool res = true;
};
template<>
struct is_integral<unsigned long int>
{
    static const bool res = true;
};
template<>
struct is_integral<unsigned long long int>
{
    static const bool res = true;
};
}

#endif