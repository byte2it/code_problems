#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& R) {
        vector<bool> vis(R.size(), false);
        vis[0] = true;
        stack<int> stk = stack<int>({ 0 });
        int count = 1;
        while (stk.size()) {
            vector<int> keys = R[stk.top()]; stk.pop();
            for (int k : keys)
                if (!vis[k]) stk.push(k), vis[k] = true, count++;
        }
        return R.size() == count;
    }
};

int main() {
    vector<vector<int>> case1 = { {1 }, { 2 }, { 3 }, {} };

    vector<vector<int>> case2 = { {1,3} ,{3,0,1},{2},{0} };

    Solution s;
    cout << s.canVisitAllRooms(case1) << ", " << s.canVisitAllRooms(case2) << std::endl;

}
