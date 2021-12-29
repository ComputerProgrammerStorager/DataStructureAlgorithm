/*
You are given three positive integers: n, index, and maxSum. You want to construct an array nums (0-indexed) that satisfies the following conditions:

nums.length == n
nums[i] is a positive integer where 0 <= i < n.
abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
The sum of all the elements of nums does not exceed maxSum.
nums[index] is maximized.
Return nums[index] of the constructed array.

Note that abs(x) equals x if x >= 0, and -x otherwise.

 

Example 1:

Input: n = 4, index = 2,  maxSum = 6
Output: 2
Explanation: nums = [1,2,2,1] is one array that satisfies all the conditions.
There are no arrays that satisfy all the conditions and have nums[2] == 3, so 2 is the maximum nums[2].
Example 2:

Input: n = 6, index = 1,  maxSum = 10
Output: 3
 

Constraints:

1 <= n <= maxSum <= 109
0 <= index < n

*/

// Greedily guess the value at index and binary search 
class Solution {
public:
    int maxValue(int n, int index, int maxSum) {
        int l = 1, r = maxSum, res; 
        while( l <= r )
        {
            int mid = l+(r-l)/2;
            long left_sum = 0, right_sum = 0, r_amt = n-index-1, l_amt = index, sum = mid, m = mid-1;
            if ( l_amt <= m )
            {
                left_sum = m*(m+1)/2 - (m-l_amt)*(m-l_amt+1)/2;
            }
            else 
            {
                left_sum = m*(m+1)/2 + l_amt - m;
            }
            
            if ( r_amt <= m )
            {
                right_sum = m*(m+1)/2 - (m-r_amt) *(m-r_amt+1) / 2;
            }
            else
            {
                right_sum = m*(m+1)/2 + (r_amt-m);
            }
            
            sum += left_sum + right_sum;
            if ( sum <= maxSum )
            {
                res = mid;
                l = mid+1;
            }
            else 
            {
                r = mid-1;
            }
        }
        return res;
    }
};