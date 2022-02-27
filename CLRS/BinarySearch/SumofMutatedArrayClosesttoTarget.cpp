/*
Given an integer array arr and a target value target, return the integer value such that when we change all the integers larger than value in the given array to be equal to value, the sum of the array gets as close as possible (in absolute difference) to target.

In case of a tie, return the minimum such integer.

Notice that the answer is not neccesarilly a number from arr.

 

Example 1:

Input: arr = [4,9,3], target = 10
Output: 3
Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.
Example 2:

Input: arr = [2,3,5], target = 10
Output: 5
Example 3:

Input: arr = [60864,25176,27249,21296,20204], target = 56803
Output: 11361
 

Constraints:

1 <= arr.length <= 104
1 <= arr[i], target <= 105

*/

// We binary search on the value ranges.. I had a difficulty in understanding why left should start from 0, given all values being positive 
// integers. After some thoughts, I figured out that when the array size it at least 2times of the target, then 0 would lead to the minimum difference 
// which is @target, while any other value would lead to a differnece larger than @target. 
// Negative values would definitely lead to larger difference than zero, given target being positive. 
// So the possible range is from [0,max_element].

class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        int sz = arr.size();
        if ( sz >= 2 * target )
            return 0;
        int left = 1, right = *max_element(arr.begin(),arr.end());
        int diff = INT_MAX, res;
        while ( left <= right )
        {
            int mid = left + (right-left)/2;
            int sum = SumTrim(arr,mid);
            int cur_diff = abs(sum-target);
            if ( cur_diff < diff )
            {
                res = mid;
                diff = cur_diff;
            }
            else if ( cur_diff == diff )
            {
                res = min(mid,res);
            }
            
            if ( sum == target )
            {
                return mid;
            }
            else if ( sum > target )
            {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return res;
    }
    
private:
    int SumTrim( vector<int> &arr, int threshold )
    {
        int sum = 0; 
        for ( auto val : arr )
        {
            if ( val > threshold )
                sum += threshold;
            else
                sum += val;
        }
        
        return sum;
    }
};

// This idea is based on the fact that we want the sum to be as cloest as possible 
// As we progressively consider the array, we compare the sum with the target. 
// if the current sum is smaller than target, then we want to try to increase the sum by increasing the threshhold. 
// whenever we first encounter current sum is less than or equal to the target, we find the result, because the difference between dynamic 
// current sum and dynamic target is mononitically increasing, leading to there being no need to continue searching. 
class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
    
        for (int i = 0; i < n; i++) {
            int cur_sum = arr[i] * (n-i);
            if ( cur_sum >= target )
                return (int)round((target-0.0001)/(n-i));
            target -= arr[i];
        }
        
        return arr[n-1];
    }
};