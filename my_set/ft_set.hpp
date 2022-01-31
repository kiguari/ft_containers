#ifndef FT_SET_HPP
#define FT_SET_HPP

#include <functional>
#include "../my_reimplemented/pair.hpp"
#include <iostream>
#include "../my_iterators/Map_iterator.hpp"
#include "knots.hpp"

#include "../my_reimplemented/ft_is_integral.hpp"
#include "../my_reimplemented/ft_lexicographical_compare.hpp"
#include "../my_reimplemented/ft_equal.hpp"
#include "../my_reimplemented/ft_enable_if.hpp"

#include "../my_reimplemented/ft_lexicographical_compare.hpp"
/*
https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
using this for check my red black tree, thx for this
*/

namespace ft
{
template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key> >
class set
{
public:
    typedef Key                                                 key_type;
    typedef Key                                                 value_type;
    typedef size_t                                              size_type;
    typedef std::ptrdiff_t                                      difference_type;
    typedef Compare                                             key_compare;
    typedef Compare                                             value_compare;

    typedef Allocator                                           allocator_type;
    typedef value_type&                                         reference;
    typedef const value_type&                                   const_reference;
    // typedef typename Allocator::pointer                         pointer;
    // typedef typename Allocator::const_pointer                   const_pointer;

    typedef ft::Map_biderection_iterator<value_type>            iterator;
    typedef ft::Map_biderection_iterator<value_type>            const_iterator;
    typedef ft::Map_biderection_iterator_rev<value_type>        reverse_iterator;
    typedef ft::Map_biderection_iterator_rev<const value_type>  const_reverse_iterator;
    
    typedef ft::knots<key_type>                                 knot;
    typedef typename Allocator::template rebind<knot>::other    node_alloc_type;

    // Member classes
    // https://www.cplusplus.com/reference/map/map/value_comp/
    // std::map::value_compare- это функциональный объект, 
    // который сравнивает объекты типа std::map::value_type(пары ключ-значение) 
    // путем сравнения первых компонентов пар.
    // class value_compare
    // {
    //     friend class map; // прочитать про friend класс
    // protected:
    //     Compare     comp;
    //     value_compare(Compare c) : comp(c) {}
    // public:
    //     typedef bool        result_type;
    //     typedef value_type  first_argument_type;
    //     typedef value_type  second_argument_type;
    //     bool operator() (const value_type &x, const value_type &y) const
    //     {
    //         return comp(x.first, y.first);
    //     }
    // };
private:
    node_alloc_type _Alloc;
    knot            *_knot;
    knot            *_tree_root;
    size_t          _size;
    knot            *last_tmp_knot;
    knot            *first_tmp_knot;
    key_compare     _comp;
    
    template <typename U>
    void swap(U& a, U& b)
    {
        U tmp = a;
        a = b;
        b = tmp;
    }
public:

    // void test_show_tree()
    // {
    //     printTreeHelper(this->_tree_root, 0);
    // }

    set()
    {
        this->last_tmp_knot = NULL;
        this->_tree_root = NULL;
        this->_size = 0;
        this->_knot = NULL;
    }

    explicit set( const Compare& compp, const Allocator& alloc = Allocator() ) : _Alloc(alloc), _comp(compp)
    {
        this->last_tmp_knot = NULL;
        this->_tree_root = NULL;
        this->_size = 0;
        this->_knot = NULL;
    }

    template< class InputIt >
    set( InputIt first, InputIt last, const Compare& compp = Compare(), const Allocator& alloc = Allocator() ) : _Alloc(alloc), _comp(compp)
    {
        this->last_tmp_knot = NULL;
        this->_tree_root = NULL;
        this->_size = 0;
        this->_knot = NULL;
        for(; first != last; first++)
        {
            if(insert_to_tree(*first))
                this->_size += 1;
        }
    }

    set( const set& other )
    {
        this->last_tmp_knot = NULL;
        this->_tree_root = NULL;
        this->_size = 0;
        this->_knot = NULL;
        if(other.size())
        {
            const_iterator tmp_oteher = other.begin();
            const_iterator tmp_oteher_end = other.end();
            for (; tmp_oteher != tmp_oteher_end; tmp_oteher++)
            {
                if(insert_to_tree(*tmp_oteher))
                    this->_size += 1;
            }
        }
    }

    ~set()
    {
        if(this->_tree_root != NULL)
            delete_tree(this->_tree_root);
    }

