/*
The thief has found himself a new place for his thievery again. There is only one entrance to this area, called root.

Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if two directly-linked houses were broken into on the same night.

Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.

 

Example 1:


Input: root = [3,2,3,null,3,null,1]
Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:


Input: root = [3,4,5,1,3,null,1]
Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 104
*/


// for each node we return two results: [0]: the amount including rob it, [1]: the amount of not robbing it 
// rob value would be its value plus not_rob children 
// not rob value would be the children could be either robbed or not robbed 

class Solution {
public:
    int rob(TreeNode* root) {
        auto res = helper(root);
        return max(res[0],res[1]);
    }
private:
    vector<int> helper(TreeNode *root)
    {
        if ( !root )
            return {0,0};
        auto left = helper(root->left);
        auto right = helper(root->right);
        int rob = left[1] + right[1] + root->val;
        int not_rob = max(left[0],left[1]) + max(right[0],right[1]);
        return {rob,not_rob};
    }
};