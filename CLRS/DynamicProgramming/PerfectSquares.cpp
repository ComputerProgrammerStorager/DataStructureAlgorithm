/*
Given an integer n, return the least number of perfect square numbers that sum to n.

A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

 

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
 

Constraints:

1 <= n <= 104
*/

// To reach a given value n, the last step could choose any perfect square v based on the step where we are at n-v. 
// quite similar to stair climbing or Fibonacci... suitable for dynamic programming 
// it's recurrence relationship is as following: 
// dp[val] = dp[val-s] + 1, for all perfect squares 

class Solution {
public:
    int numSquares(int n) {
        // numSquare[i] = min(numSquare[i-k]+1), for all k 
        vector<int> dp(n+1,INT_MAX);
        dp[0] = 0;
        int max_square = sqrt(n) + 1;
        vector<int> squares;
        for ( int i = 1; i <= max_square; i++ )
        {
            squares.push_back(i*i);
        }
        
        for ( int val = 1; val <= n; val++ )
        {
            for ( auto s : squares )
            {
                if ( val < s )
                    break;
                dp[val] = min(dp[val],dp[val-s]+1);
            }
        }
        
        return dp[n];
    }
};

// check from one to n 
class Solution {
public:
    int numSquares(int n) {
        unordered_set<int> squares;
        for ( int i = 1; i <= sqrt(n) + 1; i++ )
            squares.insert(i*i);
        for ( int i = 1; i <= n; i++ )
            if ( is_divided(n,i,squares) )
                return i;
        return -1;
    }
    
    bool is_divided(int n, int cnt, unordered_set<int> &squares)
    {
        if ( cnt == 1 )
            return squares.count(n);
        for ( auto s : squares )
        {
            if ( is_divided(n-s,cnt-1,squares) ) 
                return true;
        }
        
        return false;
    }
};

// This can sum problem visually formulate a n-ary tree with each node representing an decreasing target sum and the node at the same level representing 
// having consumed the same amount of squares (i.e., levels). The it turns to find the first level that has any of the squares. 
class Solution {
public:
    int numSquares(int n) {
        unordered_set<int> level_sum;
        unordered_set<int> squares;
        int step = 0;
        for ( int i = 1; i <= sqrt(n); i++ )
        {
            squares.insert(i*i);
        }
        
        level_sum.insert(n);
        while(!level_sum.empty())
        {
            step++;
            unordered_set<int> next_level_sum;
            for ( auto it : level_sum )
            {
                if ( squares.count(it) )
                    return step;
                for ( auto s : squares )
                    if ( it > s )
                        next_level_sum.insert(it-s);
            }
            level_sum.swap(next_level_sum);
        }
        
        return -1;
    }
};