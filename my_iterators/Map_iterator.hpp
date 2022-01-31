#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "../my_reimplemented/pair.hpp"
#include "../my_map/knots.hpp"

namespace ft
{
template <typename Pair>
class Map_biderection_iterator
{
public:
    typedef Pair                                value_type;
    typedef Pair&                               reference;
    typedef ft::knots<value_type>*		        pointer;
    typedef std::ptrdiff_t                           difference_type;
    typedef std::bidirectional_iterator_tag     iterator_category;

protected:
    pointer _ptr;

public:
    Map_biderection_iterator()
    {
        this->_ptr = NULL;
    }
    Map_biderection_iterator(const pointer new_ptr)
    {
        this->_ptr = new_ptr;
    }
    Map_biderection_iterator(const Map_biderection_iterator &other)
    {
        *this = other;
    }
    Map_biderection_iterator &operator=(const Map_biderection_iterator &other)
    {
        this->_ptr = other._ptr;
        return(*this);
    }
    Map_biderection_iterator &operator++()
    {
        if (_ptr == NULL)
        {
            return (*this);
        }
        else
        {
            if (_ptr->right == NULL)
            {
                pointer tmp_parent = _ptr->parent;
                while (tmp_parent && _ptr == tmp_parent->right)
                {
                    _ptr = tmp_parent;
                    tmp_parent = tmp_parent->parent;
                }
                _ptr = tmp_parent;
            } 
            else 
            {
                _ptr = _ptr->right;
                while (_ptr && _ptr->left != NULL)
                    _ptr = _ptr->left;
            }
        }
        return (*this);
    }
    Map_biderection_iterator operator++(int) 
    {
        Map_biderection_iterator tmp(*this);
        operator++();
        return (tmp);
    }
    Map_biderection_iterator &operator--()
    {
        if (_ptr == NULL)
        {
            return (*this);
        }
        else
        {
            if (_ptr->left == NULL)
            {
                pointer tmp_parent = _ptr->parent;
                while (tmp_parent && _ptr == tmp_parent->left)
                {
                    _ptr = tmp_parent;
                    tmp_parent = tmp_parent->parent;
                }
                _ptr = tmp_parent;
            } 
            else 
            {
                _ptr = _ptr->left;
                while (_ptr && _ptr->right != NULL)
                    _ptr = _ptr->right;
            }
        }
        return (*this);
    }
    Map_biderection_iterator operator--(int) 
    {
        Map_biderection_iterator tmp(*this);
        operator--();
        return (tmp);
    }
    value_type *operator->()
    {
        return(&this->_ptr->_pair);
    }
    value_type &operator*()
    {
        return(this->_ptr->_pair);
    }
    bool operator!=(const Map_biderection_iterator &rhs) const 
    {
        return (this->_ptr != rhs._ptr);
    }
    bool operator==(const Map_biderection_iterator &rhs) const 
    {
        return (this->_ptr == rhs._ptr);
    }
};

template <typename Pair>
class Map_biderection_iterator_rev
{
public:
    typedef Pair                                        value_type;
    typedef Pair&                                       reference;
    typedef ft::knots<value_type>*		                pointer;
    typedef std::ptrdiff_t                              difference_type;
    typedef std::bidirectional_iterator_tag             iterator_category;

protected:
    pointer _ptr;    
public:
    Map_biderection_iterator_rev()
    {
        this->_ptr = NULL;
    }
    Map_biderection_iterator_rev(const pointer new_ptr)
    {
        this->_ptr = new_ptr;
    }
    Map_biderection_iterator_rev(const Map_biderection_iterator_rev &other)
    {
        *this = other;
    }
    Map_biderection_iterator_rev &operator=(const Map_biderection_iterator_rev &other)
    {
        this->_ptr = other._ptr;
        return(*this);
    }
    Map_biderection_iterator_rev &operator++()
    {
        if (_ptr == NULL)
        {
            return (*this);
        }
        else
        {
            if (_ptr->left == NULL)
            {
                pointer tmp_parent = _ptr->parent;
                while (tmp_parent && _ptr == tmp_parent->left)
                {
                    _ptr = tmp_parent;
                    tmp_parent = tmp_parent->parent;
                }
                _ptr = tmp_parent;
            } 
            else 
            {
                _ptr = _ptr->left;
                while (_ptr && _ptr->right != NULL)
                    _ptr = _ptr->right;
            }
        }
        return (*this);
    }
    Map_biderection_iterator_rev operator++(int) 
    {
        Map_biderection_iterator_rev tmp(*this);
        operator++();
        return (tmp);
    }
    Map_biderection_iterator_rev &operator--()
    {
        if (_ptr == NULL)
        {
            return (*this);
        }
        else
        {
            if (_ptr->right == NULL)
            {
                pointer tmp_parent = _ptr->parent;
                while (tmp_parent && _ptr == tmp_parent->right)
                {
                    _ptr = tmp_parent;
                    tmp_parent = tmp_parent->parent;
                }
                _ptr = tmp_parent;
            } 
            else 
            {
                _ptr = _ptr->right;
                while (_ptr && _ptr->left != NULL)
                    _ptr = _ptr->left;
            }
        }
        return (*this);
    }
    Map_biderection_iterator_rev operator--(int) 
    {
        Map_biderection_iterator_rev tmp(*this);
        operator--();
        return (tmp);
    }
    value_type *operator->()
    {
        return(&this->_ptr->_pair);
    }
    value_type &operator*()
    {
        return(this->_ptr->_pair);
    }
    bool operator!=(const Map_biderection_iterator_rev &rhs) const 
    {
        return (this->_ptr != rhs._ptr);
    }
};
}

#endif