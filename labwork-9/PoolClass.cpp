#include "PoolClass.h"
char* Pool::MemoryGet() {
    return memory_;
}
char* Pool::BeginMemoryGet() {
    return begin_memory_;
}
char* Pool::EndMemoryGet() {
    return end_memory_;
}
size_t Pool::getFreeCountChunk() {
    return count_free_chunk_;
}
void* Pool::Pool_Allocate(size_t n) {
    if (n > count_free_chunk_) {
        return nullptr;
    }
    if (end_memory_ - memory_ >= n * chunk_size_) {
        void* pointer = memory_;// вычисляем указатель на память
        memory_ += n * chunk_size_; // увеличиваем указатель на память
        for (size_t i = 0; i < n; i++) {
            state_of_chunks_[number_of_free_chunk_ + i] = false; // меняем состояние кусков
        }
        count_free_chunk_ -= n; // уменьшаем количество свободных кусков
        number_of_free_chunk_ += n; // увеличиваем номер свободного куска
        return pointer;
    } else {
        bool flag_find = false;
        for (size_t i = 0; i < count_chunk_; i++) {
            if (state_of_chunks_[i]) { // если кусок свободен
                for (size_t j = i; j < i + n; j++) { // проверяем есть ли n свободных кусков
                    if (state_of_chunks_[j]) {
                        flag_find = true; // если есть n свободных кусков
                    } else {
                        i = j; // если нет n свободных кусков
                    }
                    if (flag_find) { // если есть n свободных кусков
                        flag_find = false;
                        void* pointer = begin_memory_ + i * chunk_size_; // вычисляем указатель на память
                        for (size_t k = 0; k < n; k++) {
                            state_of_chunks_[i + k] = false; // меняем состояние кусков
                        }
                        count_free_chunk_ -= n; // уменьшаем количество свободных кусков
                    }
                }
            }
        }
    }
    return nullptr;
}
void Pool::Pool_Deallocate(void* pointer, size_t n) {
    if (pointer == nullptr) {
        return;
    }
    if (pointer < memory_ && pointer > end_memory_) {
        return;
    }
    size_t index = (reinterpret_cast<char*>(pointer) - memory_) / chunk_size_;// вычисляем индекс куска
    for (size_t i = 0; i < n; i++) {
        state_of_chunks_[index + i] = true; // меняем состояние кусков
    }
    count_free_chunk_ += n; // увеличиваем количество свободных кусков
}
Pool::Pool(size_t size_pool, size_t size_chunk) : size_pool_(size_pool), chunk_size_(size_chunk) {
    count_chunk_ = size_pool_ / chunk_size_; // вычисляем количество кусков
    count_free_chunk_ = count_chunk_; // вычисляем количество свободных кусков
    memory_ = new char[size_pool_];// выделяем память
    begin_memory_ = memory_; // вычисляем начало памяти
    end_memory_ = memory_ + size_pool_; // вычисляем конец памяти
    state_of_chunks_ = new bool[count_chunk_]{true}; // выделяем память под состояние кусков
}
