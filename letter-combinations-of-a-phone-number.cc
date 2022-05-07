// Time:  O(n * 4^n)
// Space: O(1)

// iterative solution
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        static const vector<string> lookup = {" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        
        if (empty(digits)) {
            return {};
        }
        int total = 1;
        for (const auto& digit : digits) {
            total *= size(lookup[digit - '0']);
        }
        vector<string> result;
        for (int i = 0; i < total; ++i) {
            int base = total;
            string curr;
            for (const auto& digit : digits) {
                const auto& choices = lookup[digit - '0'];
                base /= size(choices);
                curr.push_back(choices[(i / base) % size(choices)]);
            }
            result.emplace_back(move(curr));
        }
        return result;
    }
};
