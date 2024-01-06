/*
Given a 2D integer array nums, return all elements of nums in diagonal order as shown in the below images.

 

Example 1:


Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,4,2,7,5,3,8,6,9]
Example 2:


Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i].length <= 105
1 <= sum(nums[i].length) <= 105
1 <= nums[i][j] <= 105
*/

// group by sum of row and col and walk upward and from left to right 
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        unordered_map<int,vector<int>> m; 
        vector<int> res;
        for ( int i = nums.size() - 1; i >= 0; i-- ) {
            for ( int j = 0; j < nums[i].size(); j++ ) {
                m[i+j].push_back(nums[i][j]);
            }
        }

        int cur = 0;
        while( m.count(cur) ) {
            for ( auto val : m[cur] ) {
                res.push_back(val);
            }
            cur++;
        }
        return res;
    }
};


// we can use BFS using {0,0} as the seed 
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        vector<int> res; 
        queue<pair<int,int>> q; 
        q.push({0,0});
        while(!q.empty()) { 
            auto [row, col] = q.front();
            q.pop();
            res.push_back(nums[row][col]);
            if ( col == 0 && row + 1 < nums.size() ) 
                q.push({row+1,col});
            if ( col+1 < nums[row].size() ) {
                q.push({row,col+1});
            }
        }
        return res;
    }
};