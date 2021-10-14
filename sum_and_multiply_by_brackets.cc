#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

int get_sum(string input) {
    vector<vector<int> > vv(input.size());

    int cur_mul = 0;
    for (int i = 0; i < input.size(); ++i) {
        
        if (input[i] == '[')
            ++cur_mul;
        else if (input[i] == ']')
            --cur_mul;
        else {
            if(input[i] != ',' && input[i] != ' ')
                vv[cur_mul].push_back(int(input[i] - '0'));
        }
    }

    int res = 0;
    for (int i = vv.size()-1; i > 0; --i) {
        if (vv[i].size() > 0) {
            for (int j = 0; j < vv[i].size(); ++j)
                res += vv[i][j];
            res *= (i);
                
        }
        
    }
    return res;
}

int main()
{

    int res = get_sum("[8, 3, 2, [5, 6, [9]], 6]");
}
