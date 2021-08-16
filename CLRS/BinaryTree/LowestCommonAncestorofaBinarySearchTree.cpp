/*
Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:


Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.
Example 2:


Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: root = [2,1], p = 2, q = 1
Output: 2
*/

// leverage the property of BST. This problem assumes the given p and q must bit existent nodes in the tree 
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if ( root->val < min(p->val,q->val) )
            return lowestCommonAncestor(root->right,p,q);
        if ( root->val > max(p->val,q->val) )
            return lowestCommonAncestor(root->left,p,q);
        return root;
    }
};


// General approach which applies to binary tree should also apply to BST
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if ( !root || p == root || q == root )
        {
            return root;
        }
        TreeNode *l = lowestCommonAncestor(root->left,p,q);
        TreeNode *r = lowestCommonAncestor(root->right,p,q);
        if ( l && r )
        {
            return root;
        }
        if ( !l )
            return r;
        if ( !r )
            return l;
        return nullptr;
    }
};