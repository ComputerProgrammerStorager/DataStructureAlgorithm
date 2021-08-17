/*
There is a row of n houses, where each house can be painted one of three colors: red, blue, or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with the color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.

 

Example 1:

Input: costs = [[17,2,17],[16,16,5],[14,3,19]]
Output: 10
Explanation: Paint house 0 into blue, paint house 1 into green, paint house 2 into blue.
Minimum cost: 2 + 5 + 3 = 10.
Example 2:

Input: costs = []
Output: 0
Example 3:

Input: costs = [[7,6,2]]
Output: 2
 

Constraints:

costs.length == n
costs[i].length == 3
0 <= n <= 100
1 <= costs[i][j] <= 20
*/

class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        int res = INT_MAX;
        vector<vector<int>> dp(n,vector(3,0)); // dp[i][c]: the minimum cost of painting hourse i in color c
        if ( n == 0 )
            return 0;
        for ( int c = 0; c < 3; c++ )
            dp[0][c] = costs[0][c];
        for ( int i = 1; i < n; i++ )
        {
            for ( int cur_c = 0; cur_c < 3; cur_c++ )
            {
                int val = INT_MAX;
                for ( int prev_c = 0; prev_c < 3; prev_c++ )
                {
                    if ( prev_c != cur_c )
                        val = min(val, dp[i-1][prev_c]+costs[i][cur_c]);
                }
                dp[i][cur_c] = val;
            }
        }
        for ( int c = 0; c < 3; c++ )
            res = min(res, dp[n-1][c]);
        return res;
    }
};

// recursion with memoization 
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int n = costs.size();
        if ( n == 0 )
            return 0;
        unordered_map<string, int> memo;
        return min(paint(0,0,memo,costs),min(paint(0,1,memo,costs),paint(0,2,memo,costs)));
    }
    
    int paint(int h, int c, unordered_map<string, int> &memo, vector<vector<int>> const &costs)
    {
        string key = to_string(h)+"+"+to_string(c);
        if (memo.count(key))
            return memo[key];
        int total_cost = costs[h][c];
        if ( h == costs.size() - 1 ) 
        {
            
        }
        else if ( c == 0 )
        {
            total_cost += min(paint(h+1,1,memo,costs),paint(h+1,2,memo,costs));
        } else if ( c == 1 )
        {
            total_cost += min(paint(h+1,0,memo,costs),paint(h+1,2,memo,costs));
        } else if ( c == 2 ) {
            total_cost += min(paint(h+1,0,memo,costs),paint(h+1,1,memo,costs));
        }
        memo[key] = total_cost;
        return total_cost;
    }
};