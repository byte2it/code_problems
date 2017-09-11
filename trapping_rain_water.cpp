class Solution {
public:
    int trap(vector<int>& height) {
        
        int n = height.size();
        if(n == 0) return 0;
        
        int water = 0;
        
        int left[n];
        left[0] = height[0];
        for(int i = 1; i < n; ++i){
            left[i] = max(left[i-1], height[i]);
        }
        
        int right[n];
        right[n-1] = height[n-1];
        for(int j = n-2; j >= 0; --j){
            right[j] = max(right[j+1], height[j]);
        }
        
        for(int k = 0; k < n; ++k){
            water += min(left[k], right[k]) - height[k];
        }
        
        return water;
    }
};
