/*
Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

A leaf is a node with no children.

 

Example 1:


Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
Explanation: The root-to-leaf path with the target sum is shown.
Example 2:


Input: root = [1,2,3], targetSum = 5
Output: false
Explanation: There two root-to-leaf paths in the tree:
(1 --> 2): The sum is 3.
(1 --> 3): The sum is 4.
There is no root-to-leaf path with sum = 5.
Example 3:

Input: root = [], targetSum = 0
Output: false
Explanation: Since the tree is empty, there are no root-to-leaf paths.
 

Constraints:

The number of nodes in the tree is in the range [0, 5000].
-1000 <= Node.val <= 1000
-1000 <= targetSum <= 1000
*/

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
    bool hasPathSum(TreeNode* root, int targetSum) {
        bool found = false;
        dfs(root,0,targetSum,found);
        return found;
    }

    void dfs(TreeNode* root, int cur, int targetSum, bool& found) {
        if ( !root || found ) 
            return;
        int val = cur+root->val;
        if (val == targetSum && !root->left && !root->right ) {
            found = true;
            return;
        }
        dfs(root->left,val,targetSum,found);
        dfs(root->right,val,targetSum,found);
    }
};

// Can translate it to iterative approach 

class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        stack<pair<TreeNode*,int>> st;
        if (!root) 
            return false;
        st.push({root,targetSum});
        while(!st.empty()) {
            auto [node,remainSum] = st.top();
            st.pop();
            remainSum -= node->val;
            if ( remainSum == 0 && !node->left && !node->right ) {
                return true;
            }
            if ( node->left ) 
                st.push({node->left,remainSum});
            if ( node->right )
                st.push({node->right,remainSum});
        }

        return false;
    }
};