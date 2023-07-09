#ifndef LABWORK_11_SUNLYOUS__XRANGECLASS_H_
#define LABWORK_11_SUNLYOUS__XRANGECLASS_H_

#include <iostream>
#include <iterator>

template<typename T>
class XrangeClass {
private:
    T begin_ = 0;
    T end_;
    T step_ = 1;
public:
    template<typename U>
    XrangeClass(T begin, T end, U step) {
        begin_ = begin;
        end_ = end;
        step_ = step;
    };

    XrangeClass(T begin, T end) {
        begin_ = begin;
        end_ = end;
    }

    explicit XrangeClass(T end) {
        end_ = end;
        step_ = 1;
    }

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;
    private:
        T temp_element_;
        T step_iterator_;
    public:
        Iterator(T begin, T step) {
            temp_element_ = begin;
            step_iterator_ = step;
        }

        Iterator& operator=(const Iterator& other) {
            temp_element_ = other.temp_element_;
            step_iterator_ = other.step_iterator_;
        }

        T& operator*() {
            return temp_element_;
        }

        Iterator& operator++() {
            temp_element_ += step_iterator_;
            return *this;
        }

        Iterator  operator++(int) {
            Iterator copy = *this;
            ++(*this);
            return copy;
        }

        bool operator==(const Iterator& other) const {
            if (other.step_iterator_ == 0 && step_iterator_ == 0) {
                return true;
            } else if (temp_element_ >= other.temp_element_ && step_iterator_ > 0) {
                return true;
            } else if (temp_element_ <= other.temp_element_ && step_iterator_ < 0) {
                return true;
            } else {
                return false;
            }
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    Iterator begin() {
        return Iterator(begin_, step_);
    }

    Iterator end() {
        return Iterator(end_, step_);
    }

    ~XrangeClass() = default;
};

template<typename T, typename U>
XrangeClass<T> xrange(T start, T finish, U step) {
    return xRange(start, finish, step);
}

template<typename T>
XrangeClass<T> xrange(T begin, T end, T step) {
    return xRange(begin, end, step);
}

template<typename T>
XrangeClass<T> xrange(T begin) {
    return xRange(begin);
}

#endif //LABWORK_11_SUNLYOUS__XRANGECLASS_H_
