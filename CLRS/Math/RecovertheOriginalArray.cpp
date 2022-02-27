/*
Alice had a 0-indexed array arr consisting of n positive integers. She chose an arbitrary positive integer k and created two new 0-indexed integer arrays lower and higher in the following manner:

lower[i] = arr[i] - k, for every index i where 0 <= i < n
higher[i] = arr[i] + k, for every index i where 0 <= i < n
Unfortunately, Alice lost all three arrays. However, she remembers the integers that were present in the arrays lower and higher, but not the array each integer belonged to. Help Alice and recover the original array.

Given an array nums consisting of 2n integers, where exactly n of the integers were present in lower and the remaining in higher, return the original array arr. In case the answer is not unique, return any valid array.

Note: The test cases are generated such that there exists at least one valid array arr.

 

Example 1:

Input: nums = [2,10,6,4,8,12]
Output: [3,7,11]
Explanation:
If arr = [3,7,11] and k = 1, we get lower = [2,6,10] and higher = [4,8,12].
Combining lower and higher gives us [2,6,10,4,8,12], which is a permutation of nums.
Another valid possibility is that arr = [5,7,9] and k = 3. In that case, lower = [2,4,6] and higher = [8,10,12]. 
Example 2:

Input: nums = [1,1,3,3]
Output: [2,2]
Explanation:
If arr = [2,2] and k = 1, we get lower = [1,1] and higher = [3,3].
Combining lower and higher gives us [1,1,3,3], which is equal to nums.
Note that arr cannot be [1,3] because in that case, the only possible way to obtain [1,1,3,3] is with k = 0.
This is invalid since k must be positive.
Example 3:

Input: nums = [5,435]
Output: [220]
Explanation:
The only possible combination is arr = [220] and k = 215. Using them, we get lower = [5] and higher = [435].
 

Constraints:

2 * n == nums.length
1 <= n <= 1000
1 <= nums[i] <= 109
The test cases are generated such that there exists at least one valid array arr.

*/

// we know the smallest value (x-k) in the sorted array after must have it's corresponding a (x+k), which will give a 2*k difference 
// but we don't know which number if x+k.. then guess and try the k! 
class Solution {
public:
    vector<int> recoverArray(vector<int>& nums) {
        int n_2 = nums.size(); 
        unordered_set<int> can_2k;
        sort(nums.begin(),nums.end());
        for ( int i = 1; i <= n_2/2; i++ )
        {
            int diff = nums[i] - nums[0];
            if ( diff > 0 && diff % 2 == 0 && can_2k.count(diff) == 0 )
            {
                can_2k.insert(diff);
            }
        }
        for ( auto diff : can_2k )
        {
            int cnt = 0;
            check(nums,diff, cnt);
            if ( cnt == n_2/2 )
            {
                return check(nums,diff,cnt);
            }
        }
        return {};
    }
private:
    vector<int> check(vector<int> const& nums, int double_diff, int &cnt )
    {
        unordered_map<int,int> m;
        vector<int> res;
        for ( auto n : nums )
            m[n]++;
        for ( auto n : nums )
        {
            if ( m[n] > 0 && m[n+double_diff] > 0 )
            {
                m[n]--;
                m[n+double_diff]--;
                res.push_back(n+double_diff/2);
            }
        }
        cnt = res.size();
        return res;
    }
};