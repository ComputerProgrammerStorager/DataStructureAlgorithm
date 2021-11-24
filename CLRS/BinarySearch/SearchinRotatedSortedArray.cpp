/*
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
Example 3:

Input: nums = [1], target = 0
Output: -1
 

Constraints:

1 <= nums.length <= 5000
-104 <= nums[i] <= 104
All values of nums are unique.
nums is an ascending array that is possibly rotated.
-104 <= target <= 104

*/

// we can first find the rotate position with 0 having no rotation 
// Then we translate the problem into searching in sorted subarrays 
// This approach requires two passes and handling a variety of edge cases 
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if ( n == 1 )
            return nums[0] == target ? 0 : -1;
        int rotate_idx = find_rotate_pos(nums,0,n-1);
        if ( nums[rotate_idx] == target )
            return rotate_idx;
        if ( rotate_idx == 0 )
            return binary_search(nums,0,n-1,target);
        if ( target < nums[0] )
            return binary_search(nums,rotate_idx,n-1,target);
        return binary_search(nums,0,rotate_idx,target);
    }
    
    int find_rotate_pos(vector<int> const &nums, int left, int right)
    {
        if ( nums[left] < nums[right] )
            return 0;
        while( left <= right )
        {
            int mid = left + (right-left)/2;
            if ( nums[mid] > nums[mid+1] )
                return mid + 1;
            if ( nums[mid] < nums[left] )
                right = mid-1;
            else
                left = mid+1;
        }
        return 0;
    }
    
    int binary_search(vector<int> const& nums, int l, int r, int target)
    {
        while( l <= r)
        {
            int mid = l + (r-l) / 2;
            if ( nums[mid] == target )
                return mid;
            if ( target > nums[mid] )
            {
                l = mid + 1;
            }
            else 
                r = mid - 1;
        }
        
        return -1;
    }
};

// we can do it in one-pass by slightly modifying the standard binary search process 
// we compare the mid and either of the end, and then for each possible we can always identify a sorted subarray 
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(), l = 0, r = n-1;
        while( l <= r )
        {
            int m = l + (r-l) / 2;
            if ( nums[m] == target )
                return m;
            if ( nums[m] >= nums[l] )
            {
                if ( target >= nums[l] && target < nums[m] )
                    r = m - 1;
                else
                    l = m+1;
            }
            else
            {
                if ( target > nums[m] && target <= nums[r] )
                    l = m + 1;
                else
                    r = m - 1;
            }
        }
        return -1;
    }
};