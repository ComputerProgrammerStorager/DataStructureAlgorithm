/*
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

 

Example 1:

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
Example 2:

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
 

Constraints:

0 <= nums.length <= 105
-109 <= nums[i] <= 109
*/

// use idea similar to bucket sorting with bucket size being 1, the check the longest sequence
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size(); 
        if ( n == 0 ) 
            return 0;
        int mn = *min_element(begin(nums),end(nums)), mx = *max_element(begin(nums),end(nums));
        vector<int> seen(mx-mn+1,0);
        for ( auto num : nums )
            seen[num-mn]++;
        int i = 0, res = 0;
        while( i < seen.size() )
        {
            while( seen[i] == 0 )
                i++;
            int j = i; 
            while ( j < seen.size() && seen[j] > 0 )
            {
                j++;
            }
            res = max(res,j-i);
            i = j;
        }

        return res;
    }
};

// we can sort the array and look for consecutive sequence
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size(); 
        if ( n == 0 )
            return 0;
        sort(nums.begin(),nums.end());
        int cur_len = 1, max_len = cur_len;
        for ( int i = 1; i < n; i++ )
        {
            if ( nums[i] != nums[i-1] )
            {
                if ( nums[i] == nums[i-1] + 1)
                {
                    cur_len++;
                    max_len = max(cur_len,max_len);
                }
                else 
                {
                    cur_len = 1;
                }
            }
        }

        return max(cur_len,max_len);
    }
};

// Alternatively, we can think about the way we construct a consecutive sequence 
// For the each number, we can consider it is the start of a potential sequence 
// Then we look forward to see if the next number is in the given nums, if not, we've found a sequence and update the result 
// Note if a previous number has been checked, then we can skip the case where it is the start, as it could not be the start and had already been checked 
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size(); 
        if ( n == 0 )
            return 0;
        unordered_set<int> s(nums.begin(),nums.end());
        int res = 0, cur_len = 0;
        for ( auto& n : nums )
        {
            if ( s.count(n-1) )
                continue;
            int cur_num = n, cur_len = 1;
            while(s.count(cur_num+1))
            {
                cur_len++;
                cur_num++;
            }

            res = max(res,cur_len);
        }

        return res;
    }
};