#ifndef FT_LEXICOGRAPHICAL_COMPARE_HPP
#define FT_LEXICOGRAPHICAL_COMPARE_HPP

#include "iterator_traits.hpp"
#include "../my_iterators/random_access_iterator.hpp"
/*
Проверяет, соответствует ли первый диапазон [ first1, last1] лексикографически меньше второго диапазона [ first2, last2 ].
1) Элементы сравниваются с помощью operator<.
3) Элементы сравниваются с использованием заданной функции двоичного сравнения comp.

Лексикографическое сравнение - это операция со следующими свойствами:
Два диапазона сравниваются поэлементно.
Первый элемент несовпадения определяет, какой диапазон лексикографически меньше или больше другого.
Если один диапазон является префиксом другого, более короткий диапазон лексикографически меньше другого.
Если два диапазона имеют эквивалентные элементы и имеют одинаковую длину, тогда диапазоны лексикографически равны .
Пустой диапазон лексикографически меньше любого непустого диапазона.
Два пустых диапазона лексикографически равны .

объект функции сравнения (то есть объект, который удовлетворяет требованиям Compare ), который возвращаетправдаесли первый аргумент меньше второго.
Сигнатура функции сравнения должна быть эквивалентна следующему:

bool cmp ( const Type1 & a , const Type2 & b ) ;
*/

namespace ft
{

template <class T>
struct CompareComp
{
    bool operator()(const T& left, const T& right) const
    {
        return left < right;
    }
};

// template< class InputIt1, class InputIt2 >
// bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
template< class InputIt >
bool lexicographical_compare( InputIt first1, InputIt last1, InputIt first2, InputIt last2 )
{
    typedef typename ft::iterator_traits<InputIt>::value_type      Iter_type;
    return(lexicographical_compare(first1, last1, first2, last2, CompareComp<Iter_type>()));
    // size_t size1 = 0;
    // size_t size2 = 0;
    // size_t count = 0;
    // int flag = 0;
    // int flag_equal = 0;
    // InputIt first1_tmp = first1;
    // InputIt first2_tmp = first2;
    // for(; first1_tmp != last1; first1_tmp++)
    //     size1++;
    // for(; first2_tmp != last2; first2_tmp++)
    //     size2++;  
    // if(size1 > size2)
    // {
    //     count = size1;
    //     flag = 1;
    // }
    // else
    //     count = size2;
    // // чек на то что они равны
    // if(size1 == size2)
    // {
    //     first1_tmp = first1;
    //     first2_tmp = first2;
    //     for(; first1 != last1; first1++, first2++)
    //     {
    //         if(*first1 != *first2)
    //             flag_equal = 1;
    //     }
    //     if(flag_equal == 0)
    //         return(false);
    // }
    // else if(flag_equal)
    // {
    //     for(size_t i = 0; i < count; i++, first1++, first2++)
    //     {
    //         if(*first1 > *first2)
    //             return(false);
    //         if(i == size2 && !flag && (size1 > size2))
    //             return(false);
    //         if(i == size1 && flag && (size1 < size2))
    //             return(true);
    //     }
    // }
    // return(true);
}


template< class InputIt, class Compare >
bool lexicographical_compare( InputIt first1, InputIt last1, InputIt first2, InputIt last2, Compare comp )
{
    size_t size1 = 0;
    size_t size2 = 0;
    size_t count = 0;
    int flag = 0;
    int flag_equal = 0;
    InputIt first1_tmp = first1;
    InputIt first2_tmp = first2;
    for(; first1_tmp != last1; first1_tmp++)
        size1++;
    for(; first2_tmp != last2; first2_tmp++)
        size2++;  
    if(size1 > size2)
    {
        count = size1;
        flag = 1;
    }
    else
        count = size2;
    // чек на то что они равны
    if(size1 == size2)
    {
        first1_tmp = first1;
        first2_tmp = first2;
        for(; first1 != last1; first1++, first2++)
        {
            if(*first1 != *first2)
                flag_equal = 1;
        }
        if(flag_equal == 0)
            return(false);
    }
    else if(flag_equal)
    {
        for(size_t i = 0; i < count; i++, first1++, first2++)
        {
            if(!(comp(*first1, *first2)))
                return(false);
            // if(*first1 > *first2)
                // return(false);
            if(i == size2 && !flag && (size1 > size2))
                return(false);
            if(i == size1 && flag && (size1 < size2))
                return(true);
        }
    }
    return(true);
}
}

#endif