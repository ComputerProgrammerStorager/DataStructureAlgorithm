/*
Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.

 

Example 1:


Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
Example 2:

Input: root = [1,2]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-100 <= Node.val <= 100
*/

// Again for this type of questions, we need to consider from the perspective of standing at each node
// The key point is that the diameter depends on the height of the left and right subtree
// As usual, we consider the following two questions when visiting a node:
// 1. What status the parent needs to pass down to its children ? 
//    The result! because visiting this node might lead to a longer diameter 
// 2. What is to return upon completing visiting a node ? 
//    The longer height rooted at the node! Because the height is needed to calcuate the diameter of subtree rooted at it's parent node! 
// For each node, there are two possibilities: 
// 1. The node is the hightest point of the longest diameter, i.e., the diameter is left_h + right_h + 2.
// 2. The node is not the highest point of the longest diameter, then its height would contribute to either left or right part of the highest point.
//    Therefore, we return the bigger of the left or right to its parent.
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int res = 0;
        dfs(root,res);
        return res;
    }
    
private:
    int dfs(TreeNode* root, int &res)
    {
        if ( !root )
            return -1;
        int left_h = dfs(root->left,res);
        int right_h = dfs(root->right,res);
        res = max(res,left_h+right_h+2);
        return max(left_h,right_h) + 1;
    }
};