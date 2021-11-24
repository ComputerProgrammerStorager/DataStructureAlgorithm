/*
Given an array, rotate the array to the right by k steps, where k is non-negative.

 

Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
 

Constraints:

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
0 <= k <= 105
 

Follow up:

Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?
*/

// We know pos x will be in pos (x+k) % n after the shifting, so we can put each and every element in its final position 
// in a temporay array. 
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        vector<int> tmp(n);
        for ( int i = 0; i < n; i++ )
        {
            tmp[(i+k) % n] = nums[i];
        }
        
        nums = tmp;
    }
};

// we can do three reverse operations 
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums.begin(),nums.end());
        reverse(nums.begin(),nums.begin()+k);
        reverse(nums.begin()+k,nums.end());
    }
};

// This relies on group theory. 
// We can start from 0 and replace each of the following number that is k step apart 
// the group theory tells us it will in the end reach the originally starting position, not necessarily 
// visiting all elements. If not, then we check the next start position. 
// In the special case, where n % k == 0, it will partition the numbers into n/k equal groups.
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size(); 
        k %= n;
        int rotated = 0;
        for ( int s = 0; rotated < n; s++ )
        {
            int prev = nums[s];
            int cur = s;
            do {
                int next = (cur+k) % n;
                int tmp = nums[next];
                nums[next] = prev;
                prev = tmp;
                rotated++;
                cur = next;
            } while(cur != s );
        }
    }
};