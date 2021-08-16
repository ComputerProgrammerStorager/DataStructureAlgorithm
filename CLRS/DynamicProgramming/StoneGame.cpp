/*
Alex and Lee play a game with piles of stones.  There are an even number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].

The objective of the game is to end with the most stones.  The total number of stones is odd, so there are no ties.

Alex and Lee take turns, with Alex starting first.  Each turn, a player takes the entire pile of stones from either the beginning or the end of the row.  This continues until there are no more piles left, at which point the person with the most stones wins.

Assuming Alex and Lee play optimally, return True if and only if Alex wins the game.

 

Example 1:

Input: piles = [5,3,4,5]
Output: true
Explanation: 
Alex starts first, and can only take the first 5 or the last 5.
Say he takes the first 5, so that the row becomes [3, 4, 5].
If Lee takes 3, then the board is [4, 5], and Alex takes 5 to win with 10 points.
If Lee takes the last 5, then the board is [3, 4], and Alex takes 4 to win with 9 points.
This demonstrated that taking the first 5 was a winning move for Alex, so we return true.
 

Constraints:

2 <= piles.length <= 500
piles.length is even.
1 <= piles[i] <= 500
sum(piles) is odd.
*/

// Score function returns the best score when facing with piles[s...e], regardless of the player 
// which will be the total sum minus the opponent's score 
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> memo(n,vector<int>(n,INT_MIN));
        int total_sum = accumulate(piles.begin(),piles.end(),0);
        int my_best = Score(piles,0,piles.size()-1,memo);
        return my_best > total_sum - my_best;
    }
    
    int Score( vector<int> const& piles, int s, int e, vector<vector<int>> &memo )
    {
        int sum = accumulate(piles.begin(),piles.end(),0);
        if ( s == e )
            return piles[s];
        if ( memo[s][e] != INT_MIN )
            return memo[s][e];
        return memo[s][e] = max(sum - Score(piles,s+1,e,memo), sum - Score(piles,s,e-1,memo));
    }
};


// if there is even number of steps and the even part and the odd part are not equal, then the first player will always win 
// because it has the choice to choose either even or odd part 
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};

// helper function returns the result for the step in which player's trun, current scores, and current range of stones. 
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return helper(piles,0,0,0,piles.size()-1,0);
    }
    
    bool helper( vector<int> const& piles, int play0_score, int play1_score, int s, int e, int player )
    {
        if ( s > e )
            return play0_score > play1_score;
        if ( player == 0 )
            return helper(piles,play0_score+piles[s],play1_score,s+1,e,1) || helper(piles, play0_score+piles[e],play1_score,s,e-1,1);
        else
            return helper(piles,play0_score, play1_score+piles[s],s+1,e,0) || helper(piles,play0_score,play1_score+piles[e],s,e-1,0);
    }
};


// helper function returns the overall score 
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<vector<int>>> memo(n,vector(n,vector(2,INT_MIN)));
        return helper(piles,0,piles.size()-1,0,memo) > 0;
    }
    
    int helper( vector<int> const& piles, int s, int e, int player, vector<vector<vector<int>>> &memo)
    {       
        int overall_score;
        if ( s == e )
            return player == 0 ? piles[s] : -piles[s];
        if ( memo[s][e][player] != INT_MIN )
            return memo[s][e][player];
        if ( player == 0 )
        {
            overall_score = max(piles[s]+helper(piles,s+1,e,1, memo),piles[e]+helper(piles,s,e-1,1,memo));
        }
        else 
        {
            overall_score = min(-piles[s]+helper(piles,s+1,e,0,memo), -piles[e]+helper(piles,s,e-1,0,memo));
        }
        return memo[s][e][player] = overall_score;
    }
};

// dp[i][j] denotes the difference when facing array [i...j] regardless of player 
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n,vector(n,0));
        // dp[i][j] --> dp[i+1][j] and dp[i][j-1] 
        for ( int i = 0; i < n; i++ )
            dp[i][i] = piles[i];
        for ( int len = 2; len <= n; len++ )
            for ( int i = 0; i <= n-len; i++ )
            {
                int j = i + len - 1;
                dp[i][j] = max(piles[i]-dp[i+1][j],piles[j]-dp[i][j-1]);
            }
        
        return dp[0][n-1] > 0;
    }
};