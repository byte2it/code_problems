#include <iostream>
#include <unordered_set>
#include <vector>


using namespace std;

bool find3Numbers(vector<int>& v, int sum) {

	for (int i = 0; i < v.size() - 2; i++) {

		unordered_set<int> s;
		int curr_sum = sum - v[i];
		for (int j = i + 1; j < v.size(); j++) {
			if (s.find(curr_sum - v[j]) != s.end()) {
				printf("Triplet is %d, %d, %d", v[i],
					v[j], curr_sum - v[j]);
				return true;
			}
			s.insert(v[j]);
		}
	}

	return false;
}

int main() {
	vector<int> v = { 1, 4, 45, 6, 10, 8 };
	int sum = 22;

	find3Numbers(v, sum);

	return 0;
}
