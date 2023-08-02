#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable> std::mutex mtx;
std::condition_variable cv;
bool isEvenPrinted = true; void printNumbers(int n, bool isEven) {
    for (int i = isEven ? 2 : 1; i <= n; i += 2) {
        std::cout << (isEven ? "Even" : "Odd");
        std::cout << i << std::endl;
    }
}

int main() {
    const int N = 20;
    std::thread evenThread(printNumbers, N, true);
    std::thread oddThread(printNumbers, N, false);     evenThread.join();
    oddThread.join();     return 0;
}