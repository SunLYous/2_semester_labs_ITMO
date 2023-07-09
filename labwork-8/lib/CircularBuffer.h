#pragma once
#include <iostream>
#include <vector>

template<typename T, typename Allocator = std::allocator<T>>

class CircularBuffer {
public:
    class Iterator {
    public:
        CircularBuffer<T>& user_;
        int index_;
        bool flag_stop = false;
        explicit Iterator(CircularBuffer<T>& user) : user_(user), index_(0) {};
        Iterator(CircularBuffer<T>& user, int index) : user_(user), index_(index) {
        };

        Iterator& operator++() {
            if ((user_.end_ == user_.begin_) && (index_ == (user_.Size() - 1)) && !flag_stop) {
                index_ = 0;
                flag_stop = true;
                return *this;
            }
            index_++;
            return *this;
        }
        Iterator& operator=(const Iterator& user) {
            user_ = user.user_;
            index_ = user.index_;
            flag_stop = user.flag_stop;
            return *this;
        }

        Iterator& operator--() {
            if (user_.end_ < user_.begin_ && index_ == -1) {
                index_ = user_.Size() - 1;
            }
            index_--;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            if (index_ == user_.Size() && !flag_stop && user_.end_ == user_.begin_) {
                index_ = 0;
                flag_stop = true;
                return tmp;
            }
            index_++;
            return tmp;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            if (index_ == -1) {
                index_ = user_.Size() - 1;
            }
            index_--;
            return tmp;
        }

        T& operator*() {
            if (index_ > user_.Size() || index_ < 0) {
                throw std::out_of_range("Segmentation fault");
            }
            return user_.buffer_[index_];
        }

        bool operator==(const Iterator& user) {
            return user.index_ == index_;
        }
        bool operator!=(const Iterator& user) {
            return index_ != user.index_;
        }

    };
    class ConstIterator {
    public:
        const CircularBuffer<T>& user_;
        const int index_;
        bool flag_stop = false;
        explicit ConstIterator(CircularBuffer<T>& user) : user_(user), index_(0) {};
        ConstIterator(CircularBuffer<T>& user, int index) : user_(user), index_(index) {
        };

        T& operator*() {
            if (index_ > user_.Size() || index_ < 0) {
                throw std::out_of_range("Segmentation fault");
            }
            return user_[index_];
        }
        bool operator==(const ConstIterator& user) {

            return user.index_ == index_;
        }
        bool operator!=(const ConstIterator& user) {

            return index_ != user.index_;
        }
    };
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef Iterator iterator;
    typedef const Iterator const_iterator;
    size_t size_ = 0;
    Allocator alloc_;
    T* buffer_ = nullptr;
    int begin_ = 0;
    int end_ = 0;
    bool flag = false;

    void Swap(CircularBuffer& user) {
        CircularBuffer tmp = *this;
        *this = user;
        user = tmp;
    }
    virtual void PushBack(const T& element) {
        if (flag && (end_) % size_ == begin_) {
            buffer_[end_ % size_] = element;
            end_ = (end_ + 1) % size_;
            begin_ = (begin_ + 1) % size_;
        } else if (end_ == begin_ && !flag) {
            buffer_[end_ % size_] = element;
            end_ = (end_ + 1) % size_;
        } else {
            buffer_[end_ % size_] = element;
            end_ = (end_ + 1) % size_;
        }
        if (end_ == size_) {
            flag = true;
        }
    }

    T& PopBack() {
        if (end_ == 0 && !flag) {
            throw std::out_of_range("Segmentation fault");
        } else if (end_ % size_ == 0 && end_ != 0) {
            end_ = size_ - 1;
            flag = false;
            return buffer_[(end_ + 1) % size_];
        } else if (end_ == 0 && flag) {
            end_ = size_ - 1;
            return buffer_[(end_ + 1) % size_];
        } else {
            end_ = (end_ - 1) % size_;
            return buffer_[(end_) % size_];
        }
    }

    T& PopFront() {
        if (begin_ == end_ && !flag) {
            throw std::out_of_range("Segmentation fault");
        } else {
            int tmp = begin_;
            begin_ = (begin_ + 1) % size_;
            return buffer_[tmp];
        }
    }

    T& BackElement() {
        if (end_ == 0) {
            return buffer_[size_ - 1];
        }
        return buffer_[end_ - 1];
    }

    T& FrontElement() {
        return buffer_[begin_];
    }

    size_t Size() {
        if (!flag && end_ == begin_) {
            return 0;
        } else if (flag && end_ == begin_) {
            return size_;
        } else if (flag && end_ > begin_) {
            if (begin_ == 0) {
                return end_;
            }
            return end_ - 1 - begin_;
        } else if (flag && end_ < begin_) {
            return size_ - begin_ + end_ - 1;
        } else if (!flag && end_ > begin_) {
            return end_ - 1 - begin_;
        } else if (!flag && end_ < begin_) {
            return size_ - begin_ + end_ - 1;
        }
    }

