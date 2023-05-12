/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

Example 1:

Input: nums = [3,2,3]
Output: [3]
Example 2:

Input: nums = [1]
Output: [1]
Example 3:

Input: nums = [1,2]
Output: [1,2]
 

Constraints:

1 <= nums.length <= 5 * 104
-109 <= nums[i] <= 109
 

Follow up: Could you solve the problem in linear time and in O(1) space?

*/

// hashmap and count 
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> res;
        unordered_map<int,int> m;
        for ( auto n : nums )
            m[n]++;
        for ( auto it : m )
            if ( it.second > (int)(nums.size()/3) )
                res.push_back(it.first);
        return res;
    }
};


// there are at most two elements which could appear more than n/3 times. 
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int cnt1 = 0, cnt2 = 0, candidate1 = INT_MIN, candidate2 = INT_MIN;
        vector<int> res;
        for ( auto n : nums)
        {
            if ( candidate1 != INT_MIN && candidate1 == n ) cnt1++;
            else if ( candidate2 != INT_MIN && candidate2 == n) cnt2++;
            else if ( cnt1 == 0 ) {
                candidate1 = n;
                cnt1++;
            }
            else if ( cnt2 == 0 )
            {
                candidate2 = n;
                cnt2++;
            }
            else {
                cnt1--;
                cnt2--;
            }
        }

        cnt1 = 0;
        cnt2 = 0;
        for ( auto n : nums )
        {
            if ( candidate1 != INT_MIN && candidate1 == n )
                cnt1++;
            if ( candidate2 != INT_MIN && candidate2 == n )
                cnt2++;
        }
        if ( cnt1 > nums.size() / 3 )
            res.push_back(candidate1);
        if ( cnt2 > nums.size() / 3 )
            res.push_back(candidate2);
        return res;
    }
};