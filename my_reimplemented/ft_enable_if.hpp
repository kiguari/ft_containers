#ifndef FT_ENABLE_IF_HPP
#define FT_ENABLE_IF_HPP

namespace ft
{
template< bool B, class T = void >
struct ft_enable_if
{};

template<class T>
struct ft_enable_if<true, T>
{
    typedef T       type;
};
};

#endif