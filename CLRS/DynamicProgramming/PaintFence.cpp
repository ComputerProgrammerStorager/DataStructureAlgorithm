/*

*/

// recursion with memoization 
// denote the number ways of n posts as W(n)
// for the nth post, it could be colored with the same color as the (n-1)th which leads to W(n-2) * (k-1) or it 
// could be colored as different from the (n-1)the, which leads to W(n-1) *(k-1);
class Solution {
public:
    int numWays(int n, int k) {
        unordered_map<int,int> m;
        return helper(n,k,m);
    }
    
    int helper( int n, int k, unordered_map<int,int> &m)
    {
        if ( m.count(n) )
            return m[n];
        switch(n)
        {
            case 0:
                return 0;
            case 1:
                return k;
            case 2: 
                return k*k;
        }
        return m[n] = helper(n-1,k,m) * (k-1) + helper(n-2,k,m) * (k-1);
    }
};


// bottom-up dynamical programming 
class Solution {
public:
    int numWays(int n, int k) {
        switch(n)
        {
            case 0:
                return 0;
            case 1:
                return k;
            case 2:
                return k*k;
        }
        
        vector<int> dp(n,0);
        dp[0] = k;
        dp[1] = k*k;
        for ( int i = 2; i < n; i++ )
        {
            dp[i] = (dp[i-2] + dp[i-1]) * (k-1);
        }
        
        return dp[n-1];
    }
};