    set& operator=( const set& other )
    {
        if(this->_tree_root)
            this->clear();
        if(other.size())
        {
            const_iterator tmp_oteher = other.begin();
            const_iterator tmp_oteher_end = other.end();
            for (; tmp_oteher != tmp_oteher_end; tmp_oteher++)
            {
                if(insert_to_tree(*tmp_oteher))
                    this->_size += 1;
            }
        }
        return(*this);
    }

    allocator_type get_allocator() const
    {
        return(_Alloc);
    }

    iterator begin()
    {
        if(this->_tree_root != NULL)
        {
            return(found_min_knot(this->_tree_root));
        }
        return (NULL);
    }

    const_iterator begin() const
    {
        if(this->_tree_root != NULL)
        {
            return(found_min_knot(this->_tree_root));
        }
        return (NULL);
    }

    iterator end()
    {
        if(this->_tree_root != NULL)
        {
            return(this->last_tmp_knot);
        }
        return(NULL);
    }

    const_iterator end() const
    {
        if(this->_tree_root != NULL)
        {
            return(this->last_tmp_knot);
        }
        return(NULL);
    }

    reverse_iterator rbegin()
    {
        if(this->_tree_root != NULL)
        {
            return(this->last_tmp_knot->parent);
        }
        return(NULL);
    }
    const_reverse_iterator rbegin() const
    {
        if(this->_tree_root != NULL)
        {
            return(this->last_tmp_knot->parent);
        }
        return(NULL);
    }

    reverse_iterator rend()
    {
        if(this->_tree_root != NULL)
        {
            knot *tmp = found_min_knot(this->_tree_root);
            return(tmp->left);
        }
        return (NULL);
    }
    const_reverse_iterator rend() const
    {
        if(this->_tree_root != NULL)
        {
            knot *tmp = found_min_knot(this->_tree_root);
            return(tmp->left);
        }
        return (NULL);
    }

    bool empty() const
    {
        if(this->_size > 0)
            return false;
        return true;
    }

    size_type size() const
    {
        return(this->_size);
    }

    size_type max_size() const
    {
        // return (std::numeric_limits<size_t>::max() / sizeof(ft::knots<key_type>));
        return (this->_Alloc.max_size());
    }

    void clear()
    {
        if(this->_tree_root)
        {
            delete_tree(this->_tree_root);
        }
        this->_tree_root = NULL;
    }

    ft::pair<iterator, bool> insert( const value_type& value )
    {
        knot *new_knot = insert_to_tree(value);
        bool result = false;
        if(new_knot)
        {
            _size += 1;
            result = true;
        }
        return(ft::pair<knot*, bool>(new_knot, result));
    }
    iterator insert( iterator hint, const value_type& value )
    {
        // knot *new_knot = insert_to_tree(value);
        knot *new_knot = NULL;
        if(hint)
        {
            new_knot = insert_to_tree(value);
            if(new_knot)
                _size += 1;
            else
                new_knot = find_knot(value, this->_tree_root);
        }
        return(new_knot);
    }

    template< class InputIt >
    typename ft_enable_if<!is_integral<InputIt>::res, void>::type
    insert( InputIt first, InputIt last )
    {
        for(; first != last; first++)
        {
            if(insert_to_tree(*first))
            {
                this->_size += 1;
            }
        }
    }

    void erase( iterator pos )
    {
        if(!this->_tree_root)
            return;
        knot *tmp = find_knot(*pos, this->_tree_root);
        if(!tmp)
            return;
        delete_knot(*pos);
        this->_size -= 1;
        if(!this->_tree_root)
        {
            ft_free_knot(this->last_tmp_knot);
            ft_free_knot(this->first_tmp_knot);
        }
        return;
    }

    void erase( iterator first, iterator last )
    {
        if(!this->_tree_root)
            return;
        knot *tmp;
        int i = 0;
        for(; first != last; i++)
        {
            iterator temp = first;
            temp++;
            tmp = find_knot(*first, this->_tree_root);
            if(!tmp)
            {
                continue;
            }
            else
            {
                delete_knot(tmp->_pair);
                this->_size -= 1;
            }
            first = temp;
        }
        if(!this->_tree_root)
        {
            ft_free_knot(this->last_tmp_knot);
            ft_free_knot(this->first_tmp_knot);
        }
        return;
    }

