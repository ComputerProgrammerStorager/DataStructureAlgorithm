/*
An integer array is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic sequences.
Given an integer array nums, return the number of arithmetic subarrays of nums.

A subarray is a contiguous subsequence of the array.

 

Example 1:

Input: nums = [1,2,3,4]
Output: 3
Explanation: We have 3 arithmetic slices in nums: [1, 2, 3], [2, 3, 4] and [1,2,3,4] itself.
Example 2:

Input: nums = [1]
Output: 0
 

Constraints:

1 <= nums.length <= 5000
-1000 <= nums[i] <= 1000
*/

// Choose ever possible two starting elements, and check the remaining if added to formulate the defined subarray
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size(), cnt = 0; 
        for ( int i = 0; i < n-2; i++ ) {
            int d = nums[i+1] - nums[i];
            for ( int j = i+2; j < n; j++ ) {
                if ( nums[j] - nums[j-1] != d ) 
                    break;
                else 
                    cnt++;
            }
        }
        return cnt;
    }
};

// consider A[i] is added to a subarray. 