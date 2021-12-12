/*
Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.

Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.

A subarray is defined as a contiguous block of elements in the array.

 

Example 1:

Input: nums = [3,1,4,2], p = 6
Output: 1
Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.
Example 2:

Input: nums = [6,3,5,2], p = 9
Output: 2
Explanation: We cannot remove a single element to get a sum divisible by 9. The best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.
Example 3:

Input: nums = [1,2,3], p = 3
Output: 0
Explanation: Here the sum is 6. which is already divisible by 3. Thus we do not need to remove anything.
Example 4:

Input: nums = [1,2,3], p = 7
Output: -1
Explanation: There is no way to remove a subarray in order to get a sum divisible by 7.
Example 5:

Input: nums = [1000000000,1000000000,1000000000], p = 3
Output: 0
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= p <= 109
*/

// use prefix sum to help calculate subarray sum. 
// then we can check from empty to (n-1)-sized subarrays to see if the remaing sum after removal is divisible by p

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size(); 
        vector<int> prefix_sum(n+1,0);
        for ( int i = 1; i <= n; i++ )
            prefix_sum[i] = prefix_sum[i-1] + nums[i-1];
        int total_sum = accumulate(nums.begin(),nums.end(),0);
        int rmlen = 0;
        bool found = false;
        while( rmlen < n && !found )
        {
            for ( int i = 0; i+rmlen <= n; i++ )
            {
                int rmsum = prefix_sum[i+rmlen] - prefix_sum[i];
                if ( (total_sum - rmsum) % p == 0 )
                {
                    found = true;
                    break;
                }
            }
            if ( !found )
                rmlen++;
        }
        
        return found ? rmlen : -1;
    }
};


// If we know the remainder (denoted by k) of the total_sum relative to p, then the problem becomes:
// Find the lenght of the shortest subarray whose remainders relative to p equals to k.
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size(), k = 0, res = n;
        for ( auto n : nums )
            k = (k + n%p) % p;
        if ( k == 0 )
            return 0;
        unordered_map<int,int> m;       // sum%p ---> last index 
        m[0] = -1;
        int sum = 0;
        for ( int i = 0; i < n; i++ )
        {
            sum = ( sum + nums[i]%p) % p;
            int target = (sum - k + p ) % p;
            if ( m.count(target) ) 
            {
                res = min(res,i-m[target]);
            }
            m[sum] = i;
        }
        
        return res == n ? -1 : res;
    }
};