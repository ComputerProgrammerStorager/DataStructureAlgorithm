/*
You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 

Constraints:

1 <= nums.length <= 104
0 <= nums[i] <= 105

*/

// At each step, we have several choices to move to next step, dynamical programming 
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<bool> reachable(n,false);
        reachable[0] = true;
        for ( int pos = 0; pos < n; pos++ )
        {
            if ( reachable[pos] )
            {
                for ( int step = 0; step <= nums[pos]; step++ )
                    if ( pos + step < n )
                        reachable[pos+step] = true;
            }
        }
        
        return reachable[n-1];
    }
};

// we can also apply gready algorithm, the idea is to calculate the max idx that can be reaches at each step 
// after we know the max idx that can be reached, to calculate the next max, we need to check the possible starting point 
// which could be any point bfore the current max index. 
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int max_reachable = 0;
        for ( int i = 0; i <= max_reachable; i++ )
        {
            max_reachable = max(max_reachable, i+nums[i]);
            if ( max_reachable >= n-1 )
                return true;
        }
        
        return false;
    }
};

// In fact, we only need to check the expanded interval becuase those previous indexes have already been checked 
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int max_reachable = 0;
        int last_max = max_reachable;
        for ( int i = last_max; i <= max_reachable; i++ )
        {
            last_max = max_reachable;
            max_reachable = max(max_reachable, i+nums[i]);
            if ( max_reachable >= n-1 )
                return true;
        }
        
        return false;
    }
};


// Same logical, but we can walk backwards. 
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size(); 
        int lastpos = n-1;
        for ( int i = n-1; i >= 0; i-- )
        {
            if ( i+nums[i] >= lastpos )
                lastpos = i;
        }
        
        return lastpos == 0;
    }
};