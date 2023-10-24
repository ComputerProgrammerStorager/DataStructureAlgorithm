/*
Given an integer array nums and an integer k, return the kth largest element in the array.

Note that it is the kth largest element in the sorted order, not the kth distinct element.

Can you solve it without sorting?

 

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4
 

Constraints:

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104
*/

lass Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int,vector<int>, greater<>> pq;
        for ( auto n : nums )
        {
            pq.push(n);
            if ( pq.size() > k )
                pq.pop();
        }

        return pq.top();
    }
};

// quickselect 
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickselect(nums,k);
    }
private:
    int quickselect(vector<int>& nums, int k)
    {
        int pivot = nums[rand()%nums.size()];
        vector<int> left, mid, right;
        for ( auto n : nums )
        {
            if ( n > pivot )
                left.push_back(n);
            else if ( n == pivot )
                mid.push_back(n);
            else 
                right.push_back(n);
        }
        if ( k <= left.size() )
            return quickselect(left,k);
        if ( k > left.size() + mid.size() )
            return quickselect(right,k-left.size()-mid.size());
        return pivot;
    }
};


// standard quick select 
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        quickselect(nums,0,n-1,n-k);
        return nums[n-k];
    }
    int partition(vector<int>& nums, int l, int r, int pivot_idx)
    {
        int pivot_val = nums[pivot_idx];
        swap(nums[pivot_idx],nums[r]);
        int store_idx = l;
        for ( int i = l; i < r; i++ )
        {
            if ( nums[i] < pivot_val )
            {
                swap(nums[i],nums[store_idx++]);
            }
        }
        swap(nums[r],nums[store_idx]);
        return store_idx;
    }

    void quickselect(vector<int>& nums, int l, int r, int k_smallest)
    {
        if ( l == r )
            return;
        int pivot_idx = l + rand() % (r-l+1);
        pivot_idx = partition(nums,l,r,pivot_idx);
        if ( pivot_idx == k_smallest)
            return;
        else if ( k_smallest < pivot_idx )
            quickselect(nums,l,pivot_idx-1,k_smallest);
        else 
            quickselect(nums,pivot_idx+1,r,k_smallest);
    }
};