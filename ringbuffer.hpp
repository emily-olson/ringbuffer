// A header file for ringbuffer class

#pragma once
#include <cstddef> // c standard def

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
        size_t size() const;

    private:
        int* buffer;                // pointer to my buffer
        size_t capacity;
        size_t read_head;
        size_t write_head;
        size_t count;
    };
