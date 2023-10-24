/*
Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
Example 3:

Input: nums = [], target = 0
Output: [-1,-1]
 

Constraints:

0 <= nums.length <= 105
-109 <= nums[i] <= 109
nums is a non-decreasing array.
-109 <= target <= 109

*/

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = findPos(nums,target,true), r = findPos(nums,target, false);
        if ( l == -1 || r == -1 )
            return {-1,-1};
        return {l,r};
    }
private:
    int findPos(const vector<int>& nums, int target, bool isFirst)
    {
        int n = nums.size(), l = 0, r = n-1;
        while( l <= r )
        {
            int m = l+(r-l)/2;
            if (nums[m] == target) 
            {
                if ( isFirst )
                {
                    if ( m == 0 || nums[m-1] != nums[m] )
                        return m;
                    else 
                        r = m-1;
                } else {
                    if ( m == n - 1 || nums[m+1] != nums[m] )
                        return m;
                    l = m+1;
                }
            } else if ( nums[m] > target )
            {
                r = m-1;
            } else {
                l = m+1;
            }
        }

        return -1;
    }    
};


// We can find the left or right insertion point 
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = findinsertpos(nums,target,true);
        if ( l == nums.size() || nums[l] != target )
            return {-1,-1};
        return {l,findinsertpos(nums,target,false)-1};
    }
private:   
    int findinsertpos(const vector<int>& nums, int target, bool left)
    {
        int l = 0, r = nums.size();
        while( l < r )
        {
            int m = l + (r-l)/2;
            if ( nums[m] > target || (left && nums[m] == target ) )
            {
                r = m;
            }
            else {
                l = m+1;
            }
        }

        return r;
    }
};


class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = findinsertpos(nums,target,true);
        if ( l == nums.size() || nums[l] != target )
        {
            return {-1,-1};
        }
        return {l,findinsertpos(nums,target,false)-1};
    }
private:
    int findinsertpos(const vector<int>& nums, int target, bool left)
    {
        int n = nums.size(), l = 0, r = n-1;
        while( l <= r )
        {
            int m = l+(r-l)/2;
            if ( nums[m] > target || (left && nums[m] == target) )
                r = m-1;
            else
                l = m+1;
        }
        return l;
    }
};

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = findpos(nums,target,true), r = findpos(nums,target, false);
        if ( l == -1 )
            return {-1,-1};
        return {l,r};
    }
private:
    int findpos(const vector<int>& nums, int target, bool left)
    {
        int l = 0, r = nums.size() - 1;
        while( l <= r )
        {
            int m = (r+l)/2;
            if ( nums[m] == target )
            {
                if ( left )
                {
                    if ( m == l || nums[m-1] != target )
                        return m;
                    r = m-1;
                }
                else {
                    if ( m == r || nums[m+1] != target )
                        return m;
                    l = m+1;
                }
            }
            else if ( nums[m] > target ) {
                r = m-1;
            }
            else {
                l = m+1;
            }
        }
        
        return -1;
    }
};