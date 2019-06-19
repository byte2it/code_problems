#include <iostream>
#include <vector>

using namespace std;

int best_profit(vector<int>& arr) {
	int i = 0, buy = 0, sell = 0, min = 0, profit = 0;

	for (i = 0; i < arr.size(); i++) {
		if (arr[i] < arr[min])
			min = i;
		else if (arr[i] - arr[min] > profit) {
			buy = min;
			sell = i;
			profit = arr[i] - arr[min];
		}
	}
	return profit;
}

int main() {
	vector<int> v1 = { 15, 50, 10, 45 };
	vector<int> v2 = { 10, 45, 15, 50 };
	vector<int> v3 = { 10, 10, 10, 10 };
	vector<int> v4 = { 50, 40, 20, 10 };
	int res1 = best_profit(v1);
	int res2 = best_profit(v2);
	int res3 = best_profit(v3);
	int res4 = best_profit(v4);
}
