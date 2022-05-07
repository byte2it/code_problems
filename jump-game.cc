// Time:  O(n)
// Space: O(1)

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach = 0;
        for(int i = 0; i <= reach && i < nums.size(); ++i) {
            reach = max(reach, i + nums[i]);
        }
        return reach >= nums.size() - 1;
    }
};
