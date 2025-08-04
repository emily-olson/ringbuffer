// Main file for ringbuffer program, for testing

#include "ringbuffer.hpp"
#include <iostream>

int main() {

    try {
        RingBuffer rb(3);
        rb.write(2);
        rb.write(3);
        rb.write(4);

        rb.write(5); // should error here (buffer full)
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

}
