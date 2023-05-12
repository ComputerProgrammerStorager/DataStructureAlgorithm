/*
Given an array of n integers nums and an integer target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

 

Example 1:

Input: nums = [-2,0,1,3], target = 2
Output: 2
Explanation: Because there are two triplets which sums are less than 2:
[-2,0,1]
[-2,0,3]
Example 2:

Input: nums = [], target = 0
Output: 0
Example 3:

Input: nums = [0], target = 0
Output: 0
 

Constraints:

n == nums.length
0 <= n <= 3500
-100 <= nums[i] <= 100
-100 <= target <= 100
*/

// for each starting idx, we fix the second idx and find the third idx 
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size(), res = 0;
        sort(nums.begin(),nums.end());
        for ( int i = 0; i < n - 2; i++ )
        {
            res += twosmaller(nums,i+1,target-nums[i]);
        }

        return res;
    }
private:

    int twosmaller(vector<int> const& nums, int startidx, int target)
    {
        int res = 0;
        for ( int i = startidx; i < nums.size()-1; i++ )
        {
            res += binarysearch(nums,i,target-nums[i]) - i;
        }

        return res;
    }
    int binarysearch(vector<int> const& nums, int startidx, int target)
    {
        int l = startidx, r = nums.size() - 1;
        while ( l < r )
        {
            int m = (l+r+1)/2;
            if ( nums[m] < target )
            {
                l = m;
            }
            else 
            {
                r = m - 1;
            }
        }

        return l;
    }
};

// Optimized a bit, if we find the left and right end, then we know how many combinations are there in the interval whose sum is less than the target
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size(), res = 0;
        sort(nums.begin(),nums.end());
        for ( int i = 0; i < n-2; i++ )
            res += twosmaller(nums,i+1,target-nums[i]);
        return res;
    }

private:
    int twosmaller(vector<int> const& nums, int startidx, int target)
    {
        int l = startidx, r = nums.size() - 1, res = 0;
        while( l < r )
        {
            if ( nums[l] + nums[r] < target )
            {
                res += r - l;
                l++;
            }
            else 
            {
                r--;
            }
        }

        return res;
    }
};