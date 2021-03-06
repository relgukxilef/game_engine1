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
        span(const R& range);

        T* begin() const;
        T* end() const;
        bool empty() const;
        unsigned int size() const;

        operator span<const T>();

        T& operator[] (unsigned index);

        T* begin_pointer, * end_pointer;
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
}
