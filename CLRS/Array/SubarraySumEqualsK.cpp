/*
Given an array of integers nums and an integer k, return the total number of continuous subarrays whose sum equals to k.

Example 1:

Input: nums = [1,1,1], k = 2
Output: 2
Example 2:

Input: nums = [1,2,3], k = 3
Output: 2
 
Constraints:

1 <= nums.length <= 2 * 104
-1000 <= nums[i] <= 1000
-107 <= k <= 107
*/


// brute-force O(n^2)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> dp(n,vector<int>(n));
        int cnt = 0;
        for ( int i = 0; i < n; i++ )
        {
            dp[i][i] = nums[i];
            if ( dp[i][i] == k )
                cnt++;
        }
            
        for ( int len = 2; len <= n; len++ )
        {
            for ( int l = 0; l <= n-len; l++ )
            {
                int r = l+len-1;
                dp[l][r] = dp[l][r-1] + nums[r];
                if ( dp[l][r] == k )
                {
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

// using accumulative sum, still O(n^2)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size(), cnt = 0;
        vector<int> accum_sum(n+1,0);     // sum[i]: sum(0..i-1);
        for ( int i = 1; i <= n; i++ )
        {
            accum_sum[i] += accum_sum[i-1]+nums[i-1];
        }
        for ( int i = 0; i < n; i++ )
            for ( int j = i; j < n; j++ )
            {
                if ( accum_sum[j+1] - accum_sum[i] == k )
                    cnt++;
            }
        
        return cnt;
    }
};

// Still brute force, but using constant space
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int cnt = 0, n = nums.size();
        for ( int i = 0; i < n; i++ )
        {
            int sum = 0;
            for ( int j = i; j < n; j++ )
            {
                sum += nums[j];
                if ( sum == k )
                    cnt++;
            }
        }
        return cnt;
    }
};

// this solution leverages the accumulative sum and if there exists a difference of k between two accumulative sums 
// then the interval is the satifying subarray 
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> sum_cnt{{0,1}};
        int sum = 0, cnt = 0;
        for ( auto n : nums )
        {
            sum += n;
            if ( sum_cnt.count(sum-k) )
                cnt += sum_cnt[sum-k];
            sum_cnt[sum]++;    
        }
        
        return cnt;
    }
};