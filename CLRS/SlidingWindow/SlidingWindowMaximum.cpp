/*
You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]
Example 3:

Input: nums = [1,-1], k = 1
Output: [1,-1]
Example 4:

Input: nums = [9,11], k = 2
Output: [11]
Example 5:

Input: nums = [4,-2], k = 2
Output: [4]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
*/

// brute force solution, use linear search to find the max of each sliding window
// O(n*k)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        for ( int i = 0; i <= nums.size() - k; i++)
        {
            int cur_max = nums[i];
            for ( int j = i; j < i+k; j++ )
                cur_max = max(cur_max,nums[j]);
            res.push_back(cur_max);
        }
        
        return res;
    }
};

// we can improve on the previous solution by using a multiset to sort the windown elements 
// O(nlgk)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        multiset<int> window;
        for (int i = 0; i < nums.size(); i++)
        {
            window.insert(nums[i]);
            if ( window.size() > k )
            {
                window.erase(window.find(nums[i-k]));
            }
            if ( i >= k-1 )
                res.push_back(*window.rbegin());
        }
        
        return res;
    }
};

// similarly, we can use priority queue to deal with the elments in the sliding window
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        priority_queue<pair<int,int>> pq;   // (value, indx)
        for (int i = 0; i < nums.size(); i++)
        {
            while( !pq.empty() && pq.top().second <= i-k) 
                pq.pop();
            pq.push({nums[i],i});
            if ( i >= k-1 )
                res.push_back(pq.top().first);
        }
        
        return res;
    }
};

// we use a queue to maintain the maximum value of the window at the queue front and remove the front if the front is moved out of the window 
// Note: for convenience we store the index of in the queue
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> window;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++)
        {
            if ( !window.empty() && window.front() == i-k )
            {
                window.pop_front();
            }
            
            while ( !window.empty() && nums[window.back()] <= nums[i] )
                window.pop_back();
            window.push_back(i);
            if (i >= k-1)
                res.push_back(nums[window.front()]);
        }
        
        return res;
    }
};