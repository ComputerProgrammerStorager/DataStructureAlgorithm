/*
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).


Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-1000 <= Node.val <= 1000
*/

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> cur_level;
        if ( root == nullptr )
            return res;
        cur_level.push(root);
        
        while ( !cur_level.empty() )
        {
            int cur_size = cur_level.size();
            vector<int> cur_level_res;
            for ( int i = 0; i < cur_size; i++ )
            {
                TreeNode *tmp = cur_level.front();
                cur_level.pop();
                cur_level_res.push_back(tmp->val);
                if ( tmp->left )
                    cur_level.push(tmp->left);
                if ( tmp->right)
                    cur_level.push(tmp->right);
            }

            res.push_back(cur_level_res);
        }
        return res;
    }
};