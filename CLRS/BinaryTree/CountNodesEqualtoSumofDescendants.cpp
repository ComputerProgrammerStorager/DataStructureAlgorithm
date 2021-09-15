/*
Given the root of a binary tree, return the number of nodes where the value of the node is equal to the sum of the values of its descendants.

A descendant of a node x is any node that is on the path from node x to some leaf node. The sum is considered to be 0 if the node has no descendants.

 

Example 1:


Input: root = [10,3,4,2,1]
Output: 2
Explanation:
For the node with value 10: The sum of its descendants is 3+4+2+1 = 10.
For the node with value 3: The sum of its descendants is 2+1 = 3.
Example 2:


Input: root = [2,3,null,2,null]
Output: 0
Explanation:
No node has a value that is equal to the sum of its descendants
*/

// Again, we asked the same two questions:
// 1. what we need to return upon visiting a node ? 
//          return the sum of the subtree rooted at the node
// 2. what state we need to maintain ? 
//          update the number of qualifying nodes if it satisfies the condition 
class Solution {
public:
    int equalToDescendants(TreeNode* root) {
        int cnt = 0;
        dfs(root,cnt);
        return cnt;
    }
    
    long long dfs(TreeNode* root, int &cnt)
    {
        if ( !root )
            return 0;
        long long left_sum = dfs(root->left, cnt);
        long long right_sum = dfs(root->right,cnt);
        if ( left_sum + right_sum == root->val )
            cnt++;
        return left_sum + right_sum + root->val;
    }
};