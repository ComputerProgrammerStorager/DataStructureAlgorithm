/*
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:

[4,5,6,7,0,1,2] if it was rotated 4 times.
[0,1,2,4,5,6,7] if it was rotated 7 times.
Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums of unique elements, return the minimum element of this array.

You must write an algorithm that runs in O(log n) time.

 

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

// Edge cases : n == 1 or nums[n-1] > nums[0] (no rotation)
// Inflection point: nums[m] > nums[m+1], nums[m+1] is the minimum, nums[m] < nums[m-1], nums[m] is the minimum 
// nums[m] > nums[0] go right, nums[m] < nums[0] go left
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size(), l = 0, r = n -1;
        if ( n == 1 )
            return nums[0];
        if ( nums[n-1] > nums[0] )
            return nums[0];
        while ( l <= r )
        {
            int m = l + (r-l)/2;
            if ( nums[m] > nums[m+1] )
                return nums[m+1];
            if ( nums[m] < nums[m-1] )
                return nums[m];
            if ( nums[m] > nums[0] )
                l = m+1;
            else 
                r = m-1;
        }

        return -1;
    }
};


class Solution {
public:
    int findMin(vector<int>& nums) {
        int  l = 0, r = nums.size() - 1;
        while( l < r )
        {
            int m = (l+r) / 2;
            if ( nums[m] < nums[r] )
                r = m;
            else 
                l = m+1;
        }

        return nums[l];
    }
};