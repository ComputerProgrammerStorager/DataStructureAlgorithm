/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

The number of elements initialized in nums1 and nums2 are m and n respectively. You may assume that nums1 has a size equal to m + n such that it has enough space to hold additional elements from nums2.

 

Example 1:

Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Example 2:

Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
 

Constraints:

nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-109 <= nums1[i], nums2[i] <= 109
*/

// use extra space is a trivial solution 
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = 0, j = 0, idx = 0;
        vector<int> tmp(m+n);
        if ( n == 0 )
            return ;
        if ( m == 0 )
        {
            nums1.swap(nums2);
            return;
        }
        
        while ( i < m && j < n )
        {
            if ( nums1[i] <= nums2[j] )
            {
                tmp[idx++] = nums1[i++];
            }
            else 
            {
                tmp[idx++] = nums2[j++];
            }
        }
        
        while ( i < m )
        {
            tmp[idx++] = nums1[i++];
        }
        
        while (j < n )
        {
            tmp[idx++] = nums2[j++];
        }
        
        nums1.swap(tmp);
    }
};

// we can fill up the resulting answer from the end, requiring no additional space 
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, idx = m+n-1;
        if ( m == 0 )
        {
            nums1.swap(nums2);
            return;
        }
        if ( n == 0 )
        {
            return;
        }
        
        while ( i >= 0 &&  j >= 0 )
        {
            if ( nums1[i] >= nums2[j] )
            {
                nums1[idx--] = nums1[i--];
            }
            else 
            {
                nums1[idx--] = nums2[j--];
            }
        }
        
        while ( i >= 0 )
        {
            nums1[idx--] = nums1[i--];
        }
        
        while ( j >= 0 )
        {
            nums1[idx--] = nums2[j--];
        }
        
        return;
    }
};

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int idx = m+n-1;
        m--;
        n--;
        while( m >= 0 || n >= 0 )
        {
            int x = m >= 0 ? nums1[m] : INT_MIN;
            int y = n >= 0 ? nums2[n] : INT_MIN;
            if ( x > y ) 
            {
                nums1[idx] = x;
                m--;
            }
            else
            {
                nums1[idx] = y;
                n--;
            }
            idx--;
        }
    }
};


class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int idx = m+n-1, midx = m-1, nidx = n-1;
        while( midx >= 0 && nidx >= 0 )
            nums1[idx--] = nums1[midx] >= nums2[nidx] ? nums1[midx--] : nums2[nidx--];
        while ( nidx >= 0 )
            nums1[idx--] = nums2[nidx--];
    }
};