    size_type erase( const Key& key )
    {
        if(!this->_tree_root)
            return(0);
        knot *tmp = find_knot(key, this->_tree_root);
        if(!tmp)
            return(0);
        delete_knot(tmp->_pair);
        this->_size -= 1;
        if(!this->_tree_root)
        {
            ft_free_knot(this->last_tmp_knot);
            ft_free_knot(this->first_tmp_knot);
        }
        return(1);
    }

    void swap( set& other ) 
    {        
        swap(this->_Alloc, other._Alloc);
        swap(this->_knot, other._knot);
        swap(this->_tree_root, other._tree_root);
        swap(this->_size, other._size);
        swap(this->last_tmp_knot, other.last_tmp_knot);
        swap(this->first_tmp_knot, other.first_tmp_knot);
        swap(this->_comp, other._comp);
    }

    size_type count( const Key& key ) const 
    {
        if(!this->_tree_root)
            return(0);
        if(find_knot(key, this->_tree_root))
            return(1);
        return(0);
    }

    iterator find( const Key& key )/ сделать с ней то же что и ласт тмп кнот
    {
        if(!this->_tree_root)
            return(NULL);
        knot *ret = find_knot(key, this->_tree_root);
        if(ret)
            return(ret);
        return(this->end());
    }

    const_iterator find( const Key& key ) const
    {
        if(!this->_tree_root)
            return(NULL);
        knot *ret = find_knot(key, this->_tree_root);
        if(ret)
            return(ret);
        return(this->end());
    }
    
    pair<iterator,iterator> equal_range( const Key& key )
    {
        return(pair<iterator, iterator>(this->lower_bound(key), this->upper_bound(key)));
    }

    pair<const_iterator,const_iterator> equal_range( const Key& key ) const
    {
        return(pair<iterator, iterator>(this->lower_bound(key), this->upper_bound(key)));
    }

    iterator lower_bound( const Key& key )
    {
        if(this->_tree_root != NULL)
        {
            for(iterator tmp = this->begin(); tmp != this->end(); tmp++)
            {
                if(*tmp >= key)
                    return(tmp);
            }
        }
        return(this->end());
    }
    
    const_iterator lower_bound( const Key& key ) const 
    {
        if(this->_tree_root != NULL)
        {
            for(iterator tmp = this->begin(); tmp != this->end(); tmp++)
            {
                if(*tmp >= key)
                    return(tmp);
            }
        }
        return(this->end());
    }

    iterator upper_bound( const Key& key )
    {
        for(iterator tmp = this->begin(); tmp != this->end(); tmp++)
        {
            if(*tmp > key)
                return(tmp);
        }
        return(this->end());
    }

    const_iterator upper_bound( const Key& key ) const
    {
        for(iterator tmp = this->begin(); tmp != this->end(); tmp++)
        {
            if(*tmp > key)
                return(tmp);
        }
        return(this->end());
    }

    key_compare key_comp() const
    {
        return(_comp);
    }

    value_compare value_comp() const 
    {
        return(_comp);
    }

    // class out_of_range : public std::exception {
    // public:
    //     const char*  what() const throw() {
    //         return "map::at:  key not found";
    //     }
    // };
/////////////////////////////////////////////////////////////////////////////////////
//                                                                                 //
//                                RED BLACK TREE                                   //
//                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////
private:
    knot     *find_knot(Key find_key, knot* root)  const
    {
        knot *tmp = root;
        while(1)
        {
            if(find_key == tmp->_pair)
                return(tmp);
            else if(find_key > tmp->_pair) // если то, что ищем больше, то идем в правого наследника
            {
                if(!tmp->right)
                    return(NULL);
                tmp = tmp->right;
            }
            else if(find_key < tmp->_pair) // если то, что ищем меньше, то идем в левого наследника
            {
                if(!tmp->left)
                    return(NULL);
                tmp = tmp->left;
            }
        }
        return(NULL);
    }
    void rotateLeft(knot *rotate_centre_knot) 
    {
        if (rotate_centre_knot == NULL || rotate_centre_knot->parent == NULL 
        || rotate_centre_knot->parent->left == rotate_centre_knot)
            return;
        knot *parent_knot = rotate_centre_knot->parent;
        knot *grand_parent_knot = rotate_centre_knot->parent->parent;
        parent_knot->right = rotate_centre_knot->left;
        if (rotate_centre_knot->left) 
        {
            rotate_centre_knot->left->parent = parent_knot;
            rotate_centre_knot->left = NULL;
        }
        rotate_centre_knot->parent = grand_parent_knot;
        if (grand_parent_knot == NULL)
            this->_tree_root = rotate_centre_knot;
        else if (grand_parent_knot->left == parent_knot)
            grand_parent_knot->left = rotate_centre_knot;
        else
            grand_parent_knot->right = rotate_centre_knot;
        rotate_centre_knot->left = parent_knot;
        parent_knot->parent = rotate_centre_knot;
    }

