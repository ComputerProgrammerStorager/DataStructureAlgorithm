/*
Given an integer array nums, return the third distinct maximum number in this array. If the third maximum does not exist, return the maximum number.

 

Example 1:

Input: nums = [3,2,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2.
The third distinct maximum is 1.
Example 2:

Input: nums = [1,2]
Output: 2
Explanation:
The first distinct maximum is 2.
The second distinct maximum is 1.
The third distinct maximum does not exist, so the maximum (2) is returned instead.
Example 3:

Input: nums = [2,2,3,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2 (both 2's are counted together since they have the same value).
The third distinct maximum is 1.
 

Constraints:

1 <= nums.length <= 104
-231 <= nums[i] <= 231 - 1
 

Follow up: Can you find an O(n) solution?

*/

// cascading replace out smaller nums 
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        vector<int> arr(3,INT_MIN);
        int sz = 0;
        unordered_set<int> s(nums.begin(),nums.end());
        for ( auto n : s )
        {
            int tmp = n;
            if ( sz == 0 )
            {
                swap(arr[0],n);
                sz++;
            }
            else if ( sz == 1 )
            {
                if ( tmp > arr[0] )
                {
                    swap(tmp,arr[0]);
                }
                swap(tmp,arr[1]);
                sz++;
            }
            else if ( sz == 2 )
            {
                if ( tmp > arr[0] )
                {
                    swap(tmp,arr[0]);
                }
                if ( tmp > arr[1] )
                    swap(tmp,arr[1]);
                swap(tmp,arr[2]);
                sz++;
            }
            else
            {
                if ( tmp > arr[0] )
                    swap(tmp,arr[0]);
                if ( tmp > arr[1] )
                    swap(tmp,arr[1]);
                if ( tmp > arr[2] )
                    swap(tmp,arr[2]);
            }
        }
        
        return sz < 3 ? arr[0] : arr[2];
    }
};

// similary we can use a set to keep track of the three maxs 
// leveraing the min_element and max_element apis 
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        unordered_set<int> maxs; 
        for ( int n : nums )
        {
            if ( maxs.count(n) == 0 )
            {
                maxs.insert(n);
                if ( maxs.size() > 3 )
                    maxs.erase(*min_element(maxs.begin(),maxs.end()));
            }
        }
        
        if ( maxs.size() < 3 )
            return *max_element(maxs.begin(),maxs.end());
        return *min_element(maxs.begin(),maxs.end());
    }
};

// use the set apis to find the largest num 
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        vector<int> arr(3,INT_MIN);
        int sz = 0;
        unordered_set<int> s(nums.begin(),nums.end());
        int largest = *max_element(s.begin(),s.end());
        if ( s.size() < 3 )
            return largest;
        s.erase(largest);
        s.erase(*max_element(s.begin(),s.end()));
        return *max_element(s.begin(),s.end());
    }
};