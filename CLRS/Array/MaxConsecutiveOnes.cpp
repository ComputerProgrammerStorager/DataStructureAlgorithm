/*
Given a binary array nums, return the maximum number of consecutive 1's in the array.

Example 1:

Input: nums = [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.
Example 2:

Input: nums = [1,0,1,1,0,1]
Output: 2
 

Constraints:

1 <= nums.length <= 105
nums[i] is either 0 or 1.

*/

// maintain a local count and global maximum count 
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int cur_ones = 0, max_ones = INT_MIN;
        for (auto num : nums )
        {
            if ( num )
            {
                cur_ones++;
                max_ones = max(max_ones,cur_ones);
            }
            else
                cur_ones = 0;
        }
        
        max_ones = max(max_ones,cur_ones);
        
        return max_ones;
    }
};