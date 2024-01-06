/*
Given the root of a Binary Search Tree (BST), return the minimum difference between the values of any two different nodes in the tree.

 

Example 1:


Input: root = [4,2,6,1,3]
Output: 1
Example 2:


Input: root = [1,0,48,null,null,12,49]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [2, 100].
0 <= Node.val <= 105
*/

// DFS and remember the immediately before node's val 
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
    int minDiffInBST(TreeNode* root) {
        int min_diff = INT_MAX, prev_val = INT_MIN;
        dfs(root,min_diff,prev_val);
        return min_diff;
    }
    void dfs(TreeNode* root, int& min_diff, int& prev_val) {
        if ( !root )
            return;
        dfs(root->left,min_diff,prev_val);
        if ( prev_val != INT_MIN ) 
            min_diff = min(min_diff, root->val - prev_val);
        prev_val = root->val;
        dfs(root->right, min_diff,prev_val);
    }
};