    void rotateRight(knot *rotate_centre_knot) 
    {
        if (rotate_centre_knot == NULL || rotate_centre_knot->parent == NULL 
        || rotate_centre_knot->parent->right == rotate_centre_knot)
            return;
        knot *parent_knot = rotate_centre_knot->parent;
        knot *grand_parent_knot = rotate_centre_knot->parent->parent;
        parent_knot->left = rotate_centre_knot->right;
        if (rotate_centre_knot->right) 
        {
            rotate_centre_knot->right->parent = parent_knot;
            rotate_centre_knot->right = NULL;
        }
        rotate_centre_knot->parent = grand_parent_knot;
        if (grand_parent_knot == NULL)
            this->_tree_root = rotate_centre_knot;
        else if (grand_parent_knot->left == parent_knot)
            grand_parent_knot->left = rotate_centre_knot;
        else
            grand_parent_knot->right = rotate_centre_knot;
        rotate_centre_knot->right = parent_knot;
        parent_knot->parent = rotate_centre_knot;
    }

    void coloring(knot *start, int indx)
    {
        if(indx == 1)
            start->parent->parent->right->color = 1;
        else
            start->parent->parent->left->color = 1;
        start->parent->color = 1;
        start->parent->parent->color = 2;
    }

    void balance_and_coloring_tree(knot *start) 
    {
        if (start == NULL || start->parent == NULL)
            return;
        while (start->parent->color == 2) 
        {
            if (start->parent->parent && start->parent == start->parent->parent->left) 
            {
                if (start->parent->parent->right && start->parent->parent->right->color == 2) 
                {
                    coloring(start, 1);
                    start = start->parent->parent;
                } 
                else 
                {
                    if (start == start->parent->right)
                    {
                        knot *tmp = start->parent;
                        rotateLeft(start);
                        start = tmp;
                    }
                    start->parent->color = 1;
                    if (start->parent->parent)
                        start->parent->parent->color = 2;
                    rotateRight(start->parent);
                }
            } 
            else
            {
                if (start->parent->parent && start->parent->parent->left && start->parent->parent->left->color == 2) 
                {
                    coloring(start, 2);
                    start = start->parent->parent;
                }
                else 
                {
                    if (start == start->parent->left)
                    {
                        knot *tmp = start->parent;
                        rotateRight(start);
                        start = tmp;
                    }
                    start->parent->color = 1;
                    if (start->parent->parent)
                        start->parent->parent->color = 2;
                    rotateLeft(start->parent);
                }
            }
            if (start == this->_tree_root)
                break;
        }
        this->_tree_root->color = 1;
    }

    knot *add_knot_to_tree(knot *new_knot, knot *root)
    {
        if(new_knot == NULL)
            return(NULL);
        if(root == NULL)
        {
            root = new_knot;
            return(root);
        }
        if(new_knot->_pair == root->_pair)
            return(NULL);
        if(new_knot->_pair < root->_pair)
        {
            if(root->left)
                add_knot_to_tree(new_knot, root->left);
            else
            {
                new_knot->parent = root;
                root->left = new_knot;
                balance_and_coloring_tree(new_knot);
            }
        }
        if(new_knot->_pair > root->_pair)
        {
            if(root->right)
                add_knot_to_tree(new_knot, root->right);
            else
            {
                new_knot->parent = root;
                root->right = new_knot;
                balance_and_coloring_tree(new_knot);
            }
        }
        return(new_knot); 
    }

    knot    *make_knote(value_type test)
    {
        knot *tmp;
        tmp = _Alloc.allocate(1);
        _Alloc.construct(tmp, knot(test));
        tmp->color = 2;
        return(tmp);
    }

    void ft_make_first_last_knot(value_type pair_for_new_knot, knot *new_knot, knot *tmp, knot *tmp2)
    {
        if(pair_for_new_knot > tmp->_pair)
        {
            new_knot->right = last_tmp_knot;
            last_tmp_knot->parent = new_knot;

            tmp2->left = first_tmp_knot;
            first_tmp_knot->parent = tmp2;
        }
        else if(pair_for_new_knot < tmp2->_pair)
        {
            new_knot->left = first_tmp_knot;
            first_tmp_knot->parent = new_knot;

            tmp->right = last_tmp_knot;
            last_tmp_knot->parent = tmp;
        }
        else
        {
            tmp2->left = first_tmp_knot;
            first_tmp_knot->parent = tmp2;

            tmp->right = last_tmp_knot;
            last_tmp_knot->parent = tmp;
        }
    }

