/*
Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

 

Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].
Example 2:

Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
 

Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums is sorted in non-decreasing order.
 

Follow up: Squaring each element and sorting the new array is very trivial, could you find an O(n) solution using a different approach?

*/

#include "../Common/common_api.h"

#if 0
// this is the trivial approach based on sorting 
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        
        for ( int i = 0; i < n; i++ )
            if ( nums[i] < 0 )
                nums[i] *= -1;
        
        sort(nums.begin(),nums.end());
        
        for ( int i = 0; i < n; i++ )
            nums[i] *= nums[i];
        
        return nums;
    }
};
#endif 

// We can also use two pointers to expand to two sides and pick the smaller one at a time 
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> res;
        int n = nums.size();
        int neg_idx = 0, pos_idx = 0; 
        while ( neg_idx < n && nums[neg_idx] < 0 )
            neg_idx++;
        pos_idx = neg_idx;
        while( pos_idx < n && nums[pos_idx] == 0 )
            pos_idx++;
        neg_idx -= 1;
        
        int zeros = pos_idx - neg_idx - 1;
        while( zeros-- )
            res.push_back(0);
        
        while ( neg_idx >= 0 && pos_idx < n )
        {
            if ( abs(nums[neg_idx]) <= nums[pos_idx] )
            {
                res.push_back(nums[neg_idx]*nums[neg_idx]);
                neg_idx--;
            }
            else 
            {
                res.push_back(nums[pos_idx]*nums[pos_idx]);
                pos_idx++;
            }
        }
        
        while ( neg_idx >= 0 )
        {
            res.push_back(nums[neg_idx]*nums[neg_idx]);
            neg_idx--;
        }
        while ( pos_idx < n )
        {
            res.push_back(nums[pos_idx]*nums[pos_idx]);
            pos_idx++;
        }
        
        return res;
    }
};

// Two pointers: it's essentially equal to merging two sorted array 
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size(), l = 0, r = n-1;
        vector<int> res(n,0);
        for ( int i = n-1; i >= 0; i-- )
        {
            int square = abs(nums[r]) > abs(nums[l]) ? nums[r--] : nums[l++];
            res[i] = square * square;
        }
        
        return res;
    }
};

int main()
{
    vector<int> data = {-4,-1,0,3,10};
    Solution s;
    s.sortedSquares(data);
}