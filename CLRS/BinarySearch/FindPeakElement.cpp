/*
A peak element is an element that is strictly greater than its neighbors.

Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.

You must write an algorithm that runs in O(log n) time.

 

Example 1:

Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.
Example 2:

Input: nums = [1,2,1,3,5,6,4]
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.
 

Constraints:

1 <= nums.length <= 1000
-231 <= nums[i] <= 231 - 1
nums[i] != nums[i + 1] for all valid i.
*/

// Linear scan: leveraging the fact that num[i] != num[i+1], we find a peak whenever num[i] > nums[i+1] 
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        for ( int i = 0; i < nums.size()-1; i++ )
        {
            if ( nums[i] > nums[i+1] )
                return i;
        }

        return nums.size() - 1;
    }
};

// Binary search: whenever we know the relationship between two consecutive nums, we can decides which half to go to find a local peak 
// nums[i] > nums[i+1], indicates there is peak on the left side including m itself, as we are seeing a decline at m
// nums[i] < nums[i+1], indicates m is still on the rising slope, so there must exist a peak on the right side
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while( l < r )
        {
            int m = (l+r)/2;
            if ( nums[m] > nums[m+1] )
                r = m;
            else 
                l = m+1;
        }
        
        return l;
    }
};