#include <vector>
#include <limits.h>

using namespace std;

int min_coins_rec(vector<int> coins, int value){

   if (value == 0) return 0;
 
   // Initialize result
   int res = INT_MAX;
   int m = coins.size();
 
   // Try every coin that has smaller value than 'value'
   for (int i=0; i<m; i++) {
     if (coins[i] <= value) {
         int sub_res = min_coins_rec(coins, value-coins[i]);
 
         // Check for INT_MAX to avoid overflow and see if
         // result can minimized
         if (sub_res != INT_MAX && sub_res + 1 < res)
            res = sub_res + 1;
     }
   }
   return res;
}

int min_coins(vector<int> coins, int value){
    // table[i] will be storing the minimum number of coins
    // required for i value.  So table[V] will have result
    int table[value+1];
 
    // Base case (If given value V is 0)
    table[0] = 0;
    int m = coins.size();
 
    // Initialize all table values as Infinite
    for (int i=1; i<=value; i++)
        table[i] = INT_MAX;
 
    // Compute minimum coins required for all
    // values from 1 to V
    for (int i=1; i<=value; i++) {
        // Go through all coins smaller than i
        for (int j=0; j<m; j++){
          if (coins[j] <= i) {
              int sub_res = table[i-coins[j]];
              if (sub_res != INT_MAX && sub_res + 1 < table[i])
                  table[i] = sub_res + 1;
          }
        }
    }
    return table[value];
}
