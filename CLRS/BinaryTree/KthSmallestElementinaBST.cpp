/*
Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.

 

Example 1:


Input: root = [3,1,4,null,2], k = 1
Output: 1
Example 2:


Input: root = [5,3,6,2,4,null,null,1], k = 3
Output: 3
 

Constraints:

The number of nodes in the tree is n.
1 <= k <= n <= 104
0 <= Node.val <= 104
 

Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?
*/

// inorder traversal and then take the k-1 th element 
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int> inorder;
        helper(root,inorder);
        return inorder[k-1];
    }
private:
    void helper(TreeNode *root, vector<int>& inorder)
    {
        if ( !root )
            return;
        helper(root->left,inorder);
        inorder.push_back(root->val);
        helper(root->right,inorder);
    }
};

// Simulation the traversal process using a stack 
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> s;
        while(1)
        {
            while(root)
            {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            if ( --k == 0 )
                return root->val;
            root = root->right;
        }

        return -1;
    }
};