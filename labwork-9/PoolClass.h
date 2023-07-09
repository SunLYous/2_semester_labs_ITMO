#include <iostream>
class Pool final {
private:
    bool* state_of_chunks_; // состояние кусков
    char* begin_memory_ = nullptr; // указатель на начало памяти
    char* memory_ = nullptr; // указатель на память
    char* end_memory_ = nullptr; // указатель на конец памяти
    const size_t chunk_size_; // размер куска
    const size_t size_pool_; // размер пула
    size_t count_chunk_; // количество кусков
    size_t count_free_chunk_; // количество свободных кусков
    size_t number_of_free_chunk_ = 0; // номер свободного куска
public:
    Pool(size_t size_pool, size_t size_chunk);
    ~Pool() = default;
    void* Pool_Allocate(size_t n);
    void Pool_Deallocate(void* pointer, size_t n);
    char* MemoryGet();
    char* BeginMemoryGet();
    char* EndMemoryGet();
    size_t getFreeCountChunk();
};