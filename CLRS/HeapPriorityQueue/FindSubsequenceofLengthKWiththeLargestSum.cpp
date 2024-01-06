/*
You are given an integer array nums and an integer k. You want to find a subsequence of nums of length k that has the largest sum.

Return any such subsequence as an integer array of length k.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: nums = [2,1,3,3], k = 2
Output: [3,3]
Explanation:
The subsequence has the largest sum of 3 + 3 = 6.
Example 2:

Input: nums = [-1,-2,3,4], k = 3
Output: [-1,3,4]
Explanation: 
The subsequence has the largest sum of -1 + 3 + 4 = 6.
Example 3:

Input: nums = [3,4,3,3], k = 2
Output: [3,4]
Explanation:
The subsequence has the largest sum of 3 + 4 = 7. 
Another possible subsequence is [4, 3].
 

Constraints:

1 <= nums.length <= 1000
-105 <= nums[i] <= 105
1 <= k <= nums.length
*/

// This is equal to finding the k Largest number 
// Sorting 
class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<pair<int,int>> arr;
        vector<int> idx, res;
        for ( int i = 0; i < nums.size(); i++ )
        {
            arr.push_back({nums[i],i});
        }
        sort(arr.begin(),arr.end());
        for (int i = arr.size() - 1; i >= (int)arr.size()-k; i-- )
        {
            idx.push_back(arr[i].second);
        }
        sort(idx.begin(),idx.end());
        for (int i = 0; i < idx.size(); i++ )
        {
            res.push_back(nums[idx[i]]);
        }

        return res;
    }
};

// Priority queue 

class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        auto cmp = [](pair<int,int> a, pair<int,int> b) {
            return a.first > b.first;
        };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
        for ( int i = 0; i < nums.size(); i++ )
        {
            pq.push({nums[i],i});
            if ( pq.size() > k )
            {
                pq.pop();
            }
        }

        vector<int> idx, res;
        while(!pq.empty())
        {
            idx.push_back(pq.top().second);
            pq.pop();
        }
        sort(idx.begin(),idx.end());
        for ( int i = 0; i < idx.size(); i++ )
        {
            res.push_back(nums[idx[i]]);
        }

        return res;
    }
};