    knot *insert_to_tree(value_type pair_for_new_knot)
    {
        if(this->_tree_root == NULL)
        {
            _tree_root = _Alloc.allocate(1);
            _Alloc.construct(_tree_root, knot(pair_for_new_knot));
            _tree_root->color = 1;
            // if(!this->last_tmp_knot)
            // {
                last_tmp_knot = _Alloc.allocate(1);
                _Alloc.construct(last_tmp_knot, knot(pair_for_new_knot));
                this->_tree_root->right = last_tmp_knot;
                last_tmp_knot->parent = _tree_root;

                first_tmp_knot = _Alloc.allocate(1);
                _Alloc.construct(first_tmp_knot, knot(pair_for_new_knot));
                this->_tree_root->left = first_tmp_knot;
                first_tmp_knot->parent = _tree_root;
            // }
            return(this->_tree_root);
        }
        else
        {
            knot *tmp = last_tmp_knot->parent;
            knot *tmp2 = first_tmp_knot->parent;
            tmp->right = NULL;
            tmp2->left = NULL;
            if(find_knot(pair_for_new_knot, this->_tree_root))
            {
                tmp->right = last_tmp_knot;
                tmp2->left = first_tmp_knot;
                return NULL;
            }
            else
            {
                knot *new_knot = make_knote(pair_for_new_knot);
                add_knot_to_tree(new_knot, this->_tree_root);
                ft_make_first_last_knot(pair_for_new_knot, new_knot, tmp, tmp2);
                return (new_knot);
            }
        }
    }

    void rebinding_instead_delete_knot(knot *toDel, knot *replacement)
    {
        if (toDel->parent == NULL)
            this->_tree_root = replacement;
        else if (toDel == toDel->parent->left)
            toDel->parent->left = replacement;
        else
            toDel->parent->right = replacement;
        if (replacement != NULL)
            replacement->parent = toDel->parent;
    }

    knot *found_min_knot(knot *start) const
    {
        knot *tmp = this->first_tmp_knot->parent;
        tmp->left = NULL;

        if (start->left)
            return (found_min_knot(start->left));
        tmp->left = first_tmp_knot;
        return (start);
    }

    knot *found_max_knot(knot *start)
    {
        knot *tmp2 = start;
        while(tmp2->right)
            tmp2 = tmp2->right;
        return(tmp2);
    }   

    bool isBlack(knot *ptr) 
    {
        return ((ptr == NULL) || (ptr && ptr->color == 1));
    }

    void ft_free_knot(knot *toDel) 
    {
        _Alloc.destroy(toDel);
        _Alloc.deallocate(toDel, 1);
    }

    void delete_knot(value_type data) 
    {
        knot *x;
        knot *y;
        knot *delete_knot = this->_tree_root;
        knot *parent = NULL;
        int     save_color;
        while (delete_knot != NULL)
        {
            if (delete_knot->_pair == data)
                break;
            if (!_comp(delete_knot->_pair, data))
                delete_knot = delete_knot->left;
            else
                delete_knot = delete_knot->right;
        }
        if (delete_knot == NULL)
            return;
        save_color = delete_knot->color;
        if (delete_knot->left == NULL)
        {
            x = delete_knot->right;
            parent = delete_knot->parent;
            rebinding_instead_delete_knot(delete_knot, x);
        }
        else if (delete_knot->right == NULL) 
        {
            x = delete_knot->left;
            parent = delete_knot->parent;
            rebinding_instead_delete_knot(delete_knot, x);
        }
        else 
        {
            y = found_min_knot(delete_knot->right);
            save_color = y->color;
            x = y->right;
            if (y->parent == delete_knot)
                parent = y;
            else 
            {
                parent = y->parent;
                rebinding_instead_delete_knot(y, y->right);
                y->right = delete_knot->right;
                y->right->parent = y;
            }
            rebinding_instead_delete_knot(delete_knot, y);
            y->left = delete_knot->left;
            y->left->parent = y;
            y->color = delete_knot->color;
        }
        ft_free_knot(delete_knot);
        if (save_color == 1 && parent) 
        {
            delete_fix(x, parent);
        }
    }

    void balance_coloring_in_delete_fix(knot *s, int indx, knot *parent)
    {
        if(indx == 1 || indx == 2)
        {
            s->color = 1;
            parent->color = 2;
            if(indx == 1)
                rotateLeft(s);
            else
                rotateRight(s);
        }
        if(indx == 3)
            s->color = 2;
    }

    void delete_fix(knot* x, knot *parent)
    {
        knot *s;
        while (parent && x != this->_tree_root && isBlack(x)) 
        {
            if (x == parent->left) 
            {
                s = parent->right;
                if (s && s->color == 2) 
                {
                    balance_coloring_in_delete_fix(s, 1, parent);
                    s = parent->right;
                }
                if (s && isBlack(s->left) && isBlack(s->right)) 
                {
                    balance_coloring_in_delete_fix(s, 3, parent);
                    x = parent;
                    parent = parent->parent;
                } 
                else
                {
                    if (s && isBlack(s->right))
                    {
                        if (s->left)
                            s->left->color = 1;
                        s->color = 2;
                        rotateRight(s->left);
                        s = parent->right;
                    }
                    if (s)
                        s->color = parent->color;
                    parent->color = 1;
                    if (s && s->right)
                        s->right->color = 1;
                    rotateLeft(parent->right);
                    x = this->_tree_root;
                }
            }
            else
            {
                s = parent->left;
                if (s && s->color == 2)
                {
                    balance_coloring_in_delete_fix(s, 2, parent);
                    s = parent->left;
                }
                if (s && isBlack(s->left) && isBlack(s->right))
                {
                    balance_coloring_in_delete_fix(s, 3, parent);
                    x = parent;
                    parent = parent->parent;
                }
                else
                {
                    if (s && isBlack(s->left))
                    {
                        if (s->right)
                            s->right->color = 1;
                        s->color = 2;
                        rotateLeft(s->right);
                        s = parent->left;
                    }
                    if (s)
                        s->color = parent->color;
                    parent->color = 1;
                    if (s && s->left)
                        s->left->color = 1;
                    rotateRight(parent->left);
                    x = this->_tree_root;
                }
            }
        }
        if (x)
            x->color = 1;
    }

    knot* ret_root()
    {
        return(this->_tree_root);
    }

    void printTreeHelper(knot *root, int space)
    {
        int i;
        if(root != NULL)
        {
            space = space + 10;
            printTreeHelper(root->right, space);
            std::cout << std::endl;
            for ( i = 10; i < space; i++)
            {
                std::cout << " ";
            }
            if(root == this->_tree_root)
                std::cout << "root  " << root->color << "  "<< root->_pair << std::endl;
            // else
            //     std::cout << root->color << "  " << root->_pair.first << std::endl;
            else
            {
                if(root != this->first_tmp_knot && root != this->last_tmp_knot)
                    std::cout << root->color << "  " << root->_pair << std::endl;
            }
            std::cout << std::endl;
            printTreeHelper(root->left, space);
        }
    }

    void delete_tree(knot *tmp)
    {
        if(tmp->left)
            delete_tree(tmp->left);
        if(tmp->right)
            delete_tree(tmp->right);
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->parent = NULL;

        _Alloc.destroy(tmp);
        _Alloc.deallocate(tmp, 1);
        this->_size = 0;
    }
};

template< class Key,class Compare, class Alloc >
void swap( ft::set<Key,Compare,Alloc>& lhs, ft::set<Key,Compare,Alloc>& rhs )
{
    lhs.swap(rhs);
}

template< class Key, class Compare, class Alloc >
bool operator==( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
{
    if(lhs.size() == rhs.size())
    {
        return(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    return(false);
}

template< class Key, class Compare, class Alloc >
bool operator!=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
{
    if(!(lhs == rhs))
        return(true);
    return(false);
}

template< class Key, class Compare, class Alloc >
bool operator<( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
{
    return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template< class Key, class Compare, class Alloc >
bool operator<=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
{
    if(lhs == rhs)
        return(true);
    if(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
        return(true);
    return(false);
}

template< class Key, class Compare, class Alloc >
bool operator>( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
{
    if(lhs == rhs)
        return(false);
    return(!(lhs < rhs));
}

template< class Key, class Compare, class Alloc >
bool operator>=( const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs )
{
    if(lhs == rhs)
        return(true);
    if(!(lhs <= rhs))
        return(true);
    return(false);
}
}

#endif