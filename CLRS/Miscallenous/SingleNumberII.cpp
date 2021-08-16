/*
Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.

Example 1:

Input: nums = [2,2,3,2]
Output: 3
Example 2:

Input: nums = [0,1,0,1,0,1,99]
Output: 99
 

Constraints:

1 <= nums.length <= 3 * 104
-231 <= nums[i] <= 231 - 1
Each element in nums appears exactly three times except for one element which appears once.
 

Follow up: Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/

// Naive method: remember each num's occurrence, requiring O(n) space
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int,int> m;
        for ( auto num : nums )
            m[num]++;
        for ( auto it = m.begin(); it != m.end(); it++ )
        {
            if ( it->second == 1 )
                return it->first;
        }
        return -1;
    }
};

// use math: (3 * unique_sum - total_sum) / 2 
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_set<int> s(nums.begin(),nums.end());
        long sum = accumulate(nums.begin(),nums.end(),(long)0);
        long multi_sum = accumulate(s.begin(),s.end(),(long)0);
        return (int)((3*multi_sum - sum) / 2);
    }
};

// calculate the number of bits set at each of the 32 positions
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for ( int bit = 0; bit < 32; bit++ )
        {
            int n = 0;
            for ( auto num : nums )
                if ( num & (1<<bit) ) 
                    n++;
            res |= (n%3 << bit);
        }
        return res;
    }
};


// The key to using XOR is to differentiate the one time and three times, as both cases would lead to a bit set
// basically, we need to have a state machine that does the transition: 00 --> 01 --> 10 --> 00
// seen_once: remembers the bit that appears once
// seen_twice: remember the bit that appears twice 
// when a number is first encountered, it would set the bit in seen_once
// when a number is second encountered, it needs to clear the bit in seen_once and set the bit in seen_twice
// When a number is third encountered, it needs to clear both seen_once and seen_twice
// seen_once = ~seen_twice & (seen_once & num): set the seen_once only if seen_twice is not set (to zero the third appearance)
// seen_twice = ~seen_once & (seen_twice & num): set the seen_twice only if seen_once is not set(or cleared) 
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int seen_once = 0, seen_twice = 0;
        for ( auto num : nums )
        {
            seen_once = ~seen_twice & (seen_once ^ num);
            seen_twice = ~seen_once & (seen_twice ^ num);
        }
        
        return seen_once;
    }
};