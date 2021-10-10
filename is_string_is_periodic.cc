#include <iostream>
#include <string>
using namespace std;

std::pair<int, string> getPeriod(string str) {
    int len = str.length();
    int i;

    std::pair<int, string> res = std::make_pair(0, "");

    for (i = 1; i <= len / 2; i++) {
        string period = str.substr(0, i);
        string tmp = str;
        bool flag = true;

        int pp = 0;
        while (flag && tmp.length() > 0) {
            if (tmp.find(period) == 0) {
                tmp = tmp.substr(i);
            }
            else {
                flag = false;
            }
            ++pp;
        }

        if (flag == true) {
            res.first = pp;
            res.second = period;
            return res;
        }
    }
    return res;
}

int main() {

    auto res = getPeriod("ababab");
    std::cout << res.first << " : " << res.second << "\n";

    auto res2 = getPeriod("xxxxxx");
    std::cout << res2.first << " : " << res2.second << "\n";

    auto res3 = getPeriod("aabbaaabba");
    std::cout << res3.first << " : " << res3.second << "\n";

    return 0;
}
