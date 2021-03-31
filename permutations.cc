#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

class Solution {
public:
	void print(string str) {
		stack<string> st;
		st.push(str);

		while (!st.empty())
		{
			string str = st.top();
			st.pop();

			size_t index = str.find('?');

			if (index != string::npos) {

				str[index] = '0';
				st.push(str);

				str[index] = '1';
				st.push(str);
			}

			else
				cout << str << endl;
		}
	}
};
