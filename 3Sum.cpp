// https://leetcode.com/problems/3sum/description/

#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;

        int n = nums.size();
        if(n < 3) return res;
        std::sort(nums.begin(), nums.end());

        if(nums[n-1] == 0 && nums[0] == 0){
            vector<int> v = {0,0,0};
            res.push_back(v);
            return res;
        }

        unordered_set<string> unique;

        for (int i=0; i<n-1; i++){
            int l = i + 1;
            int r = n - 1;
            int x = nums[i];
            while (l < r) {
                if (x + nums[l] + nums[r] == 0) {
                    vector<int> v = { x, nums[l], nums[r]};
                    std::sort(v.begin(), v.end());
                    char sz[128] = {0};
                    sprintf(sz, "%d%d%d\0", v[0], v[1], v[2]);
                    if(unique.find(sz) == unique.end()){
                        res.push_back(v);
                        unique.insert(sz);
                    }
                    l++;
                    r--;
                }

                else if (x + nums[l] + nums[r] < 0)
                    l++;

                else
                   r--;
            }
        }

        std::sort(res.begin(), res.end());
        return res;
    }
};
