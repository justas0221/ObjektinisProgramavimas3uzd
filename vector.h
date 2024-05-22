
#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

namespace std
{
template<class T, class Allocator = allocator<T>>
class Vector
{
    typename allocator_traits<Allocator>::pointer elem;
    size_t sz;
    size_t cap;
    Allocator alloc;
public:
    // Member types
    using value_type             = T;
    using allocator_type         = Allocator;
    using pointer                = typename allocator_traits<Allocator>::pointer;
    using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using size_type              = size_t;
    using difference_type        = ptrdiff_t;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Konstruktoriai
    Vector() noexcept(noexcept(Allocator())) : Vector(Allocator()) {}
    Vector(const Allocator&) noexcept : elem(nullptr), sz(0), cap(0), alloc(Allocator())
    {
        reserve(1);
    };
    Vector(size_type n, const Allocator& = Allocator()) : elem(nullptr), sz(0), cap(0), alloc(Allocator())
    {
        resize(n);
    };
    Vector(size_type n, const T& value, const Allocator& = Allocator()): elem(nullptr), sz(0), cap(0), alloc(Allocator())
    {
        resize(n, value);
    };

    // Initializer list'as
    Vector(initializer_list<T> il, const Allocator& = Allocator()) : elem(nullptr), sz(0), cap(0), alloc(Allocator())
    {
        insert(begin(), il);
    }

    // Destruktorius
    ~Vector()
    {
        if(elem)
            alloc.deallocate(elem, cap);
    };

    // Copy konstruktorius
    Vector(const Vector& x)
        : elem(nullptr), sz(0),
        cap(0),
        alloc(allocator_traits<Allocator>::select_on_container_copy_construction(x.alloc))
    {
        reserve(x.sz);
        for (size_type i = 0; i < x.sz; ++i)
        {
            emplace_back(x.elem[i]);
        }
    }

    // Move konstruktorius
    Vector(Vector&& x) noexcept
        : elem(std::exchange(x.elem, nullptr)),
        sz(std::exchange(x.sz, 0)),
        cap(std::exchange(x.cap, 0)),
        alloc(std::move(x.alloc)) {}

    // Copy assignment operatorius
    Vector& operator=(const Vector& x)
    {
        if (this != &x)
        {
            if (allocator_traits<Allocator>::propagate_on_container_copy_assignment::value && alloc != x.alloc)
            {
                if (elem)
                {
                    clear();
                    alloc.deallocate(elem, cap);
                }
                alloc = x.alloc;
                elem = nullptr;
                cap = 0;
            }
            reserve(x.sz);
            if (x.sz <= sz)
            {
                std::copy(x.elem, x.elem + x.sz, elem);
                for (size_type i = x.sz; i < sz; ++i)
                {
                    alloc.destroy(&elem[i]);
                }
            }
            else
            {
                for (size_type i = 0; i < sz; ++i)
                {
                    alloc.construct(&elem[i], x.elem[i]);
                }
                for (size_type i = sz; i < x.sz; ++i)
                {
                    alloc.construct(&elem[i], x.elem[i]);
                }
            }
            sz = x.sz;
        }
        return *this;
    }

    // Move assignment operatorius
    Vector& operator=(Vector&& x)
      noexcept(
        allocator_traits<Allocator>::propagate_on_container_move_assignment::value ||
        allocator_traits<Allocator>::is_always_equal::value
      )
      {
        if (this != &x)
        {
            if (allocator_traits<Allocator>::propagate_on_container_move_assignment::value)
            {
                if (elem)
                {
                    clear();
                    alloc.deallocate(elem, cap);
                }
                alloc = std::move(x.alloc);
                elem = std::exchange(x.elem, nullptr);
                sz = std::exchange(x.sz, 0);
                cap = std::exchange(x.cap, 0);
            }
            else
            {
                if (elem)
                {
                    clear();
                    alloc.deallocate(elem, cap);
                }

                elem = std::exchange(x.elem, nullptr);
                sz = std::exchange(x.sz, 0);
                cap = std::exchange(x.cap, 0);
            }
        }
        return *this;
    }

    // Operatorius, tikrinantis
    bool operator==(const Vector& x) const
    {
        if (sz != x.sz || cap != x.cap) {
            return false;
        }
        for (size_type i = 0; i < sz; ++i) {
            if (elem[i] != x.elem[i]) {
                return false;
            }
        }
        return true;
    }

