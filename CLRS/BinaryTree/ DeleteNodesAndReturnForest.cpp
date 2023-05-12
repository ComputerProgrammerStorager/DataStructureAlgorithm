/*
Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

Return the roots of the trees in the remaining forest. You may return the result in any order.

 

Example 1:


Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]
Example 2:

Input: root = [1,2,4,null,3], to_delete = [3]
Output: [[1,2,4]]
 

Constraints:

The number of nodes in the given tree is at most 1000.
Each node has a distinct value between 1 and 1000.
to_delete.length <= 1000
to_delete contains distinct values between 1 and 1000.
*/

// Consider a node, if it's deleted, then its children are pushed to the result, and it should return nullptr to its parent 
// IF it's not deleted, and it's a root node, then this root node should be pushed to the result. 
// DFS does the recursive, which takes a node, a set containing the values to delete, a flag to indicate if this is a root and a result set. 

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
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> s(to_delete.begin(),to_delete.end());
        vector<TreeNode *> res;
        dfs(root,s,true,res);
        return res;
    }
private:
    TreeNode* dfs(TreeNode *root, unordered_set<int>& values, bool isRoot, vector<TreeNode*>& res)
    {
        if ( !root )
            return nullptr;
        bool root_deleted = values.count(root->val);
        if ( isRoot && !root_deleted )
            res.push_back(root);
        
        root->left = dfs(root->left, values, root_deleted, res);
        root->right = dfs(root->right,values, root_deleted, res);

        return root_deleted ? nullptr : root;
    }
};