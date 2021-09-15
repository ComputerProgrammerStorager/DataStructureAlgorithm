/*
Given the root of a binary tree, return the number of uni-value subtrees.

A uni-value subtree means all nodes of the subtree have the same value.

 

Example 1:


Input: root = [5,1,5,5,5,null,5]
Output: 4
Example 2:

Input: root = []
Output: 0
Example 3:

Input: root = [5,5,5,5,5,null,5]
Output: 6
 

Constraints:

The numbrt of the node in the tree will be in the range [0, 1000].
-1000 <= Node.val <= 1000

*/

// we need to return whether the current subtree is a univalude tree or not
class Solution {
public:
    int countUnivalSubtrees(TreeNode* root) {
        int cnt = 0;
        univalueSubtree(root,cnt);
        return cnt;
    }
    bool univalueSubtree(TreeNode *root, int &cnt)
    {
        if ( !root )
            return true;
        bool left = univalueSubtree(root->left,cnt);
        bool right = univalueSubtree(root->right,cnt);
        if ((left&&right)
           &&(root->left == nullptr || root->left->val == root->val)
           &&(root->right == nullptr || root->right->val == root->val) )
        {
            cnt++;
            return true;
        }
        
        return false;
    }
};