/*
Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: preorder = [-1], inorder = [-1]
Output: [-1]
 

Constraints:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder and inorder consist of unique values.
Each value of inorder also appears in preorder.
preorder is guaranteed to be the preorder traversal of the tree.
inorder is guaranteed to be the inorder traversal of the tree.
*/

// preorder order gives the root in sequentience, so if we have a node as the root, then its left and right subarrais formuate 
// its left and right subtree respectively. 
// so we can gradually build the roots and subtrees, in order to fasten the division of inorder array 
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
private:
    int pre_idx; 
    unordered_map<int,int> m_in;
    TreeNode* getroot(vector<int>& preorder, vector<int>& inorder, int l, int r)
    {
        if ( l > r )
            return nullptr;
        int root_val = preorder[pre_idx++];
        TreeNode* root = new TreeNode(root_val);
        root->left = getroot(preorder,inorder, l,m_in[root_val]-1);
        root->right = getroot(preorder,inorder,m_in[root_val]+1,r);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        for ( int i = 0; i < n; i++ )
        {
            m_in[inorder[i]] = i;
        }
        pre_idx = 0;
        return getroot(preorder,inorder,0,n-1);
    }
};