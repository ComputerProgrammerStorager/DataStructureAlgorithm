/*
We define a harmonious array as an array where the difference between its maximum value and its minimum value is exactly 1.

Given an integer array nums, return the length of its longest harmonious subsequence among all its possible subsequences.

A subsequence of array is a sequence that can be derived from the array by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: nums = [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
Example 2:

Input: nums = [1,2,3,4]
Output: 2
Example 3:

Input: nums = [1,1,1,1]
Output: 0
 

Constraints:

1 <= nums.length <= 2 * 104
-109 <= nums[i] <= 109


*/

// since it needs to find ony the length of the largest harmonious subsequence, the positions of the elements 
// do not matter. Therefore, we can sort them first and then use two-pointers to find the len of qualifiying subsequences
// When the right expanding element is one larger than the left, it means it should be included in the current subsequence 
// and the maxlen should be updated. If the diff is zero, it means all the elements between [left, right] are the same, we
// we don't update the maxlen yet (because it could be possible the whole elements are the same), but just move to check the 
// next element.If the diff is the larger two, then we need to exclude the left element 

// Time: O(nlgn), O(lgn), sorting ..
class Solution {
public:
    int findLHS(vector<int>& nums) {
        int maxlen = 0, left = 0, right = 1;
        sort(nums.begin(),nums.end());
        while( right < nums.size() )
        {
            int diff = nums[right] - nums[left];
            if ( diff == 1 )
            {
                maxlen = max(maxlen,right-left+1);
            }
            if ( diff <= 1 )
            {
                right++;
            }
            else 
                left++;
        }
        
        return maxlen;
    }
};

// Because the qualifiying subsequence should contain two and only two nums, so we can put the numbs in map and check consecutive two nums 
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int,int> m;
        int res = 0;
        for ( auto n : nums )
        {
            m[n]++;
        }
        
        for ( auto it : m )
        {
            if ( m.count(it.first+1))
                res = max(res,it.second + m[it.first+1]);
        }
        
        return res;
    }
};


// we can add the check during adding map 
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int,int> m;
        int res = 0;
        for ( auto n : nums )
        {
            m[n]++;
            if ( m.count(n+1) )
                res = max(res,m[n] + m[n+1]);
            if ( m.count(n-1))
                res = max(res,m[n]+m[n-1]);
        }
        
        return res;
    }
};