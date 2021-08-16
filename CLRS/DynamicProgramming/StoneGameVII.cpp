/*
Alice and Bob take turns playing a game, with Alice starting first.

There are n stones arranged in a row. On each player's turn, they can remove either the leftmost stone or the rightmost stone from the row and receive points equal to the sum of the remaining stones' values in the row. The winner is the one with the higher score when there are no stones left to remove.

Bob found that he will always lose this game (poor Bob, he always loses), so he decided to minimize the score's difference. Alice's goal is to maximize the difference in the score.

Given an array of integers stones where stones[i] represents the value of the ith stone from the left, return the difference in Alice and Bob's score if they both play optimally.

 

Example 1:

Input: stones = [5,3,1,4,2]
Output: 6
Explanation: 
- Alice removes 2 and gets 5 + 3 + 1 + 4 = 13 points. Alice = 13, Bob = 0, stones = [5,3,1,4].
- Bob removes 5 and gets 3 + 1 + 4 = 8 points. Alice = 13, Bob = 8, stones = [3,1,4].
- Alice removes 3 and gets 1 + 4 = 5 points. Alice = 18, Bob = 8, stones = [1,4].
- Bob removes 1 and gets 4 points. Alice = 18, Bob = 12, stones = [4].
- Alice removes 4 and gets 0 points. Alice = 18, Bob = 12, stones = [].
The score difference is 18 - 12 = 6.
Example 2:

Input: stones = [7,90,5,1,100,10,10,2]
Output: 122
 

Constraints:

n == stones.length
2 <= n <= 1000
1 <= stones[i] <= 1000
*/

// Perceive this sequence of steps, at each step, Alice wants to maximize her score while minimizing Bob's score.. 
// So we can calculate the difference between their scores. 
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        vector<int> prefix_sum(n+1,0);
        for ( int i = 1; i <= n; i++ )
        {
            prefix_sum[i] = prefix_sum[i-1] + stones[i-1];
        }
        
        return FindDiff(prefix_sum,0,n-1,true);
    }
    
    int FindDiff( vector<int> const& prefix_sum, int s, int e, bool Alice )
    {
        int diff; 
        if ( s == e )
            return 0;
        int scoreRemoveFirst = prefix_sum[e+1] - prefix_sum[s+1];
        int scoreRemoveLast = prefix_sum[e] - prefix_sum[s];
        if ( Alice )
        {
            diff = max(scoreRemoveFirst + FindDiff(prefix_sum, s+1, e, !Alice), 
                       scoreRemoveLast + FindDiff(prefix_sum,s,e-1,!Alice) );
        }
        else 
        {
            diff = min(FindDiff(prefix_sum,s+1,e, !Alice) - scoreRemoveFirst, FindDiff(prefix_sum,s,e-1,!Alice) - scoreRemoveLast);
        }
        
        return diff;
    }
};

// We can add memoization to make it down to O(n^2)
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        vector<int> prefix_sum(n+1,0);
        vector<vector<int>> memo(n,vector<int>(n,INT_MAX));
        for ( int i = 1; i <= n; i++ )
        {
            prefix_sum[i] = prefix_sum[i-1] + stones[i-1];
        }
        
        return FindDiff(prefix_sum,0,n-1,true, memo);
    }
    
    int FindDiff( vector<int> const& prefix_sum, int s, int e, bool Alice, vector<vector<int>> &memo )
    {
        int diff; 
        if ( s == e )
            return 0;
        if ( memo[s][e] != INT_MAX )
            return memo[s][e];
        int scoreRemoveFirst = prefix_sum[e+1] - prefix_sum[s+1];
        int scoreRemoveLast = prefix_sum[e] - prefix_sum[s];
        if ( Alice )
        {
            diff = max(scoreRemoveFirst + FindDiff(prefix_sum, s+1, e, !Alice,memo), 
                       scoreRemoveLast + FindDiff(prefix_sum,s,e-1,!Alice,memo) );
        }
        else 
        {
            diff = min(FindDiff(prefix_sum,s+1,e, !Alice,memo) - scoreRemoveFirst, FindDiff(prefix_sum,s,e-1,!Alice,memo) - scoreRemoveLast);
        }
        memo[s][e] = diff;
        return diff;
    }
};

// At every step, we want to return the maximum difference 
// top-down dynamic programming 
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        vector<int> prefix_sum(n+1,0);
        vector<vector<int>> memo(n,vector<int>(n,INT_MAX));
        for ( int i = 1; i <= n; i++ )
        {
            prefix_sum[i] = prefix_sum[i-1] + stones[i-1];
        }
        
        return FindDiff(prefix_sum,0,n-1, memo);
    }
    
    int FindDiff( vector<int> const& prefix_sum, int s, int e,vector<vector<int>> &memo )
    {
        int diff; 
        if ( s == e )
            return 0;
        if ( memo[s][e] != INT_MAX )
            return memo[s][e];
        int scoreRemoveFirst = prefix_sum[e+1] - prefix_sum[s+1];
        int scoreRemoveLast = prefix_sum[e] - prefix_sum[s];
        diff = max(scoreRemoveFirst-FindDiff(prefix_sum,s+1,e,memo), scoreRemoveLast-FindDiff(prefix_sum,s,e-1,memo));
        return memo[s][e] = diff;
    }
};


// bottom-up dynamic programming, tabulation 
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int n = stones.size();
        vector<int> prefix_sum(n+1,0);
        vector<vector<int>> dp(n,vector<int>(n,0));
        for ( int i = 1; i <= n; i++ )
        {
            prefix_sum[i] = prefix_sum[i-1] + stones[i-1];
        }
        
        for ( int i = 0; i < n; i++ )
            dp[i][i] = 0;
        for ( int len = 2; len <= n; len++ )
        {
            for ( int s = 0; s <= n-len; s++ )
            {
                int e = s + len - 1;
                int scoreRemoveFirst = prefix_sum[e+1] - prefix_sum[s+1];
                int scoreRemoveLast = prefix_sum[e] - prefix_sum[s];
                dp[s][e] = max(scoreRemoveFirst-dp[s+1][e],scoreRemoveLast-dp[s][e-1]);
            }
        }
        
        return dp[0][n-1];
        
    }
};
