// A header file for ringbuffer class

#pragma once
#include <cstddef> // c standard def
#include <condition_variable>
#include <mutex>

// RingBuffer class, where its only supported item type is an int
class RingBuffer {
    public:
        RingBuffer(size_t capacity); // constructor
        ~RingBuffer();               // deconstructor

        void write(int item);
        int read();
        int peek() const;

        bool isEmpty() const;
        bool isFull() const;
        int size() const;

        std::mutex mutex;
        std::condition_variable nonfull;
        std::condition_variable nonempty;


    private:
        int* buffer;                // pointer to my buffer
        size_t capacity;
        size_t read_head;
        size_t write_head;
        size_t count;
    };
