/*
Given the root of a binary tree, return the maximum average value of a subtree of that tree. Answers within 10-5 of the actual answer will be accepted.

A subtree of a tree is any node of that tree plus all its descendants.

The average value of a tree is the sum of its values, divided by the number of nodes.

 

Example 1:


Input: root = [5,6,1]
Output: 6.00000
Explanation: 
For the node with value = 5 we have an average of (5 + 6 + 1) / 3 = 4.
For the node with value = 6 we have an average of 6 / 1 = 6.
For the node with value = 1 we have an average of 1 / 1 = 1.
So the answer is 6 which is the maximum.
Example 2:

Input: root = [0,null,1]
Output: 1.00000
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 105

*/

// as usual,we ask the two questions 
// 1. what need to return after visiting a node ? 
//          return the how many nodes and the total sum in the subtree rooted at the given node
// 2. what state need to update when visisting a node ? 
//          update the max average if it needs to 
class Solution {
public:
    double maximumAverageSubtree(TreeNode* root) {
        double res = -DBL_MAX;
        dfs(root,res);
        return res;
    }
    
    vector<int> dfs(TreeNode* root, double& max_avg)
    {
        vector<int> l,r;
        if ( !root )
            return {0,0};
        l = dfs(root->left,max_avg);
        r = dfs(root->right,max_avg);
        int sum = l[0] + r[0] + root->val;
        int num = l[1] + r[1] + 1;
        max_avg = max(max_avg,(double)sum/num);
        return {sum,num};
    }
};