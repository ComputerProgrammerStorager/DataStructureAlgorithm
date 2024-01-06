/*
Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e., from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]
Example 2:


Input: root = [3,9,8,4,0,1,7]
Output: [[4],[9],[3,0,1],[8],[7]]
Example 3:


Input: root = [3,9,8,4,0,1,7,null,null,null,2,5]
Output: [[4],[9,5],[3,0,1],[8,2],[7]]
*/

// BFS and append, sorting by columns and row sorting is implicitedly enforced. 
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        unordered_map<int,vector<int>> coltbl;
        queue<pair<TreeNode*, int>> q;
        vector<vector<int>> res;
        int min_col = 0, max_col = 0;
        if ( !root )
            return res;
        q.push({root,0});
        while(!q.empty()) {
            auto cur_node = q.front().first;
            auto cur_col = q.front().second;
            q.pop();
            coltbl[cur_col].push_back(cur_node->val);
            if ( cur_node->left )
            {
                min_col = min(min_col, cur_col-1);
                q.push({cur_node->left,cur_col-1});
            }
            if ( cur_node->right )
            {
                max_col = max(max_col, cur_col+1);
                q.push({cur_node->right,cur_col+1});
            }
        }

        for ( int i = min_col; i <= max_col; i++ )
        {
            res.push_back(coltbl[i]);
        }

        return res;
    }
};

// DFS: sort the same column based on the row number 
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        unordered_map<int,vector<pair<int,int>>> m;
        int min_col = 0, max_col = 0;
        vector<vector<int>> res;
        auto cmp = [](pair<int,int> a, pair<int,int>b) {
            return a.first < b.first;
        };
        if ( !root )
            return res;
        dfs(root,0,0,m,min_col,max_col);
        for ( int i = min_col; i <= max_col; i++ )
        {
            sort(m[i].begin(),m[i].end(),cmp);
            vector<int> sortedcolumn;
            for ( auto it = m[i].begin(); it != m[i].end(); it++ )
                sortedcolumn.push_back(it->second);
            res.push_back(sortedcolumn);
        }
        return res;
    }
    void dfs(TreeNode* node, int row, int col, unordered_map<int,vector<pair<int,int>>>& m, int& min_col, int &max_col) 
    {
        if ( !node )
            return;
        m[col].push_back({row,node->val});
        if ( node->left )
            dfs(node->left,row+1,col-1,m,min_col,max_col);
        if ( node->right)
            dfs(node->right,row+1,col+1,m,min_col,max_col);
        min_col = min(min_col, col);
        max_col = max(max_col, col);
    }
};