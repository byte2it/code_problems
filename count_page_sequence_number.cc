#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

void main() {
	vector<vector<string>> input = { {"100", "home", "2341234123"},
									 {"101", "home", "2341234123"},
									 {"100", "about", "2341234123"},
									 {"101", "works", "2341234123"},
									 {"100", "company", "2341234123"},
									 {"101", "home", "2341234123"}, 
	{"100", "home", "2341234123"},
									 {"101", "home", "2341234123"},
									 {"100", "about", "2341234123"},
									 {"101", "works", "2341234123"},
									 {"100", "company", "2341234123"},
									 {"101", "home", "2341234123"} };

	unordered_map<string, list<string>> mm;
	unordered_map<string, int> counts;

	for (int i = 0; i < input.size(); ++i) {
		auto user_id = input[i][0];
		auto page = input[i][1];


		auto iter = mm.find(user_id);
		if (iter != mm.end()) {
			if (iter->second.size() == 3) {
				iter->second.pop_front();
			}
			if (iter->second.size() < 3) {
				iter->second.push_back(page);
			}
		    if (iter->second.size() == 3) {
				stringstream sk;
				int i = 0;
				for (auto li = iter->second.begin(); li != iter->second.end(); ++li, ++i) {
					sk << *li;
					if (i < 2)
						sk << "->";
				}
				string key = sk.str();
				++counts[key];
			}
		}
		else {
			list<string> v;
			v.push_back(page);
			mm[user_id] = v;
		}



	}



	for (auto it = counts.begin(); it != counts.end(); ++it)
		cout << it->first << " : " << it->second << "\n";

}
