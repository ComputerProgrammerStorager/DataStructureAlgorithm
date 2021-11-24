/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

 

Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1
Example 3:

Input: coins = [1], amount = 0
Output: 0
Example 4:

Input: coins = [1], amount = 1
Output: 1
Example 5:

Input: coins = [1], amount = 2
Output: 2
 

Constraints:

1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104
*/

// naive recursive solution 
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        return coinchange(coins,amount);
    }
    
    long coinchange(vector<int> const& coins, int remain)
    {
        if ( remain == 0 )
            return 0;
        long min_coin = LONG_MAX;
        for ( int c : coins )
        {
            if ( remain < c )
                continue;
            min_coin = min(min_coin, coinchange(coins,remain-c) + 1);
        }
        
        return min_coin;
    }
};

// To arrive at amount @amount, we could start from (@amount-c) for all c in coins, similar to the climb stairs
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1,amount+1);
        dp[0] = 0;
        for ( int i = 1; i <= amount; i++ )
        {
            for ( int c : coins )
            {
                if ( i - c >= 0 )
                    dp[i] = min(dp[i],dp[i-c]+1);
            }
        }
        
        return dp[amount] == amount+1 ? -1 : dp[amount];
    }
};