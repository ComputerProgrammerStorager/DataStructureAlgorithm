/*
Given an array of digits which is sorted in non-decreasing order. You can write numbers using each digits[i] as many times as we want. For example, if digits = ['1','3','5'], we may write numbers such as '13', '551', and '1351315'.

Return the number of positive integers that can be generated that are less than or equal to a given integer n.

 

Example 1:

Input: digits = ["1","3","5","7"], n = 100
Output: 20
Explanation: 
The 20 numbers that can be written are:
1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
Example 2:

Input: digits = ["1","4","9"], n = 1000000000
Output: 29523
Explanation: 
We can write 3 one digit numbers, 9 two digit numbers, 27 three digit numbers,
81 four digit numbers, 243 five digit numbers, 729 six digit numbers,
2187 seven digit numbers, 6561 eight digit numbers, and 19683 nine digit numbers.
In total, this is 29523 integers that can be written using the digits array.
Example 3:

Input: digits = ["7"], n = 8
Output: 1
 

Constraints:

1 <= digits.length <= 9
digits[i].length == 1
digits[i] is a digit from '1' to '9'.
All the values in digits are unique.
digits is sorted in non-decreasing order.
1 <= n <= 109
*/

// Assume the given val n has k digits, then it's obvious that all numbers having (1,k-1) digits are less than n
// The big part is how to calculate the valid numbers which have the same length as the given number, which falls into two cases:
// 1. If the highest is less than, then we have pow(n,k-1) valid numbers
// 2. If the highest is equal to a choice, then we next to look at the next order, and possibly continuer recursively. 
// The case 2 gives us a hint to us dynamic programming 

// dp[i] represents the count of valid numbers using s[i...k-1], with dp[k] = 1
class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string num = to_string(n);
        int res = 0, k = num.size();
        // the same length dp[i]: num[i...k-1]
        vector<int> dp(k+1,0);
        dp[k] = 1;
        for ( int i = 1; i < k; i++ )
            res += pow(digits.size(),i);
        for ( int i = k-1; i >= 0; i--)
        {
            // num[i]: 
            for (auto c : digits )
            {
                if ( c[0] < num[i] )
                {
                    dp[i] += pow(digits.size(),k-i-1);
                }
                else if ( c[0] == num[i] )
                {
                    dp[i] += dp[i+1];
                }
            }
        }
        
        return res + dp[0];
    }
};