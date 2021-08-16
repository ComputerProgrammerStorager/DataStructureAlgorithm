/*
The frequency of an element is the number of times it occurs in an array.

You are given an integer array nums and an integer k. In one operation, you can choose an index of nums and increment the element at that index by 1.

Return the maximum possible frequency of an element after performing at most k operations.

 

Example 1:

Input: nums = [1,2,4], k = 5
Output: 3
Explanation: Increment the first element three times and the second element two times to make nums = [4,4,4].
4 has a frequency of 3.
Example 2:

Input: nums = [1,4,8,13], k = 5
Output: 2
Explanation: There are multiple optimal solutions:
- Increment the first element three times to make nums = [4,4,8,13]. 4 has a frequency of 2.
- Increment the second element four times to make nums = [1,8,8,13]. 8 has a frequency of 2.
- Increment the third element five times to make nums = [1,4,13,13]. 13 has a frequency of 2.
Example 3:

Input: nums = [3,9,6], k = 2
Output: 1
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105
1 <= k <= 105
*/

// Idea: 
// First, we need to understand the most frequent element should be an existing number in the array 
// Second, since we are only allowed to increment by one, if we consider a particular number as the most frequent elment, 
// then we will change the numbers that are less than it.. which gives us the hint to sort the elments first. 
// In summary, we sort the numbers and then for each element, we expand it to the left until the accumulative difference exceeds k 
// However, the complexity of this approach will be O(n^2)

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int maxfreq = INT_MIN;
        int n = nums.size(); 
        for ( int i = 0; i < n; i++ )
        {
            int cnt = 0, j = i;
            for ( ; j >= 0; j-- )
            {
                if ( cnt + nums[i] - nums[j] <= k ) 
                {
                    cnt += nums[i]-nums[j];
                }
                else 
                    break;
            }
            maxfreq = max(maxfreq, i-j);
        }
        return maxfreq;
    }
};

// we can use sliding window/two pointers to improve the complexity of the algorithms 
// we maintain the number of operations requried to make the entire window to be the last element in the sliding window
// and if it exceeds k, we need to shrink the sliding window and update the max value if qualified 
public:
    int maxFrequency(vector<int>& nums, int k) {
        long maxfreq = LONG_MIN;
        long ops = 0;
        long s = 0, cnt = 1;
        sort(nums.begin(),nums.end());
        for ( int e = 1; e < nums.size(); e++ )
        {
            ops += cnt * (nums[e]-nums[e-1]);
            cnt++;
            while (ops > k )
            {
                cnt--;
                ops -= nums[e]-nums[s];
                s++;
            }
            
            maxfreq = max(maxfreq,cnt);
        }
        
        maxfreq = max(maxfreq,cnt);
        return maxfreq;
    }
};