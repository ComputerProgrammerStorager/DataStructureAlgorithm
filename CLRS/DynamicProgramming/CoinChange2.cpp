/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.

You may assume that you have an infinite number of each kind of coin.

The answer is guaranteed to fit into a signed 32-bit integer.

 

Example 1:

Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
Example 2:

Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.
Example 3:

Input: amount = 10, coins = [10]
Output: 1
 

Constraints:

1 <= coins.length <= 300
1 <= coins[i] <= 5000
All the values of coins are unique.
0 <= amount <= 5000

*/

// recursive + memoization 
// The key technique to avoid duplicates is to ensure that after a coin has been considered, it will no longer be considered... extremely helpful visulize it in a recursive tree
// Then we can define a recursive function which defines a search starting from a given position..then we have to choices "to be" or "not to be". 

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<vector<int>> memo(coins.size(), vector<int>(amount+1,-1));
        return dfs(coins,0,0,amount,memo);
    }
    int dfs(vector<int> const& coins, int idx, int cur_amt, int target, vector<vector<int>> &memo) 
    {
        if ( cur_amt > target || idx == coins.size() )
            return 0;
        if ( cur_amt == target )
            return 1;
        if ( memo[idx][cur_amt] != -1 )
            return memo[idx][cur_amt];
        
        return memo[idx][cur_amt] = dfs(coins,idx, cur_amt+coins[idx], target,memo) + dfs(coins,idx+1,cur_amt,target,memo);
    }
};

// as usual we can translate a recursion + memo to dynamic programming solution 
// dp[idx][amt]: denotes the number of combinations using up to the idx_th coin amounting to @amt. 
// Then to consider the next coin for all amounts, we could either a. use the amount or b. not use the amount
// For case a: it depends on the number of combinations using the same coin, but has a less amount (only if the target amount is larger than the current coin)
// For case b: it depends on the number of combinations using only previous coins 
// Therefore we have the recurrence relationship as following: 
//     dp[i][amt] = dp[i-1][amt] 
//   if (coins[i] >= amt )
//     dp[i][amt] += dp[i][amt-coins[i]]
// The following table shows the dp table for amount = 5, and coins[] = {1,2,5}.  We fill the table from right to left and bottom to up 

//   coins\amount        5   4   3   2   1   0
//        1              4   3   2   2   1   1
//        2              1   1   0   1   0   1
//        5              1   0   0   0   0   1

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<vector<int>> dp(coins.size(), vector<int>(amount+1,0));
        for ( int i = 0; i < coins.size(); i++ )
            dp[i][0] = 1;
        for ( int amt = 1; amt <= amount; amt++ )
        {
            if ( amt >= coins[0] )
                dp[0][amt] = dp[0][amt-coins[0]];
        }
            
        for ( int c = 1; c < coins.size(); c++ )
        {
            for ( int amt = 1; amt <= amount; amt++ )
            {
                dp[c][amt] = dp[c-1][amt];
                if ( amt >= coins[c] )
                    dp[c][amt] += dp[c][amt-coins[c]];
            }
        }
        
        return dp[coins.size()-1][amount];
    }
};

// Noticing we only use one element from the previous [idx-1][amt], we can further reduce the space complexity by using only O(n) 
// Let dp[amt] denote the number of combinations using up to the previous coin, then prev[0] = 1, meaning there is only one combination where 
// no coins was ever used and the amount is 0 
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount+1,0);
        dp[0] = 1;
        for ( int c : coins )
            for ( int amt = 1; amt <= amount; amt++ )
            {
                if ( amt >= c )
                    dp[amt] += dp[amt-c];
            }
        
        return dp[amount];
    }
};