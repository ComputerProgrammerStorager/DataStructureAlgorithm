/*
Given the root of a binary tree, invert the tree, and return its root.

Example 1:


Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]
Example 2:


Input: root = [2,1,3]
Output: [2,3,1]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100

*/

// Recursively invert every subtree 
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if ( !root )
            return root;
        TreeNode* new_left = invertTree(root->left);
        TreeNode* new_right = invertTree(root->right);
        root->left = new_right;
        root->right = new_left;
        return root;
    }
};

// we can also use iterative method as the level order traversal to swap the children of each and every node
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if ( !root )
            return root;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            TreeNode *cur_node = q.front();
            q.pop();
            TreeNode* tmp = cur_node->left;
            cur_node->left = cur_node->right;
            cur_node->right = tmp;
            if ( cur_node->left)
                q.push(cur_node->left);
            if ( cur_node->right)
                q.push(cur_node->right);
        }
        
        return root;
    }
};