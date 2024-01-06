/*
You are given an array nums of positive integers and a positive integer k.

A subset of nums is beautiful if it does not contain two integers with an absolute difference equal to k.

Return the number of non-empty beautiful subsets of the array nums.

A subset of nums is an array that can be obtained by deleting some (possibly none) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.

 

Example 1:

Input: nums = [2,4,6], k = 2
Output: 4
Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2, 6].
It can be proved that there are only 4 beautiful subsets in the array [2,4,6].
Example 2:

Input: nums = [1], k = 1
Output: 1
Explanation: The beautiful subset of the array nums is [1].
It can be proved that there is only 1 beautiful subset in the array [1].
 

Constraints:

1 <= nums.length <= 20
1 <= nums[i], k <= 1000
*/

// consider each state corresponding to an element 
class Solution {
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        return dfs(nums,0,0,k) - 1;
    }

    int dfs(vector<int>& nums, int cur, int state, int k) {
        bool isCurValid = true;
        if ( cur == nums.size() )
            return 1;
        for ( int i = 0; i < cur; i++ ) {
            if ( (state & (1<<i)) && abs(nums[i]-nums[cur]) == k ) 
            {
                isCurValid = false;
                break;
            }
        }

        int take_cur = dfs(nums, cur+1, state | (1<<cur), k);
        int not_take_cur = dfs(nums, cur+1, state, k);
        if ( isCurValid ) 
            return take_cur + not_take_cur;
        else 
            return not_take_cur;
    }
};

// we can divide the numbers based on mod k 
// and solve the subproblem independently 
class Solution {
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        int res = 1; 
        unordered_map<int,vector<int>> m;
        for ( auto n : nums ) 
            m[n%k].push_back(n);
        for ( auto it : m ) 
            res *= getcnt(it.second,k);
        return res - 1;
    }

    int getcnt(vector<int>& nums, int k) {
        unordered_map<int,int> m;
        vector<int> unique;
        for ( auto n : nums ) {
            m[n]++;
        }

        for ( auto it : m )
            unique.push_back(it.first);
        sort(unique.begin(),unique.end());
        int take = 0, not_take = 1;
        for ( int i = 0; i < unique.size(); i++ ) {
            int cnt = pow(2,m[unique[i]])-1;
            int take_tmp = take, not_take_tmp = not_take;
            if ( i != 0 && unique[i] - unique[i-1] == k ) {
                take = not_take_tmp * cnt;
            } else {
                take = (not_take_tmp + take_tmp) * cnt;
            }

            not_take = take_tmp + not_take_tmp;
        }

        return not_take+take;
    }
};

// nums, k, 
