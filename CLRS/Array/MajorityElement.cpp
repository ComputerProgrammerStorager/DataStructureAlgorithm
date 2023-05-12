/*
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 104
-109 <= nums[i] <= 109
 

Follow-up: Could you solve the problem in linear time and in O(1) space?
*/

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int,int> m;
        for ( auto n : nums )
            m[n]++;
        for ( auto c : m )
            if ( c.second > (int) nums.size() / 2 )
                return c.first;
        return -1;
    }
};

// sort and check
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size(), prev = INT_MAX, cnt = 0;
        sort(nums.begin(),nums.end());
        for ( int i = 0; i < n; i++ )
        {
            if ( nums[i] != prev )
            {
                if ( cnt > n/2 )
                    return prev;
                cnt = 1;
                prev = nums[i];
            }
            else
            {
                cnt++;
            }
        }

        return prev;
    }
};

// as it's guaranteed to have a unique answer 
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()/2];
    }
};