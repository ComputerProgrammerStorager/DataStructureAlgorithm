/*
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:

[4,5,6,7,0,1,2] if it was rotated 4 times.
[0,1,2,4,5,6,7] if it was rotated 7 times.
Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums, return the minimum element of this array.

 

Example 1:

Input: nums = [3,4,5,1,2]
Output: 1
Explanation: The original array was [1,2,3,4,5] rotated 3 times.
Example 2:

Input: nums = [4,5,6,7,0,1,2]
Output: 0
Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.
Example 3:

Input: nums = [11,13,15,17]
Output: 11
Explanation: The original array was [11,13,15,17] and it was rotated 4 times. 
 

Constraints:

n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
All the integers of nums are unique.
nums is sorted and rotated between 1 and n times.
*/

// if we could not find an inflection point, then it's either ascending or descending order 
// O(n)
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int res, i;
        for ( i = 1; i < n; i++ )
        {
            if ( nums[i] < nums[i-1] )
            {
                res = nums[i];
                break;
            }
        }
        if ( i == n )
        {
            res = min(nums[0],nums[n-1]);
        }
        
        return res;
    }
};

// We can use binary search to reduce to O(lgn) complexity 
// if mid is larger than right end, then the inflexition point is on the right 
// else it's on the left side 
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while ( l < r )
        {
            int m = l + (r-l)/2;
            if ( nums[m] > nums[r] )
                l = m+1;
            else 
                r = m;
        }
        return nums[r];
    }
};

// Can also use divide and conquer and return the min of the two ends
class Solution {
public:
    int findMin(vector<int>& nums) {
        return helper(nums,0,nums.size()-1);
    }
    
    int helper( vector<int> const& nums, int l, int r)
    {
        if ( nums[l] <= nums[r] )
            return nums[l];
        else 
        {
            int m = l + (r-l)/2;
            return min(helper(nums,l,m),helper(nums,m+1,r));
        }
    }
};