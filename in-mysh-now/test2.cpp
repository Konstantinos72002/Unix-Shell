#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::this_thread::sleep_for(std::chrono::seconds(5));  // Wait for 5 seconds
    std::cout << "Test 2: five seconds have passed." << std::endl;  // Print the message
    return 0;
}