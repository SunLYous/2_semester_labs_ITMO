#ifndef LABWORK_11_SUNLYOUS__STANDARDLGORITHM_H_
#define LABWORK_11_SUNLYOUS_STANDARDLGORITHM_H_

#include<iostream>

namespace algo {
    template<typename Iterator, typename Predicate>
    bool all_of(Iterator begin, Iterator end, Predicate predicate) {
        while (begin != end) {
            if (!predicate(*begin)) {
                return false;
            }
            ++begin;
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    bool any_of(Iterator begin, Iterator end, Predicate predicate) {
        while (begin != end) {
            if (predicate(*begin)) {
                return true;
            }
            ++begin;
        }
        return false;
    }

    template<typename Iterator, typename Predicate>
    bool none_of(Iterator begin, Iterator end, Predicate predicate) {
        while (begin != end) {
            if (predicate(*begin)) {
                return false;
            }
            ++begin;
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    bool one_of(Iterator begin, Iterator end, Predicate predicate) {
        size_t count = 0;
        while (begin != end) {
            if (predicate(*begin)) {
                count++;
            }
            if (count > 1) {
                return false;
            }
            ++begin;
        }
        if (count == 1) {
            return true;
        } else {
            return false;
        }
    }

    template<typename Iterator>
    bool is_sorted(Iterator begin, Iterator end) {
        while (begin != end - 1) {
            if (*begin > *(begin + 1)) {
                return false;
            }
            ++begin;
        }
        return true;
    }

    template<typename Iterator, typename Comparator>
    bool is_sorted(Iterator begin, Iterator end, Comparator comp) {
        while (begin != end - 1) {
            if (!comp(*begin, *(begin + 1))) {
                return false;
            }
            ++begin;
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    bool is_partitioned(Iterator begin, Iterator end, Predicate predicate) {
        int check_change = 0;
        if(begin == end){
            return false;
        }
        while (begin + 1 != end) {
            if (predicate(*begin) != predicate(*(begin + 1))) {
                ++check_change;
            }
            if (check_change > 1) {
                return false;
            }
            ++begin;
        }
        if (check_change == 0) {
            return false;
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    Iterator find_not(Iterator begin, Iterator end, Predicate predicate) {
        while (begin != end) {
            if (!predicate(*begin)) {
                return begin;
            }
            ++begin;
        }
        return end;
    }

    template<typename Iterator, typename Predicate>
    Iterator find_backward(Iterator begin, Iterator end, Predicate predicate) {
        Iterator temp = end;
        --end;
        while (begin != end) {
            if (predicate(*(end))) {
                return end;
            }
            --end;
        }

        return temp;
    }
    template<typename Iterator, typename Predicate>
    bool is_palindrome(Iterator begin, Iterator end, Predicate predicate) {
        while (begin != end - 1) {
            if (!predicate(*begin, *(end - 1))) {
                return false;
            }
            ++begin;
            --end;
        }
        return true;
    }
}
#endif //LABWORK_11_SUNLYOUS__STANDARDLGORITHM_H_
