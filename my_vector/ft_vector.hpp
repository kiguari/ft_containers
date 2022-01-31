#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>
#include "../my_iterators/random_access_iterator.hpp"
#include "../my_iterators/ft_reverse_iterator.hpp"
#include "../my_reimplemented/ft_is_integral.hpp"
#include "../my_reimplemented/ft_lexicographical_compare.hpp"
#include "../my_reimplemented/ft_equal.hpp"



#include "../my_reimplemented/ft_enable_if.hpp"
#include <limits>

namespace ft {
// у вектора есть второй шаблонный параметр аллокатор, мы его не замечаем, потому что он всегда по уполчанию стд::аллокатор от нашего типа
template <typename T, typename Alloc = std::allocator<T> >
/*
все контейнеры по умолчанию для распределения используют системный аллокатор,
в шаблоне он принимается вторым параметром
*/
class vector
{
public:
    typedef ft::Random_access_iterator<T>                   iterator;
    typedef ft::Random_access_iterator<const T >            const_iterator;
    typedef ft::Reverse_iterator<T>                         reverse_iterator;
    typedef ft::Reverse_iterator<T const>                   const_reverse_iterator;
    typedef T&                                              reference;
    typedef typename Alloc::pointer                         www;
    typedef T                                               value_type;
    typedef size_t                                          size_type;
    typedef const T&                                        const_reference;

    
private:
    T *my_vector;
    size_t _size;
    size_t _capacity;
    Alloc alloc;
    
    template <typename U>
    void swap(U& a, U& b)
    {
        U tmp = a;
        a = b;
        b = tmp;
    }
public:
    explicit vector (const Alloc& allocator = Alloc()) :  alloc(allocator)
    {
        this->_size = 0;
        this->_capacity = 0;
        this->my_vector = alloc.allocate(0);
    }

    explicit vector ( size_t count, const T& value = T(), const Alloc& allocator = Alloc()) :  alloc(allocator)
    {
        this->_size = 0;
        this->_capacity = count;
        if(count > this->max_size())
            throw leng_error() ;
        this->my_vector = alloc.allocate(_capacity);
        this->assign(count, value);
    }
    
    template < class InputIt >
    vector ( InputIt first, typename ft_enable_if<!is_integral<InputIt>::res, InputIt>::type last, const Alloc& allocator = Alloc()) : alloc(allocator)
    {
        this->_size = 0;
        this->_capacity = 0;
        this->my_vector = alloc.allocate(0);
        this->assign(first, last);
    }
    vector ( const vector& other)
    {
        this->_capacity = 0;
        this->_size = 0;
        this->my_vector = alloc.allocate(0);
        *this = other;
    }
    ~vector()
    {
        www my_vector_pos = my_vector;
        for(size_t i = 0; i < this->_size; i++)
            this->alloc.destroy((my_vector_pos + i));
        this->alloc.deallocate(my_vector, _capacity);
    }

    vector &operator= ( const vector &other )
    {
        if(other._capacity == 0)
        {
            if(this->_capacity)
            {
                www my_vector_pos = my_vector;
                for(size_t i = 0; i < this->_size; i++)
                {
                    this->alloc.destroy((my_vector_pos + i));
                }
                this->alloc.deallocate(this->my_vector, this->_capacity);
                this->my_vector = alloc.allocate(0);
                this->_capacity = 0;
                this->_size = 0;
            }
            else
                return (*this);
        }
        else
        {
            if(this->_capacity)
            {
                www my_vector_pos = my_vector;
                for(size_t i = 0; i < this->_size; i++)
                {
                    this->alloc.destroy((my_vector_pos + i));
                }
                this->alloc.deallocate(this->my_vector, this->_capacity);
                this->my_vector = alloc.allocate(other.capacity());
                this->_capacity = other.capacity();
                this->_size = 0;
                for(size_t i = 0; i < other._size; i++)
                {
                    this->push_back(other.my_vector[i]);
                }
            }
            else
            {
                this->alloc.deallocate(this->my_vector, this->_capacity);
                this->_capacity = other.capacity();
                this->_size = 0;
                this->my_vector = this->alloc.allocate(_capacity);
                for(size_t i = 0; i < other._size; i++)
                {
                    this->push_back(other.my_vector[i]);
                }
            }
        }
        return(*this);
    }
    template < class InputIt >
    typename ft_enable_if<!is_integral<InputIt>::res, void>::type
    assign( InputIt first, InputIt last )
    {
            www my_vector_pos = my_vector;
            for(size_t i = 0; i < this->_size; i++)
                this->alloc.destroy((my_vector_pos + i));
            this->_size = 0;
            for(; first != last; first++)
                this->push_back(*first);
    }
    void assign(size_t n, T value)
    {
        if(this->_size)
            this->clear();
        for(size_t i = 0; i < n; i++)
            this->push_back(value);
    }
    Alloc get_allocator() const
    {
        return(this->alloc);
    }
    T& at( size_t pos )
    {
        if((pos > _size-1 || pos < 0) || !_size)
            throw std::out_of_range("vector");
        return(this->my_vector[pos]);
    }
    const T& at( size_t pos ) const
    {
        if((pos > _size-1 || pos < 0) || !_size)
            throw std::out_of_range("vector");
        return(this->my_vector[pos]);
    }
    T& operator[](size_t n)
    {
        return(this->my_vector[n]);
    }
    const T& operator[](size_t n) const
    {
        return(this->my_vector[n]);
    }
    T& front()
    {
        return(this->my_vector[0]);
    }
    const T& front() const
    {
        return(this->my_vector[0]);
    }
    T& back()
    {
        return(this->my_vector[this->_size - 1]);
    }
    const T& back() const
    {
        return(this->my_vector[this->_size - 1]);
    }
    T* data()
    {
        return(this->my_vector);
    }
    const T* data() const
    {
        return(this->my_vector);
    }

