#ifndef VECTOR
#define VECTOR

#include <memory>
#include <iostream>

template <class T>
class Vector {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef Vector<T>::iterator iter_type;
    typedef T* reverse_iterator;

    Vector() { create(); };
    explicit Vector( size_type n, const T &val = T{} ) { create(n, val); }

    Vector(const Vector& v) { create(v.begin(), v.end()); }
    Vector& operator=(const Vector&);
    ~Vector() { uncreate(); }
    Vector(std::initializer_list<T> list) : Vector(list.size()) {
        std::copy(std::begin(list), std::end(list), arr);
    }

    size_type size() const { return avail - arr; }
    size_type capacity() const { return limit - arr; }
    bool empty() const { return arr == avail; }
    void resize(size_t n, value_type val =  value_type()) { //TODO pridėti check'ą dėl capacity
        if (n < size()) {
            size_t diff = size() - n;   
            for (size_t i{}; i < diff; i++) {
                alloc.destroy(avail--);
            }
        }
        else if (n > size()) {

            if (n > capacity()) {
                size_type new_size = n;

                iterator new_arr = alloc.allocate(new_size);
                iterator new_avail = std::uninitialized_copy(arr, avail, new_arr);

                uncreate();

                arr = new_arr;
                avail = new_avail;
                limit = arr + new_size;

                int m = n - size();
                for (size_t i{}; i < m; i++) {
                    unchecked_append(val);
                }

            }
        }

    }
    size_t max_size() const { return alloc.max_size(); };
    void reserve(size_t n);
    void shrink_to_fit();

    void clear();
    T& front() { return *arr; };
    const T& front() const { return *arr; };

    T& back() { return *(avail - 1); };
    const T& back() const { return *(avail - 1); };

    T& at (size_t n);
    const T& at (size_t n) const; 

    value_type* data() { return arr; };
    const value_type* data() const { return arr; };

    void push_back(const T &val); 
    void pop_back();

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last) {

    }

    T& operator[](size_type i) { return arr[i]; }
    const T& operator[](size_type i) const { return arr[i]; }

    iterator begin() { return arr; }
    const_iterator begin() const { return arr; }
    iterator end() { return avail; }
    const_iterator end() const { return avail; }

    bool operator==(const Vector<T>& rhs);
    bool operator!=(const Vector<T>& rhs);
    bool operator<(const Vector<T>& rhs);
    bool operator<=(const Vector<T>& rhs);
    bool operator>(const Vector<T>& rhs);
    bool operator>=(const Vector<T>& rhs);

    static bool compare_greater(T v1, T v2);
    static bool compare_greater_equal(T v1, T v2);
    static bool compare_less_equal(T v1, T v2);

private:
    iterator arr;
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
Vector<T>& Vector<T>::operator=(const Vector& rhs) {
    if (&rhs != this) {
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
}

template <class T>
bool Vector<T>::operator==(const Vector<T>& rhs) {

    /*
    if (size() != rhs.size())
        return false;

    iterator it = begin();
    iterator rhs_it = rhs.begin();
    while (it != avail) {
        if (*it != *rhs_it)
           return false; 
    }
    return true;
    */

    return std::equal(begin(), end(), rhs.begin(), rhs.end());
}

template <class T>
bool Vector<T>::operator!=(const Vector<T>& rhs) {

    /*
    if (size() != rhs.size())
        return true;

    iterator it = begin();
    iterator rhs_it = rhs.begin();
    while (it != avail) {
        if (*it != *rhs_it)
           return true; 
    }

    return false;
    */
    
    return !std::equal(begin(), end(), rhs.begin(), rhs.end());
}

template <class T>
bool Vector<T>::operator<(const Vector<T>& rhs) {

    return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end());
}

template <class T>
bool Vector<T>::operator<=(const Vector<T>& rhs) {

    return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), compare_less_equal);
}

template <class T>
bool Vector<T>::operator>(const Vector<T>& rhs) {

    Vector<T> v;
    return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), compare_greater);
}

template <class T>
bool Vector<T>::compare_greater(T v1, T v2) {
    return v1 > v2;
}

template <class T>
bool Vector<T>::compare_greater_equal(T v1, T v2) {
    return v1 >= v2;
}

template <class T>
bool Vector<T>::compare_less_equal(T v1, T v2) {
    return v1 <= v2;
}

template <class T>
bool Vector<T>::operator>=(const Vector<T>& rhs) {

    Vector<T> v;
    return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end(), compare_greater_equal);
}

template <class T> 
void Vector<T>::create() {
    arr = avail = limit = nullptr;
}


template <class T> 
void Vector<T>::create(size_type n, const T &val) {
    arr = alloc.allocate(n);
    limit = avail = arr + n;
    std::uninitialized_fill(arr, limit, val);
}


template <class T>
void Vector<T>::create(const_iterator i, const_iterator j) {
    arr = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, arr);
}

template <class T>
void Vector<T>::uncreate() {
    if (arr) {
        iterator it = avail;
        while (it != arr)
            alloc.destroy(--it);

        alloc.deallocate(arr, limit - arr);
    }

    arr = limit = avail = nullptr;
}

template <class T>
void Vector<T>::reserve(size_t n) {
    size_type new_size = n;

    iterator new_arr = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(arr, avail, new_arr);

    uncreate();

    arr = new_arr;
    avail = new_avail;
    limit = arr + new_size;
}

template <class T>
void Vector<T>::shrink_to_fit() {
    size_t new_capacity = size();

    iterator new_arr = alloc.allocate(new_capacity);
    iterator new_avail = std::uninitialized_copy(arr, avail, new_arr);

    uncreate();

    arr = new_arr;
    avail = new_avail;
    limit = arr + new_capacity;
}

template <class T>
void Vector<T>::clear() {
    if (arr) {
        while (avail != arr)
            alloc.destroy(--avail);
    }
}

template <class T>
T& Vector<T>::at (size_t n) {
    if (n >= size())
        throw std::out_of_range ("Neatitinka vektoriaus dydžio\n");

    return *(arr + n - 1);
}

template <class T>
const T& Vector<T>::at (size_t n) const {
    if (n >= size())
        throw std::out_of_range ("Neatitinka vektoriaus dydžio\n");

    return *(arr + n - 1);
}

template <class T>
void Vector<T>::push_back(const T &val) {
    if (avail == limit)
        grow();
    unchecked_append(val);
}

template <class T>
void Vector<T>::pop_back() {
    alloc.destroy(--avail);  
}

template <class T>
void Vector<T>::grow() {
    size_type new_size = std::max(2 * (limit - arr), ptrdiff_t(1));

    iterator new_arr = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(arr, avail, new_arr);

    uncreate();

    arr = new_arr;
    avail = new_avail;
    limit = arr + new_size;
}

template <class T>
void Vector<T>::unchecked_append(const T &val) {
    alloc.construct(avail++, val);
}

#endif
