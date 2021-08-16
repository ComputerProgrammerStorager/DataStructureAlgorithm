/*
Given a binary tree root, a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.

Return the number of good nodes in the binary tree.

 

Example 1:



Input: root = [3,1,4,3,null,1,5]
Output: 4
Explanation: Nodes in blue are good.
Root Node (3) is always a good node.
Node 4 -> (3,4) is the maximum value in the path starting from the root.
Node 5 -> (3,4,5) is the maximum value in the path
Node 3 -> (3,1,3) is the maximum value in the path.
Example 2:



Input: root = [3,3,null,4,2]
Output: 3
Explanation: Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.
Example 3:

Input: root = [1]
Output: 1
Explanation: Root is considered as good.
 

Constraints:

The number of nodes in the binary tree is in the range [1, 10^5].
Each node's value is between [-10^4, 10^4].

*/

// use a stack to maintain the so far max value along the path 
class Solution {
public:
    int goodNodes(TreeNode* root) {
        stack<int> pathmax;
        int cnt = 0;
        helper(root,pathmax,cnt);
        return cnt;
    }
    void helper(TreeNode* node, stack<int> &pathmax, int &cnt)
    {
        if ( node == nullptr )
            return;

        if ( pathmax.size() == 0 || pathmax.top() <= node->val )
        {
            cnt++;
            pathmax.push(node->val);
        }
        helper(node->left,pathmax,cnt);
        helper(node->right,pathmax,cnt);
        if ( pathmax.top() == node->val )
        {
            pathmax.pop();
        }
    }
};

// we can save the explicit usage of stack 
class Solution {
public:
    int goodNodes(TreeNode* root) {
        return helper(root, INT_MIN);
    }
    int helper(TreeNode* node, int cur_max = INT_MIN)
    {
        if ( node == nullptr )
            return 0;
        return (node->val >= cur_max) + helper(node->left,max(cur_max,node->val)) + helper(node->right,max(cur_max,node->val));
    }
};