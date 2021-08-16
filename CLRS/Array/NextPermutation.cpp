/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).

The replacement must be in place and use only constant extra memory.

 

Example 1:

Input: nums = [1,2,3]
Output: [1,3,2]
Example 2:

Input: nums = [3,2,1]
Output: [1,2,3]
Example 3:

Input: nums = [1,1,5]
Output: [1,5,1]
Example 4:

Input: nums = [1]
Output: [1]
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 100
*/

// algorithm:
// 1. find the num[i] which breaks the non-ascending rule from the right side 
// 2. if it's not the first element then find the first element that is larger than it and swap them 
// 3. reverse the elements to the right of num[i]
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;
        
        // find the first i such that nums[i] < nums[i+1]
        while ( i >= 0 && nums[i] >= nums[i+1] )
            i--;
        
        // find the first nums[j] which is smallest but larger than nums[i]
        if ( i >= 0 )
        {
            int j = nums.size() - 1;
            while ( j >= 0 && nums[j] <= nums[i] )
                j--;
            swap(nums[i],nums[j]);
        }
        reverse(nums,i+1);
    }
    
    // reserse the range[start, end]
    void reverse(vector<int>& nums, int start)
    {
        int s = start, e = nums.size() - 1;
        while ( s < e )
        {
            swap(nums[s],nums[e]);
            s++;
            e--;
        }
    }
};