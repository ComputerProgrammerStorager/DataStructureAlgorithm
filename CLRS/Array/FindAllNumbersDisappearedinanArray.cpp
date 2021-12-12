/*
Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.

Example 1:

Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]
Example 2:

Input: nums = [1,1]
Output: [2]
 

Constraints:

n == nums.length
1 <= n <= 105
1 <= nums[i] <= n
 

Follow up: Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
*/

// use extra space to record which not has appeared, requiring two passes 
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size(); 
        vector<bool> exist(n+1,false);
        vector<int> res;
        for ( auto n : nums )
            exist[n] = true;
        for ( int i = 1; i <= n; i++ )
            if ( !exist[i] )
                res.push_back(i);
        return res;
    }
};


// We can repurpose the given array to remember which number has appeared or not
// We can add an n to the number to indicate it has appeared, but we need to round down the number when it's used as an index 
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> res;
        int n = nums.size();
        for ( auto num : nums )
            nums[(num-1)%n] += n;
        for ( int i = 1; i <= n; i++ )
            if ( nums[i-1] <= n )
                res.push_back(i);
        
        return res;
    }
};