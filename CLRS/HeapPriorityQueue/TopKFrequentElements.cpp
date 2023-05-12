/*
Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.
 
Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
*/

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int,int> m; // num <---> frequency 
        auto cmp = [&m](int n1, int n2) {return m[n1] > m[n2];};
        priority_queue<int,vector<int>, decltype(cmp)> pq(cmp);
        vector<int> res;
        for (auto n : nums)
            m[n]++;
        for (auto c : m )
        {
            pq.push(c.first);
            if ( pq.size() > k )
                pq.pop();
        }

        while ( pq.size() ) 
        {
            res.push_back(pq.top());
            pq.pop();
        }
        return res;
    }
};


/* Use quickselect */
class Solution {
private:
    vector<int> unique;
    map<int,int> m;
public:
    int partition(int l, int r, int pivot_idx)
    {
        int pivot_frequency = m[unique[pivot_idx]];
        swap(unique[pivot_idx],unique[r]);
        int store_idx = l;
        for ( int i = l; i <= r; i++ )
        {
            if ( m[unique[i]] < pivot_frequency )
            {
                swap(unique[store_idx],unique[i]);
                store_idx++;
            }
        }

        swap(unique[store_idx],unique[r]);
        return store_idx;
    }

    void quickselect(int l, int r, int k_smallest)
    {
        if ( l == r )
            return;
        int pivot_idx = l + rand()%(r-l+1);

        pivot_idx = partition(l,r,pivot_idx);
        if ( k_smallest == pivot_idx )
        {
            return;
        }
        else if ( k_smallest < pivot_idx )
        {
            quickselect( l, pivot_idx-1, k_smallest);
        } else {
            quickselect( pivot_idx, r, k_smallest );
        }
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        for ( auto n : nums )
        {
            m[n]++;
        }

        int n = m.size();
        for ( auto c : m )
            unique.push_back(c.first);

        quickselect(0,n-1,n-k);
        vector<int> top_k_frequent(k);
        copy(unique.begin()+n-k,unique.end(),top_k_frequent.begin());
        return top_k_frequent;
    }
};

/* Use python Counter object */
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        if k == len(nums):
            return nums
        cnt = Counter(nums)
        ans = cnt.most_common(k)
        res = []
        for k, v in ans:
            res.append(k)

        return res