    iterator end(void)
    {
        return(iterator(my_vector + _size));
    }
    iterator begin(void)
    {
        return(iterator(my_vector));
    }

    const_iterator begin(void) const
    {
        return(const_iterator(my_vector));
    }
    const_iterator end(void) const
    {
        return(const_iterator(my_vector + _size));
    }
    reverse_iterator rbegin(void)
    {
        return(reverse_iterator(my_vector + _size - 1));
    }
    reverse_iterator rend(void)
    {
        return(reverse_iterator(my_vector - 1));
    }
    const_reverse_iterator rbegin(void) const
    {
        return(reverse_iterator(my_vector + _size - 1));
    }
    const_reverse_iterator rend(void) const
    {
        return(reverse_iterator(my_vector - 1));
    }
    bool empty() const
    {
        if(!this->_size)
            return(true);
        else
            return(false);
    }
    size_t size() const
    {
        return(this->_size);
    }
    size_t max_size() const
    {
        size_t ret = std::numeric_limits<size_t>::max() / sizeof(T);
        return(ret);
    }
    void reserve(size_t n)
    {
        if(n > _capacity)
        {
            T *tmp;
            tmp = this->alloc.allocate(n);
            www my_vector_pos = my_vector;
            www tmp_vector_pos = tmp;
            for(size_t i = 0; i < this->_size; i++)
            {
                alloc.construct(tmp_vector_pos + i, *(my_vector + i));
            }
            for(size_t i = 0; i < this->_size; i++)
            {
                this->alloc.destroy((my_vector_pos + i));
            }
            alloc.deallocate(my_vector, _capacity);
            this->_capacity = n;
            this->my_vector = tmp;
        }
    }
    size_t capacity() const
    {
        return(this->_capacity);
    }
    void clear()
    {
        this->erase(this->begin(), this->end());
    }
    iterator insert(iterator pos, const T &val)
    {
        if(pos == this->end())
        {
            this->push_back(val);
            return(iterator(&my_vector[this->_size]));
        }
        else
        {
            ft::vector<T> tmp;
            int i = 0;
            int flag = 0;
            for(iterator start = this->begin(); start != this->end(); start++)
            {
                if(start == pos)
                {
                    tmp.push_back(val);
                    tmp.push_back(*start);
                    flag = 1;
                }
                else
                {
                    tmp.push_back(*start);
                    if(!flag)
                        i++;
                }
            }
            *this = tmp;
            return(iterator(&my_vector[i]));
        }
    }
    void insert( iterator pos, size_t count, const T& value)
    {
        ft::vector<T> tmp;
        iterator tmp_first = this->begin();
        iterator tmp_tmp_first = this->begin();
        size_t i = 0;
        for(; tmp_first != pos; tmp_first++)
        {
            tmp.push_back(this->my_vector[i]);
            i++;
        }
        for(size_t k = 0; k < count; k++)
        {
            tmp.push_back(value);
        }
        for(; pos != this->end(); pos++)
        {
            tmp.push_back(this->my_vector[i]);
            i++;
        }
        *this = tmp;
    }
    template < class InputIt >
    typename ft_enable_if<!is_integral<InputIt>::res, void>::type
    insert( iterator pos, InputIt first, InputIt last )
    {
        ft::vector<T> tmp;
        iterator tmp_first = first;
        iterator tmp_tmp_first = this->begin();
        size_t i = 0;
        for(; tmp_tmp_first != pos; tmp_tmp_first++)
        {
            tmp.push_back(this->my_vector[i]);
            i++;
        }
        size_t tmp_i = i;
        iterator third_for = tmp_tmp_first;
        for(; first != last; first++)
        {
            tmp.push_back(*first);
        }
        for(; third_for != this->end(); third_for++)
        {
            tmp.push_back(this->my_vector[tmp_i]);
            tmp_i++;
        }
        *this = tmp;
    };
    iterator erase(iterator n)
    {
        iterator tmp = n;
        if(this->_size)
        {
            iterator tmp2 = this->begin();
            int i = 0;
            for(; tmp2 < n; tmp2++)
                i++;
            www erase_pos = my_vector + i;
            this->alloc.destroy(erase_pos);
            while(n < this->end() - 1)
            {
                erase_pos = my_vector + i;
                alloc.construct(erase_pos, *(n + 1));
                erase_pos = my_vector + i + 1;
                this->alloc.destroy(erase_pos);
                n++;
                i++;
            }
            this->_size -= 1;
        }
        return(iterator(tmp));
    }
    iterator erase(iterator start, iterator end)
    {
        T *tmp = alloc.allocate(this->_capacity);
        www my_vector_pos = my_vector;
        www tmp_vector_pos = tmp;
        iterator tmpstart = this->begin();
        iterator tmpend = this->end();
        iterator ret = start;
        size_t need_erase_count = 0;
        size_t i = 0;
        size_t j = 0;
        if(start == end)
        {
            erase(start);
            return(iterator(start));
        }
        else
        {
            for(; tmpstart != start; tmpstart++)
            {
                alloc.construct(tmp_vector_pos + j, *(my_vector + i));
                i++;
                j++;
            }
            for(; start != end; start++)
            {
                need_erase_count++;
                tmpstart++;
                i++;
            }
            for(; tmpstart != tmpend; tmpstart++)
            {
                alloc.construct(tmp_vector_pos + j, *(my_vector + i));
                i++;
                j++;
            }
            for(size_t i = 0; i < this->_size; i++)
            {
                this->alloc.destroy((my_vector_pos + i));
            }
            alloc.deallocate(my_vector, _capacity);
            this->_size = _size - need_erase_count;
            this->my_vector = tmp;
        }
        return(iterator(ret));
    }
    void push_back(const T &new_element)
    {
        if(this->_size + 1 > _capacity)
        {
            if(this->_size != 0)
                this->reserve((_size) * 2);
            else
                this->reserve((_size+1) * 2);
        }
        www position = my_vector + _size;
        this->alloc.construct(position, new_element);
        this->_size += 1;
    }
    void pop_back()
    {
        if(this->_size)
        {
            this->erase(this->end()-1);
        }
        else
            return ;
    }
    void resize( size_t count, T value = T() )
    {
        T tmp = value;
        (void)tmp;
        size_t tmp_count = count;
        if(count > this->max_size())
            throw leng_error() ;
        if(tmp_count > _size)
        {
            for(; tmp_count > _size;)
            {
                push_back(tmp);
            }
        }
        else if(_size > tmp_count)
        {
            for(; _size > tmp_count;)
            {
                pop_back();
            }
        }
    }

