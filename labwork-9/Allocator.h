#ifndef LABWORK_9_SUNLYOUS__ALLOCATOR_H_
#define LABWORK_9_SUNLYOUS__ALLOCATOR_H_

#include<iostream>
#include "PoolClass.h"
template<typename T>
class Allocator {
public:
    template<typename U>
    struct rebind {
        typedef Allocator<U> other;
    };
    using value_type = T;
    using size_type = size_t;
    using pointer = T*;

    template<class U>
    explicit Allocator(const Allocator<U>& other) noexcept {
        count_pools_ = other.GetCountPools();
        pools_ = reinterpret_cast<std::pair<size_t, Pool*>*>(other.GetPools());
    }

    constexpr T* allocate(size_type n) {
        T* pointer = nullptr;
        size_t size_chunk = sizeof(T); // размер куска
        size_t min_difference = INT32_MAX;
        size_t index = 0; // индекс пула
        for (size_t i = 0; i < count_pools_; i++) {
            if (size_chunk == pools_[i].first && n <= pools_[i].second->getFreeCountChunk()) {
                pointer = reinterpret_cast<T*>(pools_[i].second->Pool_Allocate(n));
                if (pointer != nullptr) {
                    return pointer;
                }
            }
            if (size_chunk < pools_[i].first && n <= pools_[i].second->getFreeCountChunk()) {
                if (pools_[i].first - size_chunk < min_difference) {
                    min_difference = pools_[i].first - size_chunk;  // находим минимальную разницу
                    index = i;
                }
            }
        }
        if (min_difference != INT32_MAX) {
            pointer = reinterpret_cast<T*> (pools_[index].second->Pool_Allocate(
                    pools_[index].first / size_chunk + pools_[index].first % size_chunk));
            if (pointer != nullptr) {
                return pointer;
            }
        }
        throw std::bad_alloc();
    }

    constexpr void deallocate(void* p, const size_type n) {
        char* pointer = reinterpret_cast<char*>(p);
        for (size_t i = 0; i < count_pools_; i++) {
            if (pointer - pools_[i].second->MemoryGet() >= 0 && pools_[i].second->EndMemoryGet() - pointer >= 0) {
                pools_[i].second->Pool_Deallocate(p, n);
                return;
            }
        }
    }

    explicit Allocator(const size_t count_pools, const size_t* pools_size, const size_t* chunk_size) noexcept {
        count_pools_ = count_pools;
        pools_ = new std::pair<size_t, Pool*>[count_pools_];
        for (size_t i = 0; i < count_pools_; i++) {
            pools_[i].first = chunk_size[i];
            pools_[i].second = new Pool(pools_size[i], chunk_size[i]);
        }
    }
    ~Allocator() {
        std::destroy_n(pools_, count_pools_);
    }
    bool operator==(const Allocator& other) const {
        return count_pools_ == other.count_pools_;
    }
    bool operator!=(const Allocator& other) const {
        return !(*this == other);
    }
    Allocator(const Allocator& other) {
        count_pools_ = other.count_pools_;
        pools_ = new std::pair<size_t, Pool*>[count_pools_];
        for (size_t i = 0; i < count_pools_; i++) {
            pools_[i].first = other.pools_[i].first;
            pools_[i].second = new Pool(*other.pools_[i].second);
        }
    }
    Allocator& operator=(const Allocator& other) {
        if (this == &other) {
            return *this;
        }
        std::destroy_n(pools_, count_pools_);
        count_pools_ = other.count_pools_;
        pools_ = new std::pair<size_t, Pool*>[count_pools_];
        for (size_t i = 0; i < count_pools_; i++) {
            pools_[i].first = other.pools_[i].first;
            pools_[i].second = new Pool(*other.pools_[i].second);
        }
        return *this;
    }

    size_t GetCountPools() const {
        return count_pools_;
    }
    std::pair<size_t, Pool*>* GetPools() const {
        return pools_;
    }
private:
    size_t count_pools_;
    std::pair<size_t, Pool*>* pools_;
};

#endif //LABWORK_9_SUNLYOUS__ALLOCATOR_H_
