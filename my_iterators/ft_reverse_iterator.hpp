#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

namespace ft
{
    template<typename T>
    class Reverse_iterator  //: public ft::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T*, T&>
    {
    public:
        typedef T                                   value_type;
        typedef std::ptrdiff_t                      difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef Reverse_iterator<T>                 iterator_category;
    protected:
        pointer              ptr;       
    public:
        Reverse_iterator() : ptr(0) {}
        // Reverse_iterator( const Reverse_iterator &new_iterator) {*this = new_iterator;}
        Reverse_iterator(const Reverse_iterator<typename remove_const<value_type>::type > & src)// : ptr(&(*src)) {}
        {
            this->ptr = src.ptr_geter();
        }
        Reverse_iterator( T* new_ptr ) { this->ptr = new_ptr;}
        ~Reverse_iterator() {}

        Reverse_iterator<value_type> & operator=(Reverse_iterator<typename remove_const<value_type>::type > const & src) {
            this->ptr = src.ptr_geter();
			return *this;
		}
        // Reverse_iterator &operator=(const Reverse_iterator &new_iterator)
        // {
        //     this->ptr = new_iterator.ptr;
        //     return(*this);
        // }
        bool operator==(const Reverse_iterator &second) const
        {
            return(this->ptr == second.ptr);
        }
        bool operator!=(const Reverse_iterator &second) const
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
        Reverse_iterator operator++(int)
        {
            Reverse_iterator tmp(*this);
            this->ptr--;
            return(tmp);
        }
        Reverse_iterator &operator++()
        {
            this->ptr--;
            return(*this);
        }
        Reverse_iterator operator--(int)
        {
            Reverse_iterator tmp(*this);
            this->ptr++;
            return(tmp);
        }
        Reverse_iterator &operator--()
        {
            this->ptr++;
            return(*this);
        }   
        Reverse_iterator operator+(int n) 
        {
            return(Reverse_iterator(this->ptr - n));
        }
        Reverse_iterator operator-(int n)
        {

            return(Reverse_iterator(this->ptr + n));
        }
        bool operator>(const Reverse_iterator &second) const
        {
            return(this->ptr > second.ptr);
        }
        bool operator>=(const Reverse_iterator &second) const
        {
            return(this->ptr >= second.ptr);
        }
        
        bool operator<(const Reverse_iterator &second) const
        {
            return(this->ptr < second.ptr);
        }
        bool operator<=(const Reverse_iterator &second) const
        {
            return(this->ptr <= second.ptr);
        }
        Reverse_iterator operator+=(int n) 
        {
            if(n < 0)
                this->operator-=((n*(-1)));
            for(int i = 0; i < n; i++)
                this->operator++();
            return(*this);
        }
        Reverse_iterator operator-=(int n)
        {
            if(n < 0)
                this->operator+=((n*(-1)));
            for(int i = 0; n > i; n--)
                this->operator--();
            return(*this);
        }
        T &operator[](int n) const
        {
            return *(this->ptr - n);
        }
        T* ptr_geter() const
        {
            return(ptr);
        }
    };


    template <typename T>
    ft::Reverse_iterator<T> operator+(const std::ptrdiff_t &to_add, Reverse_iterator<T> &it)
    {
        Reverse_iterator<T> n;
        n = it.operator+(to_add);
        return(n);
    }

    // template <typename T>
    // ft::Reverse_iterator<T> operator-(const ptrdiff_t &to_add, Reverse_iterator<T> &it)
    // {
    //     Reverse_iterator<T> n;
    //     n = it.operator-(to_add);
    //     return(n);
    // }
};

#endif