    T& At(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Segmentation fault");
        }
        return buffer_[index];
    }

    void Clear() {
        begin_ = 0;
        end_ = 0;
        flag = false;
    }

    bool Empty() {
        if (begin_ == end_ && !flag) {
            return true;
        } else {
            return false;
        }
    }

    size_t MaxSize() {
        return size_;
    }

    T& operator[](size_t index) {
        if (index > size_) {
            throw std::out_of_range("Segmentation fault");
        }
        if (flag && begin_ != 0)
            return buffer_[(begin_ - 1 + index) % size_];
        else if (flag && begin_ == 0)
            return buffer_[(begin_ + index) % size_];
    }

    CircularBuffer& operator=(CircularBuffer& user) {
        if (this == &user) {
            return *this;
        }
        delete[] buffer_;
        size_ = user.size_;
        begin_ = user.begin_;
        end_ = user.end_;
        for (int i = 0; i < size_; ++i) {
            buffer_[i] = user.buffer_[i];
        }
        return *this;
    }
    bool operator==(const CircularBuffer& user) {
        if (size_ != user.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (buffer_[i] != user.buffer_[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const CircularBuffer& user) {
        return !(*this == user);
    }

    //копирующий конструктор
    CircularBuffer(const CircularBuffer& user) {
        size_ = user.size_;
        end_ = user.end_;
        begin_ = user.begin_;
        buffer_ = alloc_.allocate(size_);
        for (size_t i = 0; i < size_; ++i) {
            buffer_[i] = user.buf_[i];
        }
    }

    CircularBuffer() {
        size_ = 0;
        buffer_ = nullptr;
    }

    explicit CircularBuffer(size_t size) {
        size_ = size;
        buffer_ = alloc_.allocate(size_);
        for (int i = 0; i < size_; ++i) {
            buffer_[i] = 0;
        }
        end_ = size_;
        flag = true;
    }

    CircularBuffer(size_t size, T element) {
        size_ = size;
        alloc_.allocate(size_);
        for (int i = 0; i < size_; ++i) {
            buffer_[i] = element;
        }
        end_ = size_;
        flag = true;
        Iterator it(*this);
    }

    ~CircularBuffer() {
        alloc_.deallocate(buffer_, size_);
    }

    Iterator begin() {
        return Iterator(*this, begin_);
    }

    Iterator end() {
        if (end_ == 0) {
            return Iterator(*this, size_ - 1);
        }
        return Iterator(*this, end_ - 1);
    }

    ConstIterator cbegin() {
        return ConstIterator(*this, begin_);
    }

    ConstIterator cend() {
        return ConstIterator(*this, end_ - 1);
    }

};

template<typename T>
void Swap(CircularBuffer<T>& user1, CircularBuffer<T>& user2) {
    CircularBuffer<T> tmp = user1;
    user1 = user2;
    user2 = tmp;
}

template<typename T, typename Allocator = std::allocator<T>>
class CircularBufferExt {
public:
public:
    class Iterator {
    public:
        CircularBufferExt<T>& user_;
        int index_;
        bool flag_stop = false;
        Iterator(CircularBufferExt<T>& user) : user_(user), index_(0) {};
        Iterator(CircularBufferExt<T>& user, int index) : user_(user), index_(index) {
        };
        Iterator& operator++() {
            if (user_.end_ == user_.begin_ && index_ == user_.Size() && !flag_stop) {
                index_ = 0;
                flag_stop = true;
                return *this;
            }
            index_++;
            return *this;
        }

        Iterator& operator--() {
            if (user_.end_ < user_.begin_ && index_ == -1) {
                index_ = user_.Size() - 1;
            }
            index_--;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            if (index_ == user_.Size()) {
                index_ = 0;
                flag_stop = true;
                return tmp;
            }
            index_++;
            return tmp;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            if (index_ == -1) {
                index_ = user_.Size() - 1;
            }
            index_--;
            return tmp;
        }

        T& operator*() {
            if (index_ > user_.Size() || index_ < 0) {
                throw std::out_of_range("Segmentation fault");
            }
            return user_[index_];
        }

        bool operator==(const Iterator& user) {

            return user.index_ == index_;
        }
        bool operator!=(const Iterator& user) {
            return index_ != user.index_;
        }
    };
    class ConstIterator {
    public:
        const CircularBufferExt<T>& user_;
        const int index_;
        bool flag_stop = false;
        ConstIterator(CircularBufferExt<T>& user) : user_(user), index_(0) {};
        ConstIterator(CircularBufferExt<T>& user, int index) : user_(user), index_(index) {
        };

        T& operator*() {
            if (index_ > user_.Size() || index_ < 0) {
                throw std::out_of_range("Segmentation fault");
            }
            return user_[index_];
        }
        bool operator==(const ConstIterator& user) {

            return user.index_ == index_;
        }
        bool operator!=(const ConstIterator& user) {

            return index_ != user.index_;
        }
    };
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef Iterator iterator;
    typedef const Iterator const_iterator;
    size_t size_ = 0;
    int tmp_end_ = 0;
    Allocator alloc_;
    T* buffer_ = nullptr;
    int begin_ = 0;
    int end_ = 0;
    bool flag = false;

    void Swap(CircularBufferExt& user) {
        CircularBuffer tmp = *this;
        *this = user;
        user = tmp;
    }
    T& PopBack() {
        if (end_ == 0 && !flag) {
            throw std::out_of_range("Segmentation fault");
        } else if (end_ % size_ == 0 && end_ != 0) {
            end_ = size_ - 1;
            flag = false;
            return buffer_[(end_ + 1) % size_];
        } else if (end_ == 0 && flag) {
            end_ = size_ - 1;
            return buffer_[(end_ + 1) % size_];
        } else {
            end_ = (end_ - 1) % size_;
            return buffer_[(end_) % size_];
        }
    }

    T& PopFront() {
        if (begin_ == end_ && !flag) {
            throw std::out_of_range("Segmentation fault");
        } else {
            int tmp = begin_;
            begin_ = (begin_ + 1) % size_;
            return buffer_[tmp];
        }
    }

    T& BackElement() {
        if (end_ == 0) {
            return buffer_[size_ - 1];
        }
        return buffer_[end_ - 1];
    }

    T& FrontElement() {
        return buffer_[begin_];
    }

    size_t Size() {
        if (!flag && end_ == begin_) {
            return 0;
        } else if (flag && end_ == begin_) {
            return size_;
        } else if (flag && end_ > begin_) {
            if (begin_ == 0) {
                return end_;
            }
            return end_ - 1 - begin_;
        } else if (flag && end_ < begin_) {
            return size_ - begin_ + end_ - 1;
        } else if (!flag && end_ > begin_) {
            return end_ - 1 - begin_;
        } else if (!flag && end_ < begin_) {
            return size_ - begin_ + end_ - 1;
        }
    }

    T& At(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Segmentation fault");
        }
        return buffer_[index];
    }

    void Clear() {
        begin_ = 0;
        end_ = 0;
        flag = false;
    }

    bool Empty() {
        if (begin_ == end_ && !flag) {
            return true;
        } else {
            return false;
        }
    }

    size_t MaxSize() {
        return size_;
    }

    T& operator[](size_t index) {
        if (index > size_) {
            throw std::out_of_range("Segmentation fault");
        }
        if (flag && begin_ != 0)
            return buffer_[(begin_ - 1 + index) % size_];
        else if (flag && begin_ == 0)
            return buffer_[(begin_ + index) % size_];
    }

    CircularBufferExt& operator=(const CircularBufferExt& user) {
        if (this == &user) {
            return *this;
        }
        delete[] buffer_;
        size_ = user.size_;
        begin_ = user.begin_;
        end_ = user.end_;
        flag = user.flag;
        buffer_ = alloc_.allocate(size_);
        for (size_t i = 0; i < size_; ++i) {
            buffer_[i] = user.buffer_[i];
        }
        return *this;
    }
    bool operator==(const CircularBufferExt& user) {
        if (size_ != user.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (buffer_[i] != user.buffer_[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const CircularBufferExt& user) {
        return !(*this == user);
    }

    Iterator begin() {
        return Iterator(*this, begin_);
    }

    Iterator end() {
        if (end_ == 0) {
            return Iterator(*this, size_);
        }
        return Iterator(*this, end_ - 1);
    }

    ConstIterator cbegin() {
        return ConstIterator(*this, begin_);
    }

    ConstIterator cend() {
        return ConstIterator(*this, end_ - 1);
    }
    void PushBack(const T& element) {
        if (!flag && (end_) % size_ == begin_) {
            buffer_[end_ % size_] = element;
            tmp_end_ = end_;
            end_ = (end_ + 1) % size_;
        } else if (end_ == begin_ && flag) {
            T* buff_ = alloc_.allocate(size_ * 2);
            int k = 0;
            for (auto i = begin(); i != end(); i++) {
                buff_[k] = *i;
                k++;
            }
            end_ = k;
            begin_ = 0;
            size_ *= 2;
            alloc_.deallocate(buffer_, size_);
            buffer_ = buff_;
            buffer_[end_ % size_] = element;
            end_ = (end_ + 1) % size_;
        } else {
            buffer_[end_ % size_] = element;
            end_ = (end_ + 1) % size_;
        }
        if (end_ == begin_ && !flag) {
            flag = true;
        }
    }

    CircularBufferExt() {
        size_ = 1;
        buffer_ = alloc_.allocate(size_);
    }

    CircularBufferExt(size_t size, T element) {
        size_ = size;
        if (size_ == 0)
            size_ = 1;
        buffer_ = alloc_.allocate(size_);
        for (int i = 0; i < size_; ++i) {
            buffer_[i] = element;
        }
        end_ = size_;
        flag = true;

    }

    explicit CircularBufferExt(size_t size) {
        size_ = size;
        if (size_ == 0)
            size_ = 1;
        buffer_ = alloc_.allocate(size_);
        for (int i = 0; i < size_; ++i) {
            buffer_[i] = 0;
        }
        end_ = size_;
        flag = true;
    }
    ~CircularBufferExt() {
        alloc_.deallocate(buffer_, size_);
    }
};
void Swap(CircularBufferExt<int>& a, CircularBufferExt<int>& b) {
    CircularBufferExt<int> tmp = a;
    a = b;
    b = tmp;
}
