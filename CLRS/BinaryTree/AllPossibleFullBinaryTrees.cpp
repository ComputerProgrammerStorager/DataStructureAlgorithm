/*
Given an integer n, return a list of all possible full binary trees with n nodes. Each node of each tree in the answer must have Node.val == 0.

Each element of the answer is the root node of one possible tree. You may return the final list of trees in any order.

A full binary tree is a binary tree where each node has exactly 0 or 2 children.

 

Example 1:


Input: n = 7
Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
Example 2:

Input: n = 3
Output: [[0,0,0]]
 

Constraints:

1 <= n <= 20
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
    vector<TreeNode*> allPossibleFBT(int n) {
        if ( n % 2 == 0 )
            return {};
        vector<vector<TreeNode*>> dp(n+1);
        dp[1].push_back(new TreeNode());

        for ( int nodes = 3; nodes <= n; nodes += 2 ) {
            for ( int l = 1; l < nodes-1; l += 2 ) {
                auto left = dp[l], right = dp[nodes-l-1];
                for (auto l_child : left )
                    for ( auto r_child : right ) {
                        TreeNode *root = new TreeNode(0,l_child,r_child);
                        dp[nodes].push_back(root);
                    }
            }
        }

        return dp[n];
    }
};