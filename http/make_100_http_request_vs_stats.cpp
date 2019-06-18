#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <random>

using namespace std;


/*
Make 100 HTTP GET requests to http://en.wikipedia.org/wiki/Main_Page
and print the following statistics for the response time to stdout:

• 10th, 50th, 90th, 95th, 99th Percentile
• Mean
• Standard Deviation

Your solution must be parallel. You must make at least N (say 10, but should be configurable).
*/

vector<int> v;
mutex vecMtx;
float avg = 0;
const int nRequests = 100;
const int nThreads = 6;

// simulate GET, radom thread sleep
void http_get(const std::string& uri, int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

    std::lock_guard<std::mutex> lock(vecMtx);
    v.push_back(delay);
    avg += delay;
}

void worker(int iter) {
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(1, nRequests);

    while (iter > 0) {
        iter--;
        http_get("wiki", dis(gen));
    }
}

void get_statistics() {

    std::vector <std::thread>  threads;

    auto start = std::chrono::high_resolution_clock::now();

    int work = nRequests;
    int workChunk = work / nThreads;
    while (work > 0) {
        if (workChunk > work)
            workChunk = work;
        threads.push_back(std::thread(worker, workChunk));
        work -= workChunk;
    }

    for (size_t i = 0, j = threads.size(); i < j; ++i)  {
        threads[i].join();
    }
    auto end = std::chrono::high_resolution_clock::now();

    avg /= nRequests;
    std::vector<int> vr(v);
    std::sort(vr.begin(), vr.end());

    std::cout << "10th pr = " << vr[9] << "\n";
    std::cout << "50th pr = " << vr[49] << "\n";
    std::cout << "90th pr = " << vr[89] << "\n";
    std::cout << "99th pr = " << vr[98] << "\n";
    std::cout << "mean = " << avg << "\n";

    float div = 0;
    for (int i : v) {
        div += ((avg - i) * (avg - i));
    }
    std::cout << "std div = " << sqrt(div / nRequests) << "\n";

    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "worked: " << elapsed.count() << " ms\n";
}

int main() {
    get_statistics();
}
