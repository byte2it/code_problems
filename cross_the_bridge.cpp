#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <limits.h>
#include <algorithm>

using namespace std;

/*

The approach is:

1. We do sort the array of people in ascending order by time which they need to cross the bridge
2. Two people who have less times - will carry the torches (array torchers)
    Every second time torches are carried by two slowest people  
    (it saves us time comparing to option for them to go separately)
3. Rest of the people are kept in separate array (array people)
4. Lets say that people go from right bank to left bank
5. We keep track where torch is located using boolean variable 'torch_on_right'
6. first loop continues untill array of people becomes empty
7. After that we move torchers to left bank
8. Cases where we have 1-3 people have specific handling

*/

int get_time(vector<int>& v) {

	if (v.size() == 0)
		return 0;

	int res = 0;

	if (v.size() == 1 || v.size() == 2 || v.size() == 3) {
		for (int i = 0; i < v.size(); ++i)
			res += v[i];
		return res;
	}

	std::sort(v.begin(), v.end());

	vector<int> torchers(v.begin(), v.begin()+2);
	vector<int> people(v.begin()+2, v.end());

	vector<int> torchers_left;
	
	bool torch_on_right = true;

	// move people
	while (people.size() > 0) {
		if (torchers.size() == 2 && torch_on_right) {
			torchers_left.swap(torchers);
			res += max(torchers_left[0], torchers_left[1]);
			torch_on_right = false;
		}

		else if (!torch_on_right && torchers_left.size() == 2) {
			if (torchers_left[0] < torchers_left[1]) {
				torchers.push_back(torchers_left[0]);
				res += torchers_left[0];
				torchers_left.erase(torchers_left.begin());
			}
			else {
				torchers.push_back(torchers_left[1]);
				res += torchers_left[1];
				torchers_left.erase(torchers_left.begin() + 1);
			}
			torch_on_right = true;
		}	

		else {
			if (torch_on_right) {
				res += max(people[people.size() - 1], people[people.size() - 2]);
				people.erase(people.begin() + people.size() - 1);
				people.erase(people.begin() + people.size() - 1);
				torch_on_right = false;
			}
			else {
				if (torchers_left.size() == 1) {
					res += torchers_left[0];
					torchers.push_back(torchers_left[0]);
					torchers_left.clear();
				}
				torch_on_right = true;
			}
		}
	}

	// move torchers
	while (torchers.size() > 0) {
		if (torchers.size() == 2 && torch_on_right) {
			res += max(torchers[0], torchers[1]);
			torchers.clear();
			torch_on_right = false;
		}
		if (torchers.size() == 1 && torchers_left.size() == 1) {
			if (torch_on_right) {
				res += torchers[0];
				torchers.clear();
				torch_on_right = false;
			}
			else {
				torchers.push_back(torchers_left[0]);
				res += torchers_left[0];
				torch_on_right = true;
			}
		}
	}
	return res;
}

int main(int argc, char** argv)
{
	vector<int> people1 = { 1,2,5,8 };

	vector<int> people2 = { 10,20,30 };
	int time_1 = get_time(people1);
	int time_2 = get_time(people2);

	cout << time_1 << ", " << time_2 << endl;
}
