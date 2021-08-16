/*
Implement pow(x, n), which calculates x raised to the power n (i.e., xn).

Example 1:

Input: x = 2.00000, n = 10
Output: 1024.00000
Example 2:

Input: x = 2.10000, n = 3
Output: 9.26100
Example 3:

Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
 

Constraints:

-100.0 < x < 100.0
-231 <= n <= 231-1
-104 <= xn <= 104
*/


// Naive brute force approach 
class Solution {
public:
    double myPow(double x, int n) {
        long long N = n;
        if ( n < 0 )
        {
            x = 1/x;
            N = -N;
        }
        
        double ans = 1;
        while ( N-- > 0 )
        {
            ans *= x;
        }
        
        return ans;
    }
};

// we can use fast power recursively
// recursively calculate the half result and multiple one more time if it has odd number of request
class Solution {
public:
    double myPow(double x, int n) {
        long long N = n;
        if ( n < 0 )
        {
            x = 1/x;
            N = -N;
        }
        
        return fastpower(x,N);
    }
    
    double fastpower(double x, long long n)
    {
        if ( n == 0 )
            return 1.0;
        double half = fastpower(x,n/2);
        double res = half * half;
        if ( n % 2 )
            res *= x;
        return res;
    }
};

// this is an iterative approach levearing x^a * x^b = x^(a+b)
// So we check each of the bits of exponential N and accumulate the product as we progress all of its bits 
class Solution {
public:
    double myPow(double x, int n) {
        long long N = n;
        if ( n < 0 )
        {
            x = 1/x;
            N = -N;
        }
        
        double ans = 1;
        double current_power = x;
        for ( long long i = N; i; i /= 2 )
        {
            if ( i & 1 )
            {
                ans *= current_power;
            }
            current_power *= current_power;
        }
        
        return ans;
    }
};