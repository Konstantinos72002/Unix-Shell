#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::this_thread::sleep_for(std::chrono::seconds(10));  // Wait for 10 seconds
    std::cout << "Test 1: Ten seconds have passed." << std::endl;  // Print the message
    return 0;
}