/*
Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Implement KthLargest class:

KthLargest(int k, int[] nums) Initializes the object with the integer k and the stream of integers nums.
int add(int val) Returns the element representing the kth largest element in the stream.
 

Example 1:

Input
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output
[null, 4, 5, 5, 8, 8]

Explanation
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8
 

Constraints:

1 <= k <= 104
0 <= nums.length <= 104
-104 <= nums[i] <= 104
-104 <= val <= 104
At most 104 calls will be made to add.
It is guaranteed that there will be at least k elements in the array when you search for the kth element.

*/

#include "../Common/common_api.h"

class KthLargest {
private:
    priority_queue<int,vector<int>, greater<int>> q;
    int k;
public:
    KthLargest(int k, vector<int>& nums) {
        q = priority_queue<int,vector<int>,greater<int>>(nums.begin(),nums.end());
        while ( q.size() > k )
        {
            q.pop();
        }
        this->k = k;
    }
    
    int add(int val) {
        if ( q.size() >= k && val <= q.top() )
            return q.top();
        q.push(val);
        if ( q.size() > k )
            q.pop();
        return q.top();
    }
};

/*
["KthLargest","add","add","add","add","add"]
[[1,[]],[-3],[-2],[-4],[0],[4]]
*/
int main()
{
    KthLargest *obj = new KthLargest(1,{});
}

// we can also use quick sorting to find the element, i.e., if the partition function returns the index we 
// want, then we are done 
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return quick_select(nums,0,n-1, n-k);
    }
    int partition(vector<int>& nums, int s, int e )
    {
        int pivot = nums[e];
        int store_idx = s - 1;
        for ( int i = s; i <= e; i++ )
        {
            if ( nums[i] < pivot )
            {
                swap(nums[++store_idx],nums[i]);
            }
        }
        swap(nums[++store_idx],nums[e]);
        return store_idx;
    }
    int quick_select(vector<int>& nums, int s, int e, int k_smallest)
    {
        int pivot_idx = partition(nums,s,e);
        if ( pivot_idx == k_smallest )
            return nums[pivot_idx];
        else if ( pivot_idx < k_smallest )
            return quick_select(nums,pivot_idx+1,e,k_smallest);
        else
            return quick_select(nums,s,pivot_idx-1,k_smallest);
    }
};