/*
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

a binary tree in which the left and right subtrees of every node differ in height by no more than 1.

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: true
Example 2:


Input: root = [1,2,2,3,3,null,null,4,4]
Output: false
Example 3:

Input: root = []
Output: true
 

Constraints:

The number of nodes in the tree is in the range [0, 5000].
-104 <= Node.val <= 104

*/

// Essentially we check each and every node to see if it's balanced. In order to do that we need to obtain each node's height 
// Since each node's height has to be >= zero, then we can use -1 return value to return its an unbalanced tree
// In this way, we only visit once per node 
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return get_tree_height(root) != -1;
    }

    int get_tree_height(TreeNode* root)
    {
        if (!root)
            return 0;
        int left_height = get_tree_height(root->left);
        int right_height = get_tree_height(root->right);
        if ( left_height == -1 || right_height == -1 || abs(left_height-right_height) > 1 )
            return -1;
        return max(left_height,right_height) + 1;
    }
};

// The same idea of calculating tree height first, but the height of a tree is repeatedly calculated for the times of the 
// number of trees that the node happens to be part of 
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if ( !root )
            return true;
        return abs(get_tree_height(root->left)-get_tree_height(root->right)) < 2 && isBalanced(root->left) && isBalanced(root->right);
    }

    int get_tree_height(TreeNode* root)
    {
        if ( !root )
            return -1;
        return 1 + max(get_tree_height(root->left),get_tree_height(root->right));
    }
};