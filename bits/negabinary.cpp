#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string as_string(int n) {
	string str;
	stringstream ss;
	ss << n;
	ss >> str;
	return str;
}

string negabinary(int n) {
	if (n == 0)
		return "0";

	string res = "";
	int base = -2;
	while (n != 0) 	{

		int remainder = n % base;
		n /= base;

		if (remainder < 0) {
			remainder += (-base);
			n += 1;
		}

		res = as_string(remainder) + res;
	}

	return res;
}

int main() {
	cout << negabinary(-15) << endl;//'110001'
	cout << negabinary(2) << endl;  // '110'
	cout << negabinary(13) << endl; // '11101'
}
