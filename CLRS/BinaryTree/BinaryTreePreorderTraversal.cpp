/*
Given the root of a binary tree, return the preorder traversal of its nodes' values.

 

Example 1:


Input: root = [1,null,2,3]
Output: [1,2,3]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [1]
Output: [1]
Example 4:


Input: root = [1,2]
Output: [1,2]
Example 5:


Input: root = [1,null,2]
Output: [1,2]
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
*/


// Recursion method
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        preorder(root,res);
        return res;
        
    }
    
    void preorder(TreeNode *root, vector<int>& res)
    {
        if (!root)
            return;
        res.push_back(root->val);
        preorder(root->left,res);
        preorder(root->right,res);
            
    }
};

// use stack to emulate the traversal process
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> s;
        if (!root)
            return {};
        s.push(root);
        while(!s.empty())
        {
            TreeNode* cur = s.top();
            res.push_back(cur->val);
            s.pop();
            if (cur->right)
                s.push(cur->right);
            if (cur->left)
                s.push(cur->left);
                
        }
        return res;
        
    }
};

// the above two methods use extar memory space, either due to recusion or stack 
// We can us morris traversal to complete the traversal without any extra memory 
// The key insight is that we leverage the inorder predecessor, which we will encounter twice during the traversal process 
// The first time is when we process the current node, as we go down to find the rightmost node of its left subtree 
// The second time is when we process the predecessor node itself, in this case we restore the right link to nullptr and move to its 
// right link, which was established when by the first time. Then node will point to the root (whose left subtree has completed). But we still 
// go the rightmost node of its left subtree, but to find it links to the current node, so we then restore the link to nullptr and move to right subtree.
// Note: so beautiful you will find if we walk through the algorithm with an example. 
// Possible improvement: we traverse each left subtree twice, one to establish the link and the other is to restore the link
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode *node = root;
        if ( !node )
            return res;
        while(node)
        {
            if ( node->left == nullptr )
            {
                res.push_back(node->val);
                node = node->right;
            }
            else 
            {
                TreeNode *prev = node->left;
                while( prev->right && prev->right != node )
                {
                    prev = prev->right;
                }
                
                if ( !prev->right )     // first time, process the current node, establish the link and move to left subtree 
                {
                    res.push_back(node->val);
                    prev->right = node;
                    node = node->left;
                }
                else        // second time, restore the link and move to right subtree. Note: at this moment, node is pointing to prev's successor, which was reached by the if cond in last loop
                {
                    prev->right = nullptr;
                    node = node->right;
                }
            }
        }
        
        return res;
    }
};