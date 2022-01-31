#ifndef FT_STACK_HPP
#define FT_STACK_HPP

#include <iostream>
#include <deque>
#include "../my_vector/ft_vector.hpp"

//https://en.cppreference.com/w/cpp/container/stack
namespace ft 
{

template< class T, class Container = ft::vector<T> >
// template< class T, class Container = std::deque<T> >
class stack
{
public:
    typedef Container                   container_type;
    typedef T                           value_type;
    typedef size_t                      size_type;
    // typedef typename Container::reference        reference;
    // typedef typename Container::const_reference  const_reference;
protected:
    container_type c;

public:
    explicit stack( const container_type& cont = container_type() ) { this->c = cont;}
    // stack( const stack& other ) { *this = other; }
    ~stack() {}
    stack& operator=( const stack& other ) 
    {
        this->c = other.c;
        return(*this);
    }
    T &top()
    {
        return( this->c.back());
    }
    const T &top() const
    {
        return( this->c.back());
    }
    bool empty() const
    {
        return( this->c.empty());
    }
    size_type size() const
    {
        return(this->c.size());
    }
    void push( const value_type& value )
    {
        this->c.push_back(value);
    }
    void pop()
    {
        this->c.pop_back();
    }

    template <class value_type, class c>
    friend bool operator==(const stack<value_type, c>& lhs, const stack<value_type, c>& rhs);
    
    template <class value_type, class c>
    friend bool operator<(const stack<value_type, c>& lhs, const stack<value_type, c>& rhs);

    template <class value_type, class c>
    friend bool operator>(const stack<value_type, c>& lhs, const stack<value_type, c>& rhs);

};

    template <typename T, typename Container>
    bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.c == rhs.c);
    }

    template <typename T, typename Container>
    bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(lhs == rhs);
    }

    template <typename T, typename Container>
    bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.c < rhs.c);
    }

    template <typename T, typename Container>
    bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return (lhs.c > rhs.c);
    }

    template <typename T, typename Container>
    bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(lhs > rhs);
    }

    template <typename T, typename Container>
    bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
        return !(lhs < rhs);
    }

}

#endif