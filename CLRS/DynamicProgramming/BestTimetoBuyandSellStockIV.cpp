/*
You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
 

Constraints:

1 <= k <= 100
1 <= prices.length <= 1000
0 <= prices[i] <= 1000
*/

// The problem is equivalent to finding 2*k ( if there are ) days to buy or sell, while buys and sells follow the patther {B,S,B,S...} 
// dp[j] denotes the profit ending on the day @i using up to j buys and sells 
// A quick scenarios is 2*k >= n, in where we can freely do buy and sell every day, i.e., unlimited transactions. 
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<int> dp(2*k+1, INT_MIN);
        if ( 2*k >= n )
            return quickpath(prices);
        dp[0] = 0;
        for ( int i = 0; i < n; i++ ) {
            for (int j = 1; j <= min(2*k,i+1); j++ ) {
                dp[j] = max(dp[j],dp[j-1] + (j%2? -prices[i] : prices[i]));
            }
        }

        return dp[2*k];
        
    }

    int quickpath(vector<int>& prices) {
        int n = prices.size(), res = 0;
        for ( int i = 0; i < n-1; i++ ) {
            if ( prices[i] < prices[i+1] )
                res += prices[i+1] - prices[i];
        }

        return res;
    }
};