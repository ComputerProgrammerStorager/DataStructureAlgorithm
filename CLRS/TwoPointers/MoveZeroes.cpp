/*
Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.

 

Example 1:

Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]
Example 2:

Input: nums = [0]
Output: [0]
 

Constraints:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
 

Follow up: Could you minimize the total number of operations done?
*/

// Two pointers and swap 
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int zero_idx = 0, n = nums.size();
        while( zero_idx < n && nums[zero_idx] )
            zero_idx++;
        for ( int i = zero_idx; i < n; i++ )
        {
            if ( nums[i] == 0 )
                continue;
            swap(nums[zero_idx++], nums[i]);
        }
    }
};


// Two pointers and select non-zero to put front 
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int non_zero = 0, n = nums.size();
        for ( int i = 0; i < n; i++ )
        {
            if ( nums[i] )
            {
                nums[non_zero++] = nums[i];
            }
        }
        
        while ( non_zero < n )
            nums[non_zero++] = 0;
    }
};