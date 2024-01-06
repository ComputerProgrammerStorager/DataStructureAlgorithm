/*
Given a non-negative integer c, decide whether there're two integers a and b such that a2 + b2 = c.

 

Example 1:

Input: c = 5
Output: true
Explanation: 1 * 1 + 2 * 2 = 5
Example 2:

Input: c = 3
Output: false
 

Constraints:

0 <= c <= 231 - 1
*/


// the n square  is the sum of the first n odd number, i.e., 
// n^2 = 1 + 3 + 5 + ... + 2*n-1 = 2*1 - 1 + 2*2 - 1 + 2*3 - 1 + ... + 2*n - 1 = 2*sum(for i = 1 to n) - n = 2*n(n+1)/2 - n  = n^2
// this can be used to find if a number is a perfect square 
class Solution {
public:
    bool judgeSquareSum(int c) {
        for ( long a = 0; a * a <= c; a++ ) 
        {
            int b = c - (int)a*a;
            long i = 1, sum = 0;
            while( sum < b ) {
                sum += i;
                i += 2;
            }

            if ( sum == b )
                return true;
        }

        return false;
    }
};

// use square root 
class Solution {
public:
    bool judgeSquareSum(int c) {
        for ( long a = 0; a * a <= c; a++ ) 
        {
            double b = sqrt(c - (int)a*a);
            if ( b == (int)b ) 
                return true;
        }

        return false;
    }
};

// use binary search to find the perfect sqaure of 
class Solution {
public:
    bool judgeSquareSum(int c) {
        for ( long a = 0; a * a <= c; a++ ) {
            int b = c - (int)(a*a);
            if ( binary_search(0,b,b) )
                return true;
        }
        return false;
    }

    bool binary_search(long s, long e, long n ) {
        if ( s > e )
            return false;
        long m = s + (e-s)/2;
        if ( m*m == n ) 
            return true;
        if ( m*m > n )
            return binary_search(s,m-1,n);
        else
            return binary_search(m+1,e,n);
    }
};