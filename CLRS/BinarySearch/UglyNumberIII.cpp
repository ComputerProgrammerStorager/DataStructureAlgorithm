/*
An ugly number is a positive integer that is divisible by a, b, or c.

Given four integers n, a, b, and c, return the nth ugly number.

 

Example 1:

Input: n = 3, a = 2, b = 3, c = 5
Output: 4
Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.
Example 2:

Input: n = 4, a = 2, b = 3, c = 4
Output: 6
Explanation: The ugly numbers are 2, 3, 4, 6, 8, 9, 10, 12... The 4th is 6.
Example 3:

Input: n = 5, a = 2, b = 11, c = 13
Output: 10
Explanation: The ugly numbers are 2, 4, 6, 8, 10, 11, 12, 13... The 5th is 10.
Example 4:

Input: n = 1000000000, a = 2, b = 217983653, c = 336916467
Output: 1999999984
 

Constraints:

1 <= n, a, b, c <= 109
1 <= a * b * c <= 1018
It is guaranteed that the result will be in range [1, 2 * 109].

*/

// naive approach 
class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        int res;
        priority_queue<long,vector<long>,greater<long>> pq;
        for ( int i = 1; i <= n; i++ )
        {
            pq.push((long)a*i);
            pq.push((long)b*i);
            pq.push((long)c*i);
        }
        
        for ( int i = 0; i < n; i++ )
        {
            res = pq.top();
            while( pq.top() == res )
                pq.pop();
        }
        
        return res;
    }
};

// This method is more math dependent and new number theory knowledge. Actually, it is math in elementary school :-) 
// First, let understand the following two concepts:
// 1. Greatest Common Divisor(GCD) of two numbers(a,b): gcd(a,b) == a==0? b : gcd(b%a,a)
// 2. Least Common Multiple(LCM) of two numbers(a,b): lcm(a,b) = (a*b)/gcd(a,b); lcm has a property, i.e., lcm(a,b,c) == lcm(a,lcm(b,c))
// Then given a value k we can calcuate how many numbers less than value and have factors either of a or b as following:
// f(k) = k/a + k/b - k/lcm(a,b)
// similary for three factors, we have 
// f(k) = k/a + k/b + k/c - k/lcm(a,b) - k/lcm(b,c) - k/lcm(a,c) + k/lcm(a,lcm(b,c))
// Having the above knowlege, then we can do a binary search on the value 
class Solution {
public:
    int nthUglyNumber(int n, int a, int b, int c) {
        // assume a <= b <= c
        long l = 0, r = 2e9;
        long lcm_ac = lcm(a,c), lcm_ab = lcm(a,b), lcm_bc = lcm(b,c), lcm_abc = lcm(a,lcm(b,c));
        while( l < r )
        {
            long mid = l+(r-l)/2;
            long cnt = mid/a+mid/b+mid/c-mid/lcm_ab-mid/lcm_bc-mid/lcm_ac+mid/lcm_abc;
            if ( cnt < n )
            {
                l = mid+1;
            }
            else
                r = mid;
        }
        return r;
    }
    
    
    long gcd(long a, long b)
    {
        return a == 0 ? b : gcd(b%a, a);
    }
    
    long lcm(long a, long b)
    {
        return (a*b) / gcd(a,b);
    }
};