    void swap (vector& x)
    {
        swap(alloc, x.alloc);
        swap(my_vector, x.my_vector);
        swap(_size, x._size);
        swap(_capacity, x._capacity);
    }
    void show() const
    {
        int j = 0;
        for(iterator i = this->begin(); i != this->end(); i++)
        {
            std::cout << my_vector[j] << "show" << std::endl;
            j++;
        }
    }

    class leng_error : public std::exception
    {
    public:
        const char* what() const throw()
        {
            return ("vector");
        }
    };
};

template< class T, class Alloc >
void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs )
{
    lhs.swap(rhs);
    return;
}

template< class T, class Alloc >
bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
    if(lhs.size() == rhs.size())
    {
        return(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    return(false);
}

template< class T, class Alloc >
bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
    if(!(lhs == rhs))
        return(true);
    return(false);
}

template< class T, class Alloc >
bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
    // if(lhs == rhs)
    //     return(false);
    return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    // if(lhs == rhs)
    //     return(false);
    // size_t count = 0;
    // int flag = 0;
    // if(lhs.sizee() > rhs.sizee())
    // {
    //     count = lhs.sizee();
    //     flag = 1;
    // }
    // else
    //     count = rhs.sizee();
    // for(size_t i = 0; i < count; i++)
    // {
    //     if(lhs[i] > rhs[i])
    //         return(false);
    //     if(i == rhs.sizee() && !flag && (lhs.sizee() > rhs.sizee()))
    //         return(false);
    //     if(i == lhs.sizee() && flag && (lhs.sizee() < rhs.sizee()))
    //         return(true);
    // }
    // return(true);
}

template< class T, class Alloc >
bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
    if(lhs == rhs)
        return(true);
    size_t count = 0;
    int flag = 0;
    if(lhs.size() > rhs.size())
    {
        count = lhs.size();
        flag = 1;
    }
    else
        count = rhs.size();
    for(size_t i = 0; i < count; i++)
    {
        if(lhs[i] > rhs[i])
            return(false);
        if(i == rhs.size() && !flag && (lhs.size() > rhs.size()))
            return(false);
        if(i == lhs.size() && flag && (lhs.size() < rhs.size()))
            return(true);
    }
    return(true);
}

template< class T, class Alloc >
bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
    if(lhs == rhs)
        return(false);
    return(!(lhs < rhs));
}

template< class T, class Alloc >
bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
{
    if(lhs == rhs)
        return(true);
    if(!(lhs <= rhs))
        return(true);
    return(false);
}
}

#endif
