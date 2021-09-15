/*
Given the root of a binary tree, flatten the tree into a "linked list":

The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
The "linked list" should be in the same order as a pre-order traversal of the binary tree.
 

Example 1:


Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [0]
Output: [0]
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-100 <= Node.val <= 100
 

Follow up: Can you flatten the tree in-place (with O(1) extra space)?
*/

// Kth smallest in BST 

// First, since it's equal to preorder traversal, then we can do a preorder traversal and then link the nodes together 
class Solution {
public:
    void flatten(TreeNode* root) {
        vector<TreeNode*> preorder;
        if ( !root )
            return;
        pre_order(preorder,root);
        for ( int i = 0; i < preorder.size(); i++ )
        {
            if ( i == preorder.size() - 1 )
            {
                preorder[i]->right = nullptr;
            }
            else 
            {
                preorder[i]->right = preorder[i+1];
            }
            
            preorder[i]->left = nullptr;
        }

    }
    
private: 
    void pre_order(vector<TreeNode *> &preorder, TreeNode * root)
    {
        if ( !root )
            return;
        preorder.push_back(root);
        pre_order(preorder,root->left);
        pre_order(preorder,root->right);
    }
};


// we can use iterative with a stack to emulate the preorder traversal 
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode *tail = nullptr;
        if ( !root )
            return;
        stack<TreeNode*> s;
        s.push(root);
        while( !s.empty() )
        {
            TreeNode *cur = s.top();
            s.pop();
            if ( tail )
            {
                tail->left = nullptr;
                tail->right = cur;
            }
            tail = cur;
            if ( cur->right )
                s.push(cur->right);
            if ( cur->left )
                s.push(cur->left);
        }
        if ( tail )
        {
            tail->left = nullptr;
            tail->right = nullptr;
        }
    }
    
};

// We can also use recursion to flatten the tree.. 
// Assume we have flattened left and right subtrees, then we only need to perform the following three steps to ge the finally flattened linked list 
// 1. We need to move the left subtree between the node and the right flattened subtree
// 2. we need to set left subtree to nullptr 
// 3. we need to concatenate the right flatten subtree to tail the tail of the left flattened subtree 
class Solution {
public:
    void flatten(TreeNode* root) {
        if (!root )
            return;
        if ( root->left )
            flatten(root->left);
        if ( root->right )
            flatten(root->right);
        TreeNode *tmp = root->right;
        root->right = root->left;
        root->left = nullptr;
        while(root->right)
            root = root->right;
        root->right = tmp;
    }
};

// There is another solution without using any extra memory. 
// The point is for each node, we find the rightmost node in its' left child (if it exists) 
// once we have the rightmost, we do the following reconnection: 
// rightmost.right = node.right         because the rightmost is the immediately preceding node to the whole right subtree 
// node.right = node.left               move the whole left subtree (containing rightmost) to the right subtree.. essentially moving the whole left subtree between node and its original right subtree 
// node.left = nullptr                  reset left subtree to nullptr
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode *node = root;
        if ( !node )
            return;
        while( node )
        {
            if ( node->left )
            {
                TreeNode* rightmost = node->left;
                while( rightmost->right )
                    rightmost = rightmost->right;
                rightmost->right = node->right;
                node->right = node->left;
                node->left = nullptr;
            }
            
            node = node->right;
        }
    }
};