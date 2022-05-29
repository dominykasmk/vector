#ifndef VECTOR
#define VECTOR

#include <memory>

template <class T>
class Vec {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    Vec() { create(); };
    explicit Vec( size_type n, const T &val = T{} ) { create(n, val); }

    Vec(const Vec& v) { create(v.begin(), v.end()); }
    Vec& operator=(const Vec&);
    ~Vec() { uncreate(); }

    size_type size() const { return avail - data; }
    size_type capacity() const { return limit - data; }
    bool empty() const { return data == avail; }
    void resize(size_t n, value_type val =  value_type()) { 
        if (n < size()) {
            size_t diff = size() - n;   
            for (size_t i{}; i < diff; i++) {
                alloc.destroy(avail--);
            }
        }
        else if (n > size()) {
            for (size_t i{}; i < n; i++) {
                if (n + size() > capacity())
                    grow();

                unchecked_append(val);
            }
        }

    }
    size_t max_size() const { return alloc.max_size(); };
    void reserve(size_t n);
    void shrink_to_fit();

    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) const { return data[i]; }

    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    iterator end() { return limit; }
    const_iterator end() const { return limit; }

    void push_back(const T &val) {
        if (avail == limit)
            grow();
        unchecked_append(val);
    }
    

private:
    iterator data;
    iterator avail;
    iterator limit;

    std::allocator<T> alloc;

    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow();
    void unchecked_append(const T&);
};

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs) {
    if (&rhs != this) {
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

template <class T> 
void Vec<T>::create() {
    data = avail = limit = nullptr;
}


template <class T> 
void Vec<T>::create(size_type n, const T &val) {
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}


template <class T>
void Vec<T>::create(const_iterator i, const_iterator j) {
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_copy(i, j, data);
}

template <class T>
void Vec<T>::uncreate() {
    if (data) {
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);

        alloc.deallocate(data, limit - data);
    }

    data = limit = avail = nullptr;
}

template <class T>
void Vec<T>::reserve(size_t n) {
    size_type new_size = n;

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <class T>
void Vec<T>::shrink_to_fit() {
    size_t new_capacity = size();

    iterator new_data = alloc.allocate(new_capacity);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_capacity;
}

template <class T>
void Vec<T>::grow() {
    size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <class T>
void Vec<T>::unchecked_append(const T &val) {
    alloc.construct(avail++, val);
}

#endif
