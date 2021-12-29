/*
Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.

A subarray is a contiguous part of the array.

Example 1:

Input: nums = [1,0,1,0,1], goal = 2
Output: 4
Explanation: The 4 subarrays are bolded and underlined below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
Example 2:

Input: nums = [0,0,0,0,0], goal = 0
Output: 15
 

Constraints:

1 <= nums.length <= 3 * 104
nums[i] is either 0 or 1.
0 <= goal <= nums.length
*/

// use prefix sum, whenever the differentiated sum has appeared then, we found some qualified subarrays
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int n = nums.size(), sum = 0, ans = 0;
        unordered_map<int,int> m{{0,1}};
        for ( int i = 0; i < n; i++ )
        {
            sum += nums[i];
            ans += sum >= goal ? m[sum-goal] : 0;
            m[sum]++;
        }
        
        return ans;
    }
};


// translate calculating exactly k to atMostk 
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return atMostk(nums,goal) - atMostk(nums,goal-1);
    }
    
private:
    int atMostk(vector<int> const& nums, int k)
    {
        int n = nums.size(), l = 0, ans = 0, win = 0;
        for ( int r = 0; r < n; r++ )
        {
            win += nums[r];
            while( win > k && l <= r)
            {
                win -= nums[l++];
            }
            ans += r-l+1;
        }
        
        return ans;
    }
};

// Use three pointers to formulate a win
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int iLo = 0, iHi = 0, loSum = 0, hiSum = 0, n = nums.size(), ans = 0;
        for ( int i = 0; i < n; i++ )
        {
            loSum += nums[i];
            while( iLo < i && loSum > goal )
                loSum -= nums[iLo++];
            hiSum += nums[i]; 
            while( iHi < i && (hiSum > goal || hiSum == goal && nums[iHi] == 0) )
                hiSum -= nums[iHi++];
            
            if ( loSum == goal )
                ans += iHi - iLo + 1;
        }
        
        return ans;
    }
};