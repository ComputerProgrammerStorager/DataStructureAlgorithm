/*
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
 

Example 1:


Input: root = [2,1,3]
Output: true
Example 2:


Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1

*/

// Always consider the two conditions: 
// 1. Return value: what to return to parent after a node is processed ? value indicating if the subtree is a BST or not
// 2. Passing state: what state the parent needs to pass down to a subtree call ? the value range that all nodes of the subtree have to be fall within
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root,LONG_MIN,LONG_MAX);
    }
    bool helper(TreeNode *root, long min_val, long max_val)
    {
        if ( !root )
            return true;
        if ( root->val <= min_val || root->val >= max_val )
            return false;
        return helper(root->left,min_val, root->val) && helper(root->right,root->val, max_val);
        
    }
};