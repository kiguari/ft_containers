#ifndef KNOTS_HPP
#define KNOTS_HPP

namespace ft
{
// template <typename Key, typename Value>
template <typename P>
struct knots
{
    // ft::pair<Key, Value>     _pair;   // пара в узле
    P                        _pair;      // пара в узле
    knots                    *parent;    // указатель на родителя (вверх)
    knots                    *left;      // указатель на меньший кей
    knots                    *right;     // указатель на больший кей
    int                      color;      // 1 - black 2 - red;

    knots(const P &new_pair) : _pair(new_pair)
    {
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
        this->color = 2;
    }
    ~knots() {}
};
}

#endif