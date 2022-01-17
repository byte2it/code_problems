#include <iostream>          
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::mutex mtx;
std::condition_variable cv;
int current = 0;

void even() {

    std::unique_lock<std::mutex> lck(mtx);

    while (current <= 100) {

        if (current % 2 != 0)
            cv.wait(lck);

        std::cout << "even : " << current << '\n';
        current++;
        cv.notify_one();
    }
}

void odd() {
    std::unique_lock<std::mutex> lck(mtx);

    while (current < 100) {

        if (current % 2 == 0)
            cv.wait(lck);

        std::cout << "odd : " << current << '\n';
        current++;
        cv.notify_one();
    }
}

int main() {
    std::thread evenThread(even);
    std::thread oddThread(odd);

    std::cout << "Starting...\n";

    evenThread.join();
    oddThread.join();

    return 0;
}
