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
 

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
*/

// Simulating merge sorting: 
// if (m+n) is odd, then the (m+n)/2 th number is the median 
// if (m+n) is even, then the (m+n)/2-1, and (m+n)/2 are the two middles, and their average is the median 
class Solution {
private:
    int p1 = 0, p2 = 0;
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = int(nums1.size()), n = int(nums2.size());
        if ( (m+n) % 2 == 1 )
        {
            for ( int i = 0; i < (m+n)/2; i++ )
               popmin(nums1,nums2);
            return popmin(nums1,nums2);
        }
        else {
            for ( int i = 0; i < (m+n)/2 - 1; i++ )
               int _ = popmin(nums1,nums2);
            return (double)(popmin(nums1,nums2) + popmin(nums1,nums2))/2;
        }
            
        return -1;
    }
        int popmin(vector<int>& nums1, vector<int>& nums2) {
        if (p1 < nums1.size() && p2 < nums2.size()) {
            return nums1[p1] < nums2[p2] ? nums1[p1++] : nums2[p2++];
        } else if (p1 < nums1.size()) {
            return nums1[p1++];
        } else if (p2 < nums2.size()) {
            return nums2[p2++];
        } 
        return -1;
    }
};

// Similar to the binary search on the rank. 
// if midleft < midright, then we can saftely discard the half starting from start1 
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size(), r1 = (m+n+1)/2, r2 = (m+n+2)/2;
        return (double)(findkth(nums1,nums2,0,0,r1) + findkth(nums1,nums2,0,0,r2)) / 2.0;
    }
private:
    int findkth(vector<int>& nums1, vector<int>& nums2, int start1, int start2, int rank)
    {
        if ( start1 >= nums1.size() )
            return nums2[start2+rank-1];
        if ( start2 >= nums2.size() )
            return nums1[start1+rank-1];
        if ( rank == 1 )
            return min(nums1[start1],nums2[start2]);
        int midleft = start1+rank/2-1 < nums1.size() ? nums1[start1+rank/2-1] : INT_MAX;
        int midright = start2 + rank/2-1 < nums2.size() ? nums2[start2+rank/2-1] : INT_MAX;
        if ( midleft < midright )
            return findkth(nums1,nums2,start1+rank/2,start2,rank-rank/2);
        else 
            return findkth(nums1,nums2,start1,start2+rank/2,rank-rank/2);
    }
};