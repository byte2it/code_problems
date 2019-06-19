#include <iostream>
#include <vector>
using namespace std;

bool checkSubarraySum(vector<int>& v, int k, int sum) {
    int curr_sum = 0;
    for (int i = 0; i < k; i++)
        curr_sum += v[i];
    if (curr_sum == sum)
        return true;

    for (int j = k; j < v.size(); j++) {
        curr_sum = curr_sum + v[j] - v[j - k];
        if (curr_sum == sum)
            return true;
    }
    return false;
}

int main()
{
    vector<int> v = { 1, 4, 2, 10, 2, 3, 1, 0, 20 };
    int k = 4;
    int sum = 18;

    if (checkSubarraySum(v, k, sum))
        cout << "YES";
    else
        cout << "NO";

    return 0;
}
