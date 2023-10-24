/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
 

Constraints:

3 <= nums.length <= 3000
-105 <= nums[i] <= 105
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        for ( int i = 0; i < n-2; i++ )
        {
            if ( i > 0 && nums[i] == nums[i-1] )
                continue;
            if ( nums[i] > 0 )
                break;
            int l = i+1, r = n-1;
            while( l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if ( sum == 0 )
                {
                    res.push_back({nums[i],nums[l++],nums[r--]});
                    while( l<r && nums[l] == nums[l-1] )
                        l++;
                } else if (sum > 0 ) {
                    r--;
                } else {
                    l++;
                }
            }
        }

        return res;
    }
};

// Based on 2 sum 
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        for ( int i = 0; i < nums.size() && nums[i] <= 0; i++ )
        {
            if ( i == 0 || nums[i-1] != nums[i] )
                twoSum(nums,i,res);
        }

        return res;
    }

private:
    void twoSum(const vector<int>& nums, int pos, vector<vector<int>>& res)
    {
        unordered_set<int> seen;
        for ( int j = pos+1; j < nums.size(); j++ )
        {
            int rem = -nums[pos]-nums[j];
            if ( seen.count(rem) )
            {
                res.push_back({nums[pos],rem,nums[j]});
                while( j + 1 < nums.size() && nums[j] == nums[j+1] )
                    j++;
            }
            seen.insert(nums[j]);
        }
    }
};

// No sorting
// 
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> res;
        unordered_set<int> dups;    // start i is already checked 
        unordered_map<int,int> seen;    // when the next j maps to a start i: used to check if the rem of j is i 
        for ( int i = 0; i < nums.size(); i++ )
        {
            if ( dups.insert(nums[i]).second )
            {
                for ( int j = i+1; j < nums.size(); j++ )
                {
                    int rem = -nums[i]-nums[j];
                    auto it = seen.find(rem);
                    if ( it != end(seen) && it->second == i )
                    {
                        vector<int> one = {nums[i],nums[j],rem};
                        sort(one.begin(),one.end());
                        res.insert(one);
                    }
                    seen[nums[j]] = i;
                }
            }
        }

        return vector<vector<int>>(begin(res),end(res));
    }
};