/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Output: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
 

Constraints:

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.
 

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
*/

// O(n^2) 
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> res;
        for ( int i = 0; i < nums.size(); i++ )
            for ( int j = i+1; j < nums.size(); j++ )
                if ( nums[i] + nums[j] == target )
                {
                    res.push_back(i);
                    res.push_back(j);
                    break;
                }
        return res;
    }
};

// one pass O(n)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> m;
        vector<int> res;
        for ( int i = 0; i < nums.size(); i++ )
        {
            if ( m.count(target-nums[i]) )
            {
                res.push_back(m[target-nums[i]]);
                res.push_back(i);
                break;
            }
            m[nums[i]] = i;
        }
        return res;
    }
};