#ifndef LABWORK_11_SUNLYOUS_LIB_ZIPCLASS_H_
#define LABWORK_11_SUNLYOUS_LIB_ZIPCLASS_H_

#include <iostream>
#include <iterator>

template<typename T, typename U>
class ZipClass {
private:
    T::const_iterator begin1_;
    T::const_iterator end1_;
    U::const_iterator begin2_;
    U::const_iterator end2_;
public:
    ZipClass(const T& first, const U& second) {
        begin1_ = std::begin(first);
        end1_ = std::end(first);
        begin2_ = std::begin(second);
        end2_ = std::end(second);
    }

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<typename T::const_iterator, typename U::const_iterator>;
        using difference_type = ptrdiff_t;
        using pointer = std::pair<typename T::const_iterator, typename U::const_iterator>*;
        using reference = std::pair<typename T::const_iterator, typename U::const_iterator>&;
    private:
        T::const_iterator iterator_begin1_;
        U::const_iterator iterator_begin2_;
    public:
        Iterator(const T::const_iterator begin1, const U::const_iterator begin2) {
            iterator_begin1_ = begin1;
            iterator_begin2_ = begin2;
        }

        Iterator& operator=(const Iterator& other) {
            iterator_begin1_ = other.iterator_begin1_;
            iterator_begin2_ = other.iterator_begin2_;
        }

        std::pair<typename T::value_type, typename U::value_type> operator*() {
            return std::make_pair(*iterator_begin1_, *iterator_begin2_);
        }

        Iterator& operator++() {
            ++iterator_begin1_;
            ++iterator_begin2_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy = *this;
            ++iterator_begin1_;
            ++iterator_begin2_;
            return copy;
        }

        bool operator==(const Iterator& other) {
            if (iterator_begin1_ == other.iterator_begin1_ || iterator_begin2_ == other.iterator_begin2_) {
                return true;
            }
            return false;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        };
    };

    Iterator begin() {
        return Iterator(begin1_, begin2_);
    }

    Iterator end() {
        return Iterator(end1_, end2_);
    }
};

template<typename T, typename U>
ZipClass<T, U> zip(T& first, U& second) {
    return ZipClass<T, U>(first, second);
}

#endif //LABWORK_11_SUNLYOUS_LIB_ZIPCLASS_H_
