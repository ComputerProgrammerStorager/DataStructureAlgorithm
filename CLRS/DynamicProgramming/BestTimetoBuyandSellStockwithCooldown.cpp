/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:

After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
Example 2:

Input: prices = [1]
Output: 0
 

Constraints:

1 <= prices.length <= 5000
0 <= prices[i] <= 1000
*/


// state: held, reset, sold
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // sold[i] = held[i-1] + prices[i]
        // held[i] = max(reset[i-1]-prices[i],held[i-1]);
        // reset[i] = max(reset[i-1],sold[i-1])

        int n = prices.size();
        vector<int> sold(n,0),held(n,0),reset(n,0);
        held[0] = -prices[0];
        for ( int i = 1; i < n; i++ ){
            sold[i] = held[i-1] + prices[i];
            held[i] = max(reset[i-1]-prices[i],held[i-1]);
            reset[i] = max(reset[i-1],sold[i-1]);
        }

        return max(sold[n-1],reset[n-1]);
    }
};