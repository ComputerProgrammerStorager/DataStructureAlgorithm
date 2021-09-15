/*
You are given an integer array nums of length n where nums is a permutation of the numbers in the range [0, n - 1].

You should build a set s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ... } subjected to the following rule:

The first element in s[k] starts with the selection of the element nums[k] of index = k.
The next element in s[k] should be nums[nums[k]], and then nums[nums[nums[k]]], and so on.
We stop adding right before a duplicate element occurs in s[k].
Return the longest length of a set s[k].

 

Example 1:

Input: nums = [5,4,0,3,1,6,2]
Output: 4
Explanation: 
nums[0] = 5, nums[1] = 4, nums[2] = 0, nums[3] = 3, nums[4] = 1, nums[5] = 6, nums[6] = 2.
One of the longest sets s[k]:
s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}
Example 2:

Input: nums = [0,1,2]
Output: 1
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] < nums.length
All the values of nums are unique.
*/

// brute force: we check using each and every idx as the starting index to find the max length
// since the values in nums are [0,n-1].. so termination condition is that the next index equals to 
// the starting index 
// O(n^2) O(1)
class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int max_len = INT_MIN;
        for ( int i = 0; i < nums.size(); i++ )
        {
            int cnt = 0, start = nums[i];
            do {
                cnt++;
                start = nums[start];
            } while(start != nums[i]);
            max_len = max(max_len,cnt);
        }
        
        return max_len;
    }
};

// the above method will repeatedly check loops of numbers for each iteration 
// In fact, this is an excellent question that can be translated to a graph problem, which has several circles.
// The problem then comes down to find the biggest length of circles. Therefore, we can remember any the circles that 
// have been visited already. Because if we enter a circle from any of its node, it will find the same length and we can avoid this 
// redundantly checking, bringing down the complexity to O(n)
class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        vector<bool> visited(nums.size(),false);
        int max_len = 0;
        for ( int i = 0; i < nums.size(); i++ )
        {
            if ( !visited[i] )
            {
                int cnt = 0;
                int start_idx = nums[i];
                do {
                    cnt++;
                    visited[start_idx] = true;
                    start_idx = nums[start_idx];
                } while (start_idx != nums[i]);
                max_len = max(max_len,cnt);
            }
            
        }
        
        return max_len;
    }
};