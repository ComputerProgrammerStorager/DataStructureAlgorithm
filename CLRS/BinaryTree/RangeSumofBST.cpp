/*
Given the root node of a binary search tree and two integers low and high, return the sum of values of all nodes with a value in the inclusive range [low, high].

 

Example 1:


Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
Output: 32
Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.
Example 2:


Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
Output: 23
Explanation: Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.
 

Constraints:

The number of nodes in the tree is in the range [1, 2 * 104].
1 <= Node.val <= 105
1 <= low <= high <= 105
All Node.val are unique.

*/

// add the value while dfsing the nodes.. 
// the condition of BST helps cutting recursive branches 
class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        int sum = 0;
        dfs(root,sum,low,high);
        return sum;
    }
    
    void dfs( TreeNode* root, int &sum, int low, int high)
    {
        if ( !root )
            return;
        if ( root->val <= high && root->val >= low )
            sum += root->val;
        if ( root->val > low )
            dfs(root->left,sum,low,high);
        if ( root->val < high )
            dfs(root->right,sum,low,high);
    }
};

// we can emulate the recursion process via explicitly using a stack 
class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        int sum = 0;
        stack<TreeNode*> s;
        s.push(root);
        while(!s.empty())
        {
            TreeNode *cur = s.top();
            s.pop();
            if ( cur )
            {
                if ( cur->val >= low && cur->val <= high )
                    sum += cur->val;
                if ( cur->val > low )
                    s.push(cur->left);
                if ( cur->val < high )
                    s.push(cur->right);
            }
        }
        return sum;
    }
};