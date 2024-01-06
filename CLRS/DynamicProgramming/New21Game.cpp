/*
Alice plays the following game, loosely based on the card game "21".

Alice starts with 0 points and draws numbers while she has less than k points. During each draw, she gains an integer number of points randomly from the range [1, maxPts], where maxPts is an integer. Each draw is independent and the outcomes have equal probabilities.

Alice stops drawing numbers when she gets k or more points.

Return the probability that Alice has n or fewer points.

Answers within 10-5 of the actual answer are considered accepted.

 

Example 1:

Input: n = 10, k = 1, maxPts = 10
Output: 1.00000
Explanation: Alice gets a single card, then stops.
Example 2:

Input: n = 6, k = 1, maxPts = 10
Output: 0.60000
Explanation: Alice gets a single card, then stops.
In 6 out of 10 possibilities, she is at or below 6 points.
Example 3:

Input: n = 21, k = 17, maxPts = 10
Output: 0.73278
 

Constraints:

0 <= k <= n <= 104
1 <= maxPts <= 104
*/

// We need to add a random number from [1,W] to your current point when it is less than K. And we want to find the probiblity of your point being less than or equal to N, when the game ends 
// So when and how you would end the game? 
// Suppose your current point is x and denote its probility as f(x). Assume x < K, otherwise, our game ends at x. 
// Also assume, we get y points for the next draw from [1,W], our next score would be x+y, and probility is f(x+y). y could be 1,2,3...W-1, W, each at probility of 1/W. 
// First, we want to clarify that when K + W <= n, then the probility is 1.0.. because with one jump starting from K, all possible results are not larger than n, thus it's guaranteed any result satisfies the condition
// we only need to consider the case where n >= K. 
// Second, alternatively, we can reach x from x-1,x-2,...x-W, each at a probility of 1/W, mathematically, we have:
// f(x) = (f(x-1) + f(x-2) + f(x-W))/W. 
// Third, let's look at the last step, the last possible score that we need to jump from is K-1, and the highest score we can reach is W+K-1, i.e., get the largest score for the last step. 
// and we need to check if the last step goes beyond n, and n >= K, therefore we define a dp size being n+W to avoid out-of-range access. 
// Fourth, dp[n+W] is our entire state space, and we know the last step's W transitions as following: 
// K-1 ----> K,    when y is 1 with probabililty of 1/W if K <= n
// K-1 ----> K+1,  when y is 2 with probabililty of 1/W if K+1 <= n
// K-1 ----> K+2,  when y is 3 with probabililty of 1/W if K+2 <= n
// ...........................
// K-1 ----> K+W-2, when y is W-1 with probility of 0 if if K+W-2 > n
// K-1 ----> K+W-1, when y is W   with probility of 0 if if K+W-1 > n
// In summary, we are counting the number scores which are less than or equal to n and can be reached from K-1 
// Once we have the last window, we can sliding leftward to calculate less scores' probabilies 
// and the result is dp[0], as our starting score is 0 

class Solution {
public:
    double new21Game(int N, int K, int W) {
        vector<double> dp(N+W);
        if ( K+W <= N ) 
            return 1.0;
        for ( int i = K; i <= N; i++ ) 
            dp[i] = 1;
        for ( int i = N+1; i < N+W; i++ )
            dp[i] = 0;
        
        double win_sum = 0.0;
        for ( int i = K-1; i >= 0; i-- ) {
            if ( i == K-1 ) {
                for ( int k = 1; k <= W; k++ ) 
                    win_sum += dp[i+k];
                dp[i] = win_sum / W;
            } else {
                win_sum -= dp[i+W+1];
                win_sum += dp[i+1];
                dp[i] = win_sum / W;
            }
        }

        return dp[0];
    }
};

// of course, dynamic programming's ancestor is recursion + memoization 
class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        unordered_map<int,double> memo;  //start score vs prob of score being less and equal to n 
        if ( k == 0 ) {
            return k <= n;
        }
        helper(memo,n,k,maxPts,0);
        return memo[0];
    }

    double helper(unordered_map<int,double>& memo, int n, int k, int maxPts, int score) {
        if ( score >= k ) {
            if ( score <= n )
                return 1;
            return 0;
        }

        if (memo.count(score) != 0) {
            return memo[score];
        }

        double prob = 0;
        for (int i = 1; i <= maxPts; i++ ) {
            prob += helper(memo,n,k,maxPts,score+i);
        }

        return  memo[score] = prob / maxPts;
    }
};