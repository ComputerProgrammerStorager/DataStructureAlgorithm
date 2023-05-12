/*
You are given an integer array nums and two integers indexDiff and valueDiff.

Find a pair of indices (i, j) such that:

i != j,
abs(i - j) <= indexDiff.
abs(nums[i] - nums[j]) <= valueDiff, and
Return true if such pair exists or false otherwise.

 

Example 1:

Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
Output: true
Explanation: We can choose (i, j) = (0, 3).
We satisfy the three conditions:
i != j --> 0 != 3
abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0
Example 2:

Input: nums = [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3
Output: false
Explanation: After trying all the possible pairs (i, j), we cannot satisfy the three conditions, so we return false.
 

Constraints:

2 <= nums.length <= 105
-109 <= nums[i] <= 109
1 <= indexDiff <= nums.length
0 <= valueDiff <= 109
*/

// sliding window 
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        int sz = nums.size();
        for ( int i = 0; i < sz; i++ )
        {
            for ( int d = 1; d <= indexDiff && i+d < sz; d++ )
            {
                if ( abs(nums[i] - nums[i+d]) <= valueDiff )
                    return true;
            }
        }

        return false;
    }
};

// we can maintain a sorted sliding window of preceding k nums. 
// then for each number before it's inserted to the window, we check if there exists an adjacent number that is within the distance 
// We use upper_bound to find the nearest greater number. If there exists such a number (not equal to end), then we check the distance 
// If the bigger num is not within distance, then we continue to check the nearest smaller or equal number, i.e., *(--it). 
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        multiset<long> w;
        for ( int i = 0; i < nums.size(); i++ )
        {
            auto it = w.upper_bound(nums[i]);
            if ( (it != w.end() && *it - nums[i] <= valueDiff) || (it != w.begin() && nums[i] - *(--it) <= valueDiff) )
                return true;
            if ( i >= indexDiff )
                w.erase(nums[i-indexDiff]);
            w.insert(nums[i]);
        }

        return false;
    }
};

// we can apply the idea of bucket sorting. Basically, we can put the number into buckets [0,t], [t+1,2t+1]....etc. 
// then check each and every number, if there is already a number in the same bucket, it means we have found two elements which are within the given distance. 
// Similarly, we check the left and right adjacent buckets. 
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        int n = nums.size(); 
        unordered_map<long,long> bucket;     // map bucket id to the value 
        if ( n == 0 || indexDiff <= 0 || valueDiff < 0 )
            return false;
        long bucket_width = (long) valueDiff + 1;
        int min_val = *min_element(begin(nums),end(nums));

        for ( int i = 0; i < n; i++ )
        {
            int buckid = getbuckid(nums[i],min_val,bucket_width);
            if ( bucket.count(buckid) )
                return true;
            if ( bucket.count(buckid-1) && nums[i] - bucket[buckid-1] <= valueDiff )
                return true;
            if ( bucket.count(buckid + 1) && bucket[buckid+1] - nums[i] <= valueDiff )
                return true;
            bucket[buckid] = nums[i];
            if ( i >= indexDiff )
                bucket.erase(getbuckid(nums[i-indexDiff],min_val,bucket_width));
        }

        return false;
    }

private: 
    int getbuckid(int val, int min_val, int width)
    {
        return (val - min_val) / width;
    }
};