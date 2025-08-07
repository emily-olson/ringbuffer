#include "ringbuffer.hpp"
#include <stdexcept>

// Constructor for my RingBuffer 
// returns nothing, don't need to say void
RingBuffer::RingBuffer(size_t cap): capacity(cap), read_head(0), write_head(0), count(0) {
    buffer = new int[capacity];                             // create an array of ints of length capacity, to serve as buffer. allocates memory on the heap.
    /* This was wrong because these are local variables to JUST the constructor function. After the constructor finishes, these variables go out of scope!!!!
    std::mutex mutex;
    std::condition_variable nonfull;
    std::condition_variable nonempty;
    */

}

// Deconstructor for my RingBuffer
RingBuffer::~RingBuffer() {
    delete[] buffer;                                        // delete memory off the heap for clean up
}


// Write function
void RingBuffer::write(int item) {
    std::unique_lock guard(mutex);
    while (isFull()) {
        nonfull.wait(guard);
    }
    if (isFull()) {
        throw std::runtime_error("RingBuffer is full. Please read before writing again.");
    }

    buffer[write_head] = item;
    write_head = (write_head + 1) % capacity;               // increment the write head (pointing at next available place to write)
    count++;                                                // increment number of items in buffer, don't need to use modulo because we just add to count and then subtract from count when reading
    if (!isEmpty()) {
        nonempty.notify_all();
    }
}


// Read function 
int RingBuffer::read() {
    std::unique_lock guard(mutex);
    while (isEmpty()) {
        nonempty.wait(guard);
    }
    if (isEmpty()) {
        throw std::runtime_error("RingBuffer is empty. Please write before reading again.");
    }

    int read_item;
    read_item = buffer[read_head];
    read_head = (read_head + 1) % capacity;
    count--;
    if (!isFull()) {
        nonfull.notify_all();
    }
    return read_item;
}

// Peek function
int RingBuffer::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("RingBuffer is empty. Please write before reading again.");
    }

    return buffer[read_head];
}    

// Function to check if the buffer is full (need to read before being able to write again)
bool RingBuffer::isFull() const {
    return count == capacity;
}


// Function to check if the buffer is empty (need to write before reading again)
bool RingBuffer::isEmpty() const {
    return count == 0;
}

int RingBuffer::size() const {
    return count;
}
