#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "../my_reimplemented/iterator_traits.hpp"

namespace ft
{
    template<typename T>
    class Random_access_iterator 
    {
    public:
        typedef T                                   value_type;
        typedef std::ptrdiff_t                      difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        // typedef ft::random_access_iterator_tag     iterator_category;
        typedef std::random_access_iterator_tag     iterator_category;
 
    protected:
        // https://www.cplusplus.com/reference/cstddef/ptrdiff_t/
        pointer              ptr;     
    public:
        //https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
        //Is default-constructible, copy-constructible, copy-assignable and destructible
        Random_access_iterator() : ptr(0) {}
        Random_access_iterator( T* new_ptr ) { this->ptr = new_ptr;}
        
        // Random_access_iterator( const Random_access_iterator &new_iterator) {*this = new_iterator;}
        Random_access_iterator(const Random_access_iterator<typename remove_const<value_type>::type> & src)// : ptr(&(*src)) {}
        {
            this->ptr = src.ptr_geter();
        }

		Random_access_iterator<value_type> & operator=(Random_access_iterator<typename remove_const<value_type>::type> const & src) {
            this->ptr = src.ptr_geter();
			return *this;
		}

        // Random_access_iterator &operator=(const Random_access_iterator &new_iterator)
        // {
        //     this->ptr = new_iterator.ptr;
        //     return(*this);
        // }

        T* ptr_geter() const
        {
            return(ptr);
        }
    
        ~Random_access_iterator() {}
    
        bool operator==(const Random_access_iterator &second) const
        {
            return(this->ptr == second.ptr);
        }
        bool operator!=(const Random_access_iterator &second) const
        {
            return(this->ptr != second.ptr);
        }

        T &operator*()
        {
            return(*ptr);
        }

        T *operator->()
        {
            return(this->ptr);
        }

        Random_access_iterator operator++(int)
        {
            Random_access_iterator tmp(*this);
            operator++();
            return(tmp);
        }
        Random_access_iterator &operator++()
        {
            this->ptr++;
            return(*this);
        }

        Random_access_iterator operator--(int)
        {
            Random_access_iterator tmp(*this);
            operator--();
            return(tmp);
        }
        Random_access_iterator &operator--()
        {
            this->ptr--;
            return(*this);
        }
                
        Random_access_iterator operator+(int n) 
        {
            return(Random_access_iterator(this->ptr + n));
        }
        Random_access_iterator operator-(int n)
        {

            return(Random_access_iterator(this->ptr - n));
        }
        
        bool operator>(const Random_access_iterator &second) const
        {
            return(this->ptr > second.ptr);
        }
        bool operator>=(const Random_access_iterator &second) const
        {
            return(this->ptr >= second.ptr);
        }
        
        bool operator<(const Random_access_iterator &second) const
        {
            return(this->ptr < second.ptr);
        }
        bool operator<=(const Random_access_iterator &second) const
        {
            return(this->ptr <= second.ptr);
        }
        
        Random_access_iterator operator+=(int n) 
        {
            if(n < 0)
                this->operator-=((n*(-1)));
            for(int i = 0; i < n; i++)
                this->operator++();
            return(*this);
        }
        Random_access_iterator operator-=(int n)
        {
            if(n < 0)
                this->operator+=((n*(-1)));
            for(int i = 0; n > i; n--)
                this->operator--();
            return(*this);
        }
         
        T &operator[](int n) const
        {
            return *(this->ptr + n);
        }        
    };

template <typename T>
ft::Random_access_iterator<T> operator+(const std::ptrdiff_t &to_add, Random_access_iterator<T> &it)
{
    Random_access_iterator<T> n;
    n = it.operator+(to_add);
    return(n);
}

// template <typename T>
// ft::Random_access_iterator<T> operator-(const ptrdiff_t &to_add, Random_access_iterator<T> &it)
// {
//     Random_access_iterator<T> n;
//     n = it.operator-(to_add);
//     return(n);
// }

};

#endif