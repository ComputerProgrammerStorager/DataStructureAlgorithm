/*
Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

 

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
 

Constraints:

1 <= k <= nums.length <= 104
-104 <= nums[i] <= 104
*/

// Naive approach 
// O(nlgn)
// O(1)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()-k];
    }
};

// use min priority queue to dynamically maintain the current k largest element 
// O(nlgk)
// O(k)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int,vector<int>,greater<int>> pq;
        for ( auto n : nums )
        {
            pq.push(n);
            if ( pq.size() > k )
                pq.pop();
        }
        
        return pq.top();
    }
};

// we can also use the divide-and-conquer similar to the quicksort algorithm 
// the key is the partition algorithm in which we place a chosen pivot in it's 
// final position in the array and return it's pos. If the position equal to (n-k) 
// then we have found the wanted value
class Solution {
    int res;
    int n;
    int k;
public:
    int findKthLargest(vector<int>& nums, int k) {
        n = nums.size();
        this->k = k;
        quickselect_kthlargest(nums,0,n-1);
        return res;
    }
    
    void quickselect_kthlargest(vector<int> &nums, int s, int e )
    {
        int pos = partition(nums,0,n-1);
        while ( pos != n - k)
        {
            if ( pos > n - k)
                pos = partition(nums,s,pos-1);
            else
                pos = partition(nums,pos+1,e);
        }
        
        res = nums[pos];
        return;
    }
    
    int partition(vector<int> &nums, int s, int e )
    {
        int p = s-1, pivot = nums[e];
        for ( int j = s; j < e; j++ )
        {
            if ( nums[j] <= pivot )
            {
                p++;
                swap(nums[p],nums[j]);
            }
        }
        
        swap(nums[p+1],nums[e]);
        return p+1;
    }
};

// Use set to maintain the largest k nums..
// Note: we need to use multiset and when erase it erases all occurrence of the given value 
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_multiset<int> maxs;
        for ( auto n : nums )
        {
            maxs.insert(n);
            if ( maxs.size() > k )
            {
                maxs.erase(maxs.find(*min_element(maxs.begin(),maxs.end())));
            }
        }
        
        return *min_element(maxs.begin(),maxs.end());
    }
};
