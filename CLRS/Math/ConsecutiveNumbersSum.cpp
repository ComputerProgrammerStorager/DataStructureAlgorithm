/*
Given an integer n, return the number of ways you can write n as the sum of consecutive positive integers.

 

Example 1:

Input: n = 5
Output: 2
Explanation: 5 = 2 + 3
Example 2:

Input: n = 9
Output: 3
Explanation: 9 = 4 + 5 = 2 + 3 + 4
Example 3:

Input: n = 15
Output: 4
Explanation: 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
 

Constraints:

1 <= n <= 109
*/

/* 
Analysis: 
1. A number can have certain kinds of consecutive number sums, let's say it is k
2. Then the number can be represented as n = (x+1) + (x+2) + ... + (x+k), i.e., n = x*k + k(k+1)/2
3. Then we need to find the relationship between x and k.  Since k varies, we represent x using k: x = n/k - (k+1)/2
4. In order to be qualified for consecutive number sums, x has to be larger or equal than zero and must be an integer 
5. To satisfy the first condition, we have k <= sqrt(n/2+1/4) - 1/2. 
6. Therefore, we examine k from 1 to sqrt(n/2+1/4) - 1/2 cases and if any k numer leads to x being an integer, then it's an answer
*/

class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int upper = sqrt(2*n+0.25) - 0.5;
        int cnt = 0;
        for ( int i = 1; i <= upper; i++ )
        {
            if ((2 * n - i * (i+1)) % (2*i) == 0 )
                cnt++;
        }

        return cnt;
    }
};


// Python3 code 
class Solution:
    def consecutiveNumbersSum(self, n: int) -> int:
        cnt = 0
        upper = ceil((2*n+0.25)**0.5 - 0.5) + 1
        for k in range(1,upper):
            if (2*n - k*(k+1)) % (2*k) == 0: 
                cnt += 1
        return cnt