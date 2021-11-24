/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

 

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
Example 3:

Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000
Example 4:

Input: nums1 = [], nums2 = [1]
Output: 1.00000
Example 5:

Input: nums1 = [2], nums2 = []
Output: 2.00000
 

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
*/

// Idea: 
// To find the nth (rank) of the combined nums, we could add n/2 to each of the two sorted arrays
// then we can decide which n/2 could be discarded by comparing the values at the n/2 position.
// After reducing the search range to a half, we are repeat this process. 

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size(), left = (m+n+1)/2, right = (m+n+2)/2;
        
        return ((double)findkth(nums1,0,nums2,0,left)+findkth(nums1,0,nums2,0,right)) / 2.0;
    }
    int findkth(vector<int> const& nums1, int start1, vector<int> const&nums2, int start2, int rank)
    {
        if ( start1 >= nums1.size() )
            return nums2[start2+rank-1];
        if ( start2 >= nums2.size() )
            return nums1[start1+rank-1];
        if ( rank == 1 )
            return min(nums1[start1],nums2[start2]);
        int midleft = start1+rank/2-1 < nums1.size() ? nums1[start1+rank/2-1] : INT_MAX;
        int midright = start2+rank/2-1 < nums2.size() ? nums2[start2+rank/2-1] : INT_MAX;
        if ( midleft < midright )
            return findkth(nums1,start1+rank/2,nums2,start2,rank - rank/2);
        else
            return findkth(nums1,start1,nums2,start2+rank/2,rank - rank/2);
    }
};