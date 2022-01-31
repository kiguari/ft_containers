#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

/*
    https://en.cppreference.com/w/cpp/iterator/iterator_traits
    на сайте указано 2 шаблона:
    template< class Iter >
    struct iterator_traits;

    template< class T >
    struct iterator_traits<T*>;

    https://code.woboq.org/gcc/libstdc++-v3/include/bits/stl_iterator_base_types.h.html
    соурс код итератор трейтс
*/

namespace ft
{

    template<class T> 
    struct remove_const
    { 
        typedef T type; 
    };

    template<class T> 
    struct remove_const <const T> 
    { 
        typedef T type;
    };


    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template <class C, class T, class Dist = std::ptrdiff_t, class Pt = T*, class Rt = T&>
    struct iterator {
        typedef C                                   iterator_category;
        typedef T                                   value_type;
        typedef Dist                                difference_type;
        typedef Pt                                  pointer;
        typedef Rt                                  reference;
        
    };

    template< class Iter >
    struct iterator_traits
    {
        typedef typename Iter::iterator_category    iterator_category;
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::pointer              pointer;
        typedef typename Iter::reference            reference;
    };

    template< class T >
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag          iterator_category;
        typedef T                                   value_type;
        typedef std::ptrdiff_t                      difference_type;
        // https://www.cplusplus.com/reference/cstddef/ptrdiff_t/
        typedef T*                                  pointer;
        typedef T&                                  reference;
    };

    template< class T >
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag          iterator_category;
        typedef T                                   value_type;
        typedef std::ptrdiff_t                      difference_type;
        // https://www.cplusplus.com/reference/cstddef/ptrdiff_t/
        typedef const T*                            pointer;
        typedef const T&                            reference;
    };
}
#endif