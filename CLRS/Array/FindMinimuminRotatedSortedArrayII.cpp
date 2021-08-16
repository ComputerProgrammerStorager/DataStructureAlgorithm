/*
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

The array may contain duplicates.

Example 1:

Input: [1,3,5]
Output: 1
Example 2:

Input: [2,2,2,0,1]
Output: 0
Note:

This is a follow up problem to Find Minimum in Rotated Sorted Array.
Would allow duplicates affect the run-time complexity? How and why?
*/

// Divide and conquer:
// if duplicates exist, then should return either there is only one element or left is less than right
class Solution {
public:
    int findMin(vector<int>& nums) {
        return helper(nums,0,nums.size()-1);
    }
    int helper(vector<int> const& nums, int l, int r)
    {
        if ( l == r )
            return nums[l];
        if (nums[l] < nums[r])
            return nums[l];
        int m = (l+r)/2;
        return min(helper(nums,l,m),helper(nums,m+1,r));
    }
};

// The only different we need to deal with is the equal case in which we reduce the righ end by one
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        
        while(l < r)
        {
            int m = l + (r-l)/2;
            if ( nums[m] < nums[r] )
            {
                r = m;
            }
            else if ( nums[m] > nums[r] )
            {
                l = m+1;
            }
            else 
            {
                r = r-1;
            }
        }
        return nums[l];
    }
};