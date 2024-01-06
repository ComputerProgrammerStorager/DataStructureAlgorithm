/*
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.

For examples, if arr = [2,3,4], the median is 3.
For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.
You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
Explanation: 
Window position                Median
---------------                -----
[1  3  -1] -3  5  3  6  7        1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7        3
 1  3  -1  -3 [5  3  6] 7        5
 1  3  -1  -3  5 [3  6  7]       6
Example 2:

Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
 

Constraints:

1 <= k <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
*/

// straightforward approach would be copy every k size window and sort to find the median according to the definition 
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res; 
        for ( int i = 0; i + k <= nums.size(); i++ ) {
            vector<int> tmp(nums.begin()+i,nums.begin()+i+k);
            sort(tmp.begin(),tmp.end());
            if ( k & 1 )
                res.push_back(double(tmp[k/2]));
            else 
                res.push_back((long(tmp[k/2-1]) + tmp[k/2])*1.0/2);
        }

        return res;
    }
};

// Use two sets to store the two halves as it provides the convenient to access both ends 
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        multiset<int> lo, hi;
        for ( int i = 0; i < nums.size(); i++ ) {
            if ( i >= k ) {
                if ( nums[i-k] <= *lo.rbegin() ) {
                    lo.erase(lo.find(nums[i-k]));
                } else {
                    hi.erase(hi.find(nums[i-k]));
                }
            }

            lo.insert(nums[i]);
            hi.insert(*lo.rbegin());
            lo.erase(prev(lo.end()));

            if ( lo.size() < hi.size() ) {
                lo.insert(*hi.begin());
                hi.erase(hi.begin());
            }

            if ( i >= k - 1 ) {
                double median = k & 1 ? *lo.rbegin() : ((double)(*lo.rbegin())+(double)(*hi.begin())) * 0.5;
                res.push_back(median);
            }
        }

        return res;
    }
};