#include <vector>

using namespace std;

int count(vector<int> ar, int n){
    int m = ar.size();
    vector<int> table(n+1, 0);
    
    table[0] = 1;
    
    for(int i = 0; i < m; ++i){
        for(int j = ar[i]; j <= n; ++j){
            table[j] += table[j - ar[i]];
        }            
    }
    
    return table[n];    
}
