#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

void print_sums(vector<int>& coins, int n) {

    unordered_set<int> st;
    st.insert(0);
    
    for (int i = 1; i < n;  ++i) {
        for (int j = 0; j < coins.size(); ++j) {
            if (st.find(i - coins[j]) != st.end()) {
                if (st.find(i) == st.end()) {
                    st.insert(i);
                    cout << i << "\n";
                }
            }
        }
    }
}

int main()
{
    vector<int> coins = { 10, 15, 55 };

    print_sums(coins, 1000);
}
