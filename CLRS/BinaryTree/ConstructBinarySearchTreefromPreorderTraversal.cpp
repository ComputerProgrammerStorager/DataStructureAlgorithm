/*
Given an array of integers preorder, which represents the preorder traversal of a BST (i.e., binary search tree), construct the tree and return its root.

It is guaranteed that there is always possible to find a binary search tree with the given requirements for the given test cases.

A binary search tree is a binary tree where for every node, any descendant of Node.left has a value strictly less than Node.val, and any descendant of Node.right has a value strictly greater than Node.val.

A preorder traversal of a binary tree displays the value of the node first, then traverses Node.left, then traverses Node.right.

 

Example 1:


Input: preorder = [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]
Example 2:

Input: preorder = [1,3]
Output: [1,null,3]
 

Constraints:

1 <= preorder.length <= 100
1 <= preorder[i] <= 1000
All the values of preorder are unique.
*/

// it is easy to conver it to a problem knowing both preorder and inorder 
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
        root->left = getroot(preorder,inorder,l,m_in[root_val]-1);
        root->right = getroot(preorder,inorder,m_in[root_val]+1,r);
        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        vector<int> inorder(preorder);
        sort(inorder.begin(),inorder.end());
        int n = preorder.size();
        for ( int i = 0; i < n; i++ )
            m_in[inorder[i]] = i;
        return getroot(preorder,inorder,0,n-1);
    }
};

// We can multiplex the method of validating BST using lower and upper limits 
class Solution {
private:
    int pre_idx;
    int n;
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        pre_idx = 0;
        n = preorder.size();
        return helper(LONG_MIN,LONG_MAX,preorder);
    }
    TreeNode* helper(long lower, long upper, vector<int>& preorder)
    {
        if ( pre_idx == n )
            return nullptr;
        int val = preorder[pre_idx];
        if ( val < lower || val > upper )
            return nullptr;
        pre_idx++;
        TreeNode* root = new TreeNode(val);
        root->left = helper(lower,val, preorder);
        root->right = helper(val, upper, preorder);
        return root;
    }
};

// use a stack simulate building an BST
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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        stack<TreeNode*> nodes; 
        int n = preorder.size();
        if ( n == 0 )
            return nullptr;
        auto root = new TreeNode(preorder[0]);
        nodes.push(root);
        for ( int i = 1; i < n; i++ )
        {
            auto parent = nodes.top(), child = new TreeNode(preorder[i]);
            while( !nodes.empty() && nodes.top()->val < child->val )
            {
                parent = nodes.top();
                nodes.pop();
            }
            if (parent->val < child->val)
                parent->right = child;
            else 
                parent->left = child;
            nodes.push(child);
        }

        return root;
    }
};