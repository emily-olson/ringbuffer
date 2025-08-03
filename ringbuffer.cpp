#include "ringbuffer.hpp"
#include <stdexcept>

// Constructor for my RingBuffer 
// returns nothing, don't need to say void
RingBuffer::RingBuffer(size_t cap): capacity(cap), read_head(0), write_head(0), count(0) {
    buffer = new int[capacity]; // create an array of ints of length capacity
}


// Write function
void RingBuffer::write(int item) {
    if (isFull()) {
        throw std::runtime_error("RingBuffer is full. Please read before writing again.");

    buffer[write_head] = item;
    write_head = (write_head + 1) % capacity;               // increment the write head (pointing at next available place to write)
    count++;                                                // increment number of items in buffer, don't need to use modulo because we just add to count and then subtract from count when reading
    }
}
