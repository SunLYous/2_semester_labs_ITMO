#include <lib/CircularBuffer.h>
#include <gtest/gtest.h>
#include <sstream>

TEST(CircularBuffer, PopBack) {
    CircularBuffer<int> buffer(3);
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    buffer.PopBack();
    EXPECT_EQ(buffer.MaxSize(), 3);
    EXPECT_EQ(buffer.Size(), 2);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
}

//Далее, для проверки очистки буфера можно использовать следующий тест:

TEST(CircularBuffer, Clear) {
    CircularBuffer<int> buffer(3);
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    buffer.Clear();
    EXPECT_EQ(buffer.Size(), 0);
}
//Для проверки перезаписи можно использовать следующий тест:

TEST(CircularBuffer, Overwrite) {
    CircularBuffer<int> buffer(3);
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    buffer.PushBack(4);
    EXPECT_EQ(buffer.Size(), 3);
    EXPECT_EQ(buffer[0], 4);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
}

//Для проверки индексирования буфера можно использовать следующий тест:

TEST(CircularBuffer, Indexing) {
    CircularBuffer<int> buffer(3);
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
}

//Для проверки итераторов буфера можно использовать следующий тест:

TEST(CircularBuffer, Iterators) {
    CircularBuffer<int> buffer(3);
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    int i = 0;
    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
        EXPECT_EQ(*it, ++i);
    }
}


//Для проверки проверки предельного размера буфера с возможностью расширения можно использовать следующий тест:

TEST(CircularBufferExt, MaxSize) {
    CircularBufferExt<int> buffer(3);
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    EXPECT_EQ(buffer.MaxSize(), 3);
    buffer.PushBack(4);
    EXPECT_EQ(buffer.MaxSize(), 6);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);
}
TEST(CircularBufferExt, PushBack) {
    CircularBufferExt<int> buffer;
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    buffer.PushBack(4);
    EXPECT_EQ(buffer.MaxSize(), 4);
    EXPECT_EQ(buffer.Size(), 4);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);
}
TEST(CircularBufferExt, PopBack) {
    CircularBufferExt<int> buffer;
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    buffer.PushBack(4);
    buffer.PopBack();
    EXPECT_EQ(buffer.MaxSize(), 4);
    EXPECT_EQ(buffer.Size(), 3);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
}
TEST(CircularBufferExt, Clear) {
    CircularBufferExt<int> buffer;
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    buffer.PushBack(4);
    buffer.Clear();
    EXPECT_EQ(buffer.Size(), 0);
}
TEST(CircularBufferExt, Overwrite) {
    CircularBufferExt<int> buffer;
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    buffer.PushBack(4);
    buffer.PushBack(5);
    EXPECT_EQ(buffer.Size(), 5);
    EXPECT_EQ(buffer.MaxSize(), 8);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);
    EXPECT_EQ(buffer[4], 5);
}
TEST(CircularBufferExt, Indexing) {
    CircularBufferExt<int> buffer;
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    buffer.PushBack(4);
    EXPECT_EQ(buffer[0], 1);
    EXPECT_EQ(buffer[1], 2);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);
}
TEST(CircularBufferExt, Iterators) {
    CircularBufferExt<int> buffer;
    buffer.PushBack(1);
    buffer.PushBack(2);
    buffer.PushBack(3);
    buffer.PushBack(4);
    int i = 0;
    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
        EXPECT_EQ(*it, ++i);
    }
}

