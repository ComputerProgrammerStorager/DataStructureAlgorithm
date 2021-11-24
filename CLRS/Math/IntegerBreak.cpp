/*
Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the product of those integers.

Return the maximum product you can get.

 

Example 1:

Input: n = 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.
Example 2:

Input: n = 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
 

Constraints:

2 <= n <= 58
*/

// the main idea to only divide the number into 2 and 3s, with preference to 3. The only exception if 4, which should be divided to 2 + 2. 
class Solution {
public:
    int integerBreak(int n) {
        int product = 1, threes = 0, twos = 0;
        if ( n < 5 )
        {
            switch(n)
            {
                case 2:
                    return 1;
                case 3: 
                    return 2;
                case 4:
                    return 4;
            }
        }
        if ( n % 3 == 0 )
        {
            threes = n / 3;
            twos = 0;
        }
        else if ( n % 3 == 1 )
        {
            threes = (n-4) / 3;
            twos = 2;
        }
        else if ( n % 3 == 2 )
        {
            threes = (n-2) / 3;
            twos = 1;
        }
        
        while ( threes-- > 0 )
        {
            product *= 3;
        }
        while ( twos-- > 0 )
        {
            product *= 2;
        }
        
        return product;
    }
};

// same idea but more concise
class Solution {
public:
    int integerBreak(int n) {
        if ( n == 2 )
            return 1;
        if ( n == 3 )
            return 2;
        if ( n == 4 )
            return 4;
        if ( n % 3 == 0 )
            return pow(3,n/3);
        else if ( n % 3 == 1 )
            return pow(3,(n-4)/3) * 4;
        else 
            return pow(3,n/3) * 2;
    }
};

// we can also use dynamic programming
// Note dp[2] = 2 and dp[3] = 3 because if it's recursively reached, then we don't need to break it any further
class Solution {
public:
    int integerBreak(int n) {
        if ( n == 2 )
            return 1;
        if ( n == 3 )
            return 2;
        vector<int> dp(n+1,0);
        dp[2] = 2;
        dp[3] = 3;
        for ( int i = 4; i <= n; i++ )
        {
            int maxprod = 0;
            for ( int j = 2; j <= i/2; j++ )
            {
                maxprod = max(maxprod,dp[j]*dp[i-j]);
            }
            dp[i] = maxprod;
        }
        return dp[n];
    }
};

// Note the dp[i] is initialized to i if it's not equal to n (meaning it doesn't divide any longer because it's internal to the recursion tree) and to 0 if it's equal to n
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n+1,0);     // interger to max prod 
        dp[1] = 1;
        for ( int i = 2; i <= n; i++ )
        {
            dp[i] = i==n ? 0 : i;
            for ( int l = 1; l < i; l++ )
            {
                dp[i] = max(dp[i], dp[l] * dp[i-l]);
            }
  
        }
        
        return dp[n];
    }
};