    // Priskyrimo operatorius su initializer list'u
    Vector& operator=(initializer_list<T> il) {
        clear();
        reserve(il.size());
        for (auto& elem : il) {
            emplace_back(elem);
        }
        return *this;
    }

    // Funkcija, nustatanti vektoriaus dydi i nuli
    bool empty() const noexcept
    {
        return sz==0;
    }

    // Funkcija, grazinanti vektoriaus dydi
    size_type size() const noexcept
    {
        return sz;
    }

    // Funkcija, grazinanti vektoriaus talpa
    size_type capacity() const noexcept
    {
        return cap;
    }

    // Operatoriai elementu pasiekimui
    reference operator[](size_type n)
    {
        return elem[n];
    }
    const_reference operator[](size_type n) const
    {
        return elem[n];
    }
    const_reference at(size_type n) const
    {
        if (n >= sz)
        {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return elem[n];
    }
    reference at(size_type n)
    {
        if (n >= sz)
        {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return elem[n];
    }
    reference front()
    {
        return elem[0];
    }
    const_reference front() const
    {
        return elem[0];
    }
    reference back()
    {
        return elem[sz-1];
    }
    const_reference back() const
    {
        return elem[sz-1];
    }

    T* elem() noexcept
    {
        return elem;
    }
    const T* elem() const noexcept
    {
        return elem;
    }

    // Funkcija, ikopijuojanti elementa i vektoriaus gala
    void push_back(const T& x)
    {
        if (sz == cap)
        {
            reserve(cap* 2);
        }
        alloc.construct(&elem[sz++], x);
    }

    // Funkcija, perkelianti elementa i vektoriaus gala
    void push_back(T&& x)
    {
        emplace_back(std::move(x));
    }

    // Funkcija, pasalinanti paskutini vektoriaus elementa
    void pop_back()
    {
        if (sz > 0)
        {
            alloc.destroy(&elem[--sz]);
        }
    }

    // Funkcija, ikopijuojanti nauja elementa i vektoriaus tam tikra vieta
    iterator insert(const_iterator position, const T& x)
    {
        return emplace(position, x);
    }

    // Funkcija, istrinanti elementa is nurodytos vektoriaus pozicijos
    iterator erase(const_iterator position)
    {
        size_type pos_index = position - cbegin();
        if (pos_index >= sz)
        {
            throw std::out_of_range("Vector::erase: position out of range");
        }
        alloc.destroy(&elem[pos_index]);
        for (size_type i = pos_index; i < sz - 1; ++i)
        {
            alloc.construct(&elem[i], std::move(elem[i + 1]));
            alloc.destroy(&elem[i + 1]);
        }
        --sz;
        return begin() + pos_index;
    }

    // Funkcija, istrinanti nurodyta intervala vektoriaus elementu
    iterator erase(const_iterator first, const_iterator last)
    {
        size_type start_index = first - cbegin();
        size_type end_index = last - cbegin();
        if (start_index >= sz || end_index > sz || start_index > end_index)
        {
            throw std::out_of_range("Vector::erase: range out of range");
        }

        for (size_type i = start_index; i < end_index; ++i)
        {
            alloc.destroy(&elem[i]);
        }
        for (size_type i = end_index; i < sz; ++i)
        {
            alloc.construct(&elem[i - (end_index - start_index)], std::move(elem[i]));
            alloc.destroy(&elem[i]);
        }
        sz -= (end_index - start_index);
        return begin() + start_index;
    }

    // Funkcija, apkeicianti dvieju vektoriu reiksmes vietomis
    void swap(Vector& other) noexcept (allocator_traits<Allocator>::propagate_on_container_swap::value ||
             allocator_traits<Allocator>::is_always_equal::value)
    {
        std::swap(elem, other.elem);
        std::swap(sz, other.sz);
        std::swap(cap, other.cap);
        std::swap(alloc, other.alloc);
    }

    // Funkcija, isvalanti vektoriu
    void clear() noexcept
    {
        for (size_type i = 0; i < sz; ++i)
        {
            alloc.destroy(&elem[i]);
        }
        sz = 0;
    }
};

}

#endif
