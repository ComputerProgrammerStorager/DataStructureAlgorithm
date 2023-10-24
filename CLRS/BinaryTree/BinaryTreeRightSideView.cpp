/*
Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

 

Example 1:


Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]
Example 2:

Input: root = [1,null,3]
Output: [1,3]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
*/

// recusive right child first, so when we need to expand the level size, the current node is the rightmost node 
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if ( !root )
            return res;
        helper(root,0,res);
        return res;
    }

    void helper(TreeNode* root, int level, vector<int>& res)
    {
        if ( level == res.size() )
            res.push_back(root->val);
        if ( root->right )
            helper(root->right,level+1,res);
        if ( root->left )
            helper(root->left,level+1,res);
    }
};

// we can do a level order traversal and get the last number of each level 
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> q;
        if ( !root )
            return res;
        q.push(root);
        while(!q.empty())
        {
            int q_sz = q.size();
            for ( int i = 0;i < q_sz; i++ )
            {
                auto node = q.front();
                q.pop();
                if ( i == q_sz - 1 )
                    res.push_back(node->val);
                if ( node->left )
                    q.push(node->left);
                if ( node->right )
                    q.push(node->right);
            }
        }

        return res;
    }
};


// do a level order traversal and push the last element of the queue to the result for each level 