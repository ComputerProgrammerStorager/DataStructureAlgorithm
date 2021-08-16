/*
Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.

Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.

Example 1:

Input: [1, 5, 2]
Output: False
Explanation: Initially, player 1 can choose between 1 and 2. 
If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2). 
So, final score of player 1 is 1 + 2 = 3, and player 2 is 5. 
Hence, player 1 will never be the winner and you need to return False.
 

Example 2:

Input: [1, 5, 233, 7]
Output: True
Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
 

Constraints:

1 <= length of the array <= 20.
Any scores in the given array are non-negative integers and will not exceed 10,000,000.
If the scores of both players are equal, then player 1 is still the winner.
*/

/* 
In this recursive method, we calculate the overall score upon each step, which the player has two options: choosing the first or the last score 
When the step is Player #1's turn, we want to return the max score, and when the step is Player#2's trun we want to return the min score, because the we will deduce the score from the overall score. 
*/
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        if ( nums.size() <=1 )
            return true;
        return winner(nums,0,nums.size()-1,1) >= 0;
    }
    
    int winner( vector<int>& nums, int s, int e, int turn )
    {
        if ( s == e )
            return turn * nums[s];
        int take_first = nums[s] * turn + winner(nums,s+1,e,(-1)*turn);
        int take_last = nums[e] * turn + winner(nums,s,e-1,(-1)*turn);
        return turn * max(turn*take_first,turn*take_last);
        // could also be written as 
    #if 0 
        if ( turn == 1 )
            return max(take_first,take_last);
        else 
            return min(take_first,take_last);
    #endif 
    }
};


// The same idea as the above, but avoid using a turn parameter. Moreover, it employs memoization 
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        if ( nums.size() <=1 )
            return true;
        unordered_map<string,int> m;
        return winner(nums,0,nums.size()-1,m) >= 0;
    }
    
    int winner( vector<int>& nums, int s, int e, unordered_map<string,int> &m)
    {
        if ( s == e )
            return nums[s];
        if ( m.count(to_string(s)+"+"+to_string(e)) )
            return m[to_string(s)+"+"+to_string(e)];
        int take_first = nums[s]  - winner(nums,s+1,e,m);
        int take_last = nums[e] - winner(nums,s,e-1,m);
        m[to_string(s)+"+"+to_string(e)] =  max(take_first,take_last);
        return m[to_string(s)+"+"+to_string(e)];
    }
};

// Dynamical programming !!! 
// dp[i][j] represents the maximum effective score that can be obtained for nums[i...j]
// since we assume every player plays optimally, so we need to deduce the maximum score that could optimally obtained by the next player 
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n,vector<int>(n,0));
        for ( int i = 0; i < n; i++ )
            dp[i][i] = nums[i];
        for ( int len = 1; len < n; len++ )
            for ( int i = 0, j = len; j < n; i++, j++ )
                dp[i][j] = max(nums[i]-dp[i+1][j],nums[j]-dp[i][j-1] );
        return dp[0][n-1] >= 0;
    }
};