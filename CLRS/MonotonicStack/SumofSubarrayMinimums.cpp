/*
Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.

 

Example 1:

Input: arr = [3,1,2,4]
Output: 17
Explanation: 
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
Sum is 17.
Example 2:

Input: arr = [11,81,94,43,3]
Output: 444
 

Constraints:

1 <= arr.length <= 3 * 104
1 <= arr[i] <= 3 * 104
*/

// for each element, if we know how many subarrarys it is part of as the minimum, then we can know its total contribution to the mini sum 
// Basically, we need to find the where is the smaller element than it both before and after it 
// We could use a monotonic increasing stack to help find the before and after smaller ones 
// When we see a following number that is smaller than a number being considered, then it means we know its right side. and the left side is the number below it in the stack. 
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size(), mod = 1000000007;
        long sum = 0;
        stack<int> s;
        for ( int i = 0; i <= n; i++ )
        {
            while( !s.empty() && (i == n || arr[s.top()] >= arr[i]) )
            {
                int m = s.top();
                s.pop();
                int l = s.empty() ? -1 : s.top();
                long cnt = (m-l) * (i-m) % mod;
                long cur_sum = (cnt * arr[m]) % mod;
                sum += cur_sum;
                sum %= mod;
            }
            s.push(i);
        }

        return sum;
    }
};
