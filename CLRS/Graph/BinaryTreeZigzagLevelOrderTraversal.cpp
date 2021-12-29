/*
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-100 <= Node.val <= 100

*/

// use deque and remember what's the current direction 
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if ( !root )
            return res;
        bool left = true;
        deque<TreeNode*> q;
        q.push_back(root);
        while( !q.empty() )
        {
            vector<int> level;
            deque<TreeNode*> next_level;
            if ( left )
            {
                while(!q.empty())
                {
                    TreeNode* cur = q.front();
                    q.pop_front();
                    level.push_back(cur->val);
                    if ( cur->left )
                        next_level.push_back(cur->left);
                    if ( cur->right )
                        next_level.push_back(cur->right);
                }
            }
            else {
                while(!q.empty())
                {
                    TreeNode* cur = q.back();
                    q.pop_back();
                    level.push_back(cur->val);
                    if ( cur->right )
                        next_level.push_front(cur->right);
                    if ( cur->left )
                        next_level.push_front(cur->left);
                }
            }
            left = !left;
            res.push_back(level);
            q = next_level;
        }
        
        return res;
    }
};

// could also use dfs and update the level as we recurse
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if ( !root )
            return res;
        dfs(root,0,res);
        return res;
    }
    
    void dfs(TreeNode*root, int level, vector<vector<int>> &res)
    {
        if ( level >= res.size() )
        {
            vector<int> new_level(1,root->val);
            res.push_back(new_level);
        } 
        else {
            if ( level % 2 == 0 )       // left to right 
            {
                res[level].push_back(root->val);
            }
            else
            {
                res[level].insert(res[level].begin(),root->val);
            }
        }
        
        if ( root->left )
            dfs(root->left,level+1,res);
        if ( root->right )
            dfs(root->right,level+1,res);
    }
};