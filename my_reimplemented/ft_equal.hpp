#ifndef FT_EQUAL_HPP
#define FT_EQUAL_HPP

#include "iterator_traits.hpp"
#include "../my_iterators/random_access_iterator.hpp"
/*
https://en.cppreference.com/w/cpp/algorithm/equal
Возврат правда если диапазон [first1, last1] равен диапазону [first2, first2 + (last1 - first1)], и ложный иначе
BinaryPredicate p
бинарный предикат, который возвращает правда если элементы следует рассматривать как равные.
Сигнатура функции предиката должна быть эквивалентна следующему:
bool pred ( const Type1 & a , const Type2 & b ) ;
*/
namespace ft
{

template <class T>
struct BinPredP
{
    bool operator()(const T& left, const T& right) const
    {
        return left == right;
    }
};

// template< class InputIt1, class InputIt2 >
// bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
template< class InputIt>
bool equal( InputIt first1, InputIt last1, InputIt first2 )
{
    // for(; first1 != last1; first1++, first2++)
    // {
    //     if(*first1 != *first2)
    //         return(false);
    // }
    // return(true);
    typedef typename ft::iterator_traits<InputIt>::value_type      Iter_type;
    return(equal(first1, last1, first2, BinPredP<Iter_type>()));
}

// template< class InputIt1, class InputIt2, class BinaryPredicate >
// bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
template< class InputIt, class BinaryPredicate >
bool equal( InputIt first1, InputIt last1, InputIt first2, BinaryPredicate p )
{
    for(; first1 != last1; first1++, first2++)
    {
        if(!p(*first1, *first2))
            return(false);
    }
    return(true);
}
}
#endif