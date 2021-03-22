#pragma once

#include <initializer_list>

namespace ge1 {

    template<class T>
    struct span {
        span();
        span(unsigned size);
        span(T* begin, T* end);
        span(std::initializer_list<T> values);
        template<class R>
        span(const R& range); // only works with continuous ranges

        T* begin() const;
        T* end() const;
        bool empty() const;
        unsigned int size() const;

        operator span<const T>();

        T& operator[] (unsigned index);

        T* begin_pointer, * end_pointer;
    };

    template<class T>
    struct unique_span : public span<T> {
        unique_span();
        unique_span(unsigned size);
        unique_span(T* begin, T* end);
        unique_span(std::initializer_list<T> values);
        unique_span(const unique_span<T>&) = delete;

        ~unique_span();

        unique_span<T>& operator=(const unique_span<T>&) = delete;
        unique_span<T>& operator=(unique_span<T>&& other);
    };

    template<class T>
    span<T>::span() : span(nullptr, nullptr) {}

    template<class T>
    span<T>::span(unsigned size) :
        begin_pointer(new T[size]), end_pointer(begin_pointer + size)
    {}

    template<class T>
    span<T>::span(T* begin, T* end) :
        begin_pointer(begin), end_pointer(end)
    {}

    template<class T>
    span<T>::span(std::initializer_list<T> values) :
        span(values.begin(), values.end())
    {}

    template<class T>
    template<class R>
    ge1::span<T>::span(const R& range) : span(&*range.begin(), &*range.end()) {}

    template<class T>
    T* span<T>::begin() const {
        return begin_pointer;
    }

    template<class T>
    T* span<T>::end() const {
        return end_pointer;
    }

    template<class T>
    bool span<T>::empty() const {
        return begin() == end();
    }

    template<class T>
    unsigned int span<T>::size() const {
        return end_pointer - begin_pointer;
    }

    template<class T>
    T& ge1::span<T>::operator[](unsigned index) {
        return begin()[index];
    }

    template<class T>
    ge1::span<T>::operator span<const T>() {
        return {begin_pointer, end_pointer};
    }

    template<class T>
    unique_span<T>::unique_span() : span<T>() {}

    template<class T>
    unique_span<T>::unique_span(unsigned size) : span<T>(size) {}

    template<class T>
    unique_span<T>::unique_span(T* begin, T* end) :
        span<T> (begin, end)
    {}

    template<class T>
    unique_span<T>::unique_span(std::initializer_list<T> values) :
        span<T> (values)
    {}

    template<class T>
    unique_span<T>::~unique_span() {
        if (this->begin_pointer != nullptr) {
            delete[] this->begin_pointer;
        }
    }

    template<class T>
    unique_span<T>& unique_span<T>::operator=(unique_span<T>&& other) {
        if (this->begin_pointer) {
            delete[] this->begin_pointer;
        }
        this->begin_pointer = other.begin_pointer;
        this->end_pointer = other.end_pointer;
        other.begin_pointer = nullptr;
        other.end_pointer = nullptr;

        return *this;
    }

}
