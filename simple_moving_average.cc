#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class SimpleMovingAverage {

    queue<double> dataset;
    const int period;
    double sum;

public:
    SimpleMovingAverage(int p) : dataset(), period(p), sum(0) {
    }

    void add_data(double num) {
        sum += num;
        dataset.push(num);

        if (dataset.size() > period) {
            sum -= dataset.front();
            dataset.pop();
        }
    }

    double get_average() {
        return sum / period;
    }

};


int main()
{
    vector<double> input_data = { 1, 3, 5, 6, 8,
                        12, 18, 21, 22, 25 };
    int per = 3;
    SimpleMovingAverage obj(per);

    for (double x : input_data) {
        obj.add_data(x);
        cout << "New number added is " << x << ", SMA = " << obj.get_average() << std::endl;
    }
    return 0;
}
