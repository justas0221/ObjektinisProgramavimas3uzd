
#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

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

    // Operatorius, tikrinantis, ar du vektoriai yra lygus
    bool operator==(const Vector& x) const
    {
        if (sz != x.sz || cap != x.cap)
        {
            return false;
        }
        for (size_type i = 0; i < sz; ++i)
        {
            if (elem[i] != x.elem[i])
            {
                return false;
            }
        }
        return true;
    }

    // Priskyrimo operatorius su initializer list'u
    Vector& operator=(initializer_list<T> il)
    {
        clear();
        reserve(il.size());
        for (auto& elem : il)
        {
            emplace_back(elem);
        }
        return *this;
    }

    // Iteratoriai
    iterator begin() noexcept
    {
        return elem;
    }

    const_iterator begin() const noexcept
    {
        return elem;
    }

    iterator end() noexcept
    {
        return elem + sz;
    }

    const_iterator end() const noexcept
    {
        return elem + sz;
    }

    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    const_iterator cbegin() const noexcept
    {
        return elem;
    }

    const_iterator cend() const noexcept
    {
        return elem + sz;
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator(begin());
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

    // Funkcija, grazinanti maksimalu galima vektoriaus elementu kieki
    size_type max_size() const noexcept
    {
        return alloc.max_size();
    }

    // Funkcija, grazinanti vektoriaus talpa
    size_type capacity() const noexcept
    {
        return cap;
    }

    // Funkcija, pakeicianti vektoriaus dydi
    void resize(size_type new_size)
    {
        if (new_size > cap)
        {
            reserve(new_size);
        }

        if (new_size > sz)
        {
            for (size_type i = sz; i < new_size; ++i)
            {
                alloc.construct(&elem[i]);
            }
        }
        else
        {
            for (size_type i = new_size; i < sz; ++i)
            {
                alloc.destroy(&elem[i]);
            }
        }

        sz = new_size;
    }

    // Funkcija, pakeicianti vektoriaus dydi ir priskirianti naujiems elementams tam tikra reiksme
    void resize(size_type newsz, const T& c)
    {
        if (newsz > cap)
        {
            reserve(newsz);
        }

        if (newsz > sz)
        {
            for (size_type i = sz; i < newsz; ++i)
            {
                alloc.construct(&elem[i], c);
            }
        }
        else
        {
            for (size_type i = newsz; i < sz; ++i)
            {
                alloc.destroy(&elem[i]);
            }
        }

        sz = newsz;
    }

    // Funkcija, keicianti vektoriaus talpa
    void reserve(size_type n)
    {
        if (n > cap)
        {
            pointer new_data = alloc.allocate(n);
            for (size_type i = 0; i < sz; ++i)
            {
                alloc.construct(&new_data[i], std::move(elem[i]));
                alloc.destroy(&elem[i]);
            }
            if (elem)
            {
                alloc.deallocate(elem, cap);
            }
            elem = new_data;
            cap = n;
        }
    }

    // Funkcija, pakeicianti vektoriaus talpos reiksme i lygia vektoriaus dydziui
    void shrink_to_fit()
    {
        if (sz < cap)
        {
            pointer new_data = alloc.allocate(sz);
            for (size_type i = 0; i < sz; ++i)
            {
                alloc.construct(&new_data[i], std::move(elem[i]));
                alloc.destroy(&elem[i]);
            }
            if (elem)
            {
                alloc.deallocate(elem, cap);
            }
            elem = new_data;
            cap = sz;
        }
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

    T* data() noexcept
    {
        return elem;
    }
    const T* data() const noexcept
    {
        return elem;
    }

    // Funkcija, vektoriaus gale sukonstruojanti elementa
    template<class... Args> reference emplace_back(Args&&... args)
    {
        if (sz == cap)
        {
            reserve(cap * 2);
        }
        alloc.construct(&elem[sz], std::forward<Args>(args)...);
        return elem[sz++];
    }

    // Funkcija, sukonstruojanti elementa vektoriaus gale
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

    // Funkcija, sukonstruojanti nauja elementa vartotojo parinktoje vektoriaus vietoje
    template<class... Args> iterator emplace(const_iterator position, Args&&... args)
    {
        size_type pos_index = position - cbegin();
        if (sz == cap)
        {
            reserve(2 *cap);
        }
        if (pos_index < sz)
        {
            for (size_type i = sz; i > pos_index; --i)
            {
                alloc.construct(&elem[i], std::move(elem[i - 1]));
                alloc.destroy(&elem[i - 1]);
            }
        }
        alloc.construct(&elem[pos_index], std::forward<Args>(args)...);
        ++sz;
        return begin() + pos_index;
    }

    // Funkcija, ikopijuojanti nauja elementa i vektoriaus tam tikra vieta
    iterator insert(const_iterator position, const T& x)
    {
        return emplace(position, x);
    }

    // Funkcija, perkelianti nauja elementa i vektoriaus tam tikra vieta
    iterator insert(const_iterator position, T&& x)
    {
        return emplace(position, std::move(x));
    }

    // Funkcija, ikopijuojanti n elementu su reiksme x i pasirinkta vektoriaus vieta
    iterator insert(const_iterator position, size_type n, const value_type& x)
    {
        size_type pos_index = position - cbegin();
        if (sz + n > cap)
        {
            reserve(sz + n);
        }
        for (size_type i = sz; i > pos_index; --i)
        {
            alloc.construct(&elem[i + n - 1], std::move(elem[i - 1]));
            alloc.destroy(&elem[i - 1]);
        }
        for (size_type i = 0; i < n; ++i)
        {
            alloc.construct(&elem[pos_index + i], x);
        }
        sz += n;
        return begin() + pos_index;
    }

    // Funkcija, iterpianti intervala elementu i nurodyta vektoriaus vieta
    template<class InputIt, typename = std::_RequireInputIter<InputIt>>
    iterator insert(const_iterator position, InputIt first, InputIt last)
    {
        size_type pos_index = position - cbegin();
        size_type n = std::distance(first, last);
        if (sz + n > cap)
        {
            reserve(sz + n);
        }
        for (size_type i = sz; i > pos_index; --i)
        {
            alloc.construct(&elem[i + n - 1], std::move(elem[i - 1]));
            alloc.destroy(&elem[i - 1]);
        }
        for (size_type i = 0; first != last; ++i, ++first)
        {
            alloc.construct(&elem[pos_index + i], *first);
        }
        sz += n;
        return begin() + pos_index;
    }

    // Funkcija, iterpianti duota elementu sarasa i paskirta vektoriaus vieta
    iterator insert(const_iterator position, initializer_list<T> il)
    {
        return insert(position, il.begin(), il.end());
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
