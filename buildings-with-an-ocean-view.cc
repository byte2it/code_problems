// Time:  O(n)
// Space: O(1)
class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        vector<int> result;
        for (int i = size(heights) - 1; i >= 0; --i) {
            if (empty(result) || heights[i] > heights[result.back()]) {
                result.emplace_back(i);
            }
        }
        return {rbegin(result), rend(result)};
    }
};
