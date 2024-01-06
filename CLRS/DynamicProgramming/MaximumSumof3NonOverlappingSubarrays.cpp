/*
Given an integer array nums and an integer k, find three non-overlapping subarrays of length k with maximum sum and return them.

Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.

 

Example 1:

Input: nums = [1,2,1,2,6,7,5,1], k = 2
Output: [0,3,5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
Example 2:

Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
Output: [0,2,4]
 

Constraints:

1 <= nums.length <= 2 * 104
1 <= nums[i] < 216
1 <= k <= floor(nums.length / 3)
*/

// First  we need to calculate the array of k-sized window sums. Index of the window sum corresponds to the window's start position in the original array 
// Then we need to consider each possible window as the middle (k <= m < win_sz-k), and then we also need the max windown on both left and right 
// To facilitate finding the left and right windown max, we can precompute the leftmax and rightmax 
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size(), win_sz = n-k+1, sum = 0, best;
        vector<int> wins(win_sz), ans(3,-1), leftmax(win_sz), rightmax(win_sz);
        for ( int i = 0; i < n; i++ ) {
            sum += nums[i];
            if ( i >= k ) 
                sum -= nums[i-k];
            if ( i >= k -1 ) 
                wins[i-k+1] = sum;
        }
        best = 0;
        for ( int i = 0; i < win_sz; i++ ) {
            if ( wins[i] > wins[best] ) 
                best = i;
            leftmax[i] = best;
        }
        best = win_sz - 1;
        for ( int i = win_sz - 1; i >= 0; i-- ) {
            if ( wins[i] >= wins[best] ) 
                best = i;
            rightmax[i] = best;
        }
        int maxSum;
        for (int m = k; m < win_sz-k; m++ ) {
            int l = leftmax[m-k], r = rightmax[m+k];
            if ( ans[0] == -1 || wins[l] + wins[m] + wins[r] > maxSum ) {
                ans[0] = l, ans[1] = m, ans[2] = r;
                maxSum = wins[l]+wins[m]+wins[r];
            }
        }

        return ans;
    }
};