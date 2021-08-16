/*
Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary search tree.

A height-balanced binary tree is a binary tree in which the depth of the two subtrees of every node never differs by more than one.

 

Example 1:


Input: nums = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: [0,-10,5,null,-3,null,9] is also accepted:

Example 2:


Input: nums = [1,3]
Output: [3,1]
Explanation: [1,3] and [3,1] are both a height-balanced BSTs.
 

Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums is sorted in a strictly increasing order.

*/

// simulate in-order traversal
class Solution {
    int cur_node;
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        cur_node = 0;
        return helper(0,nums.size()-1,nums);
    }
    
    TreeNode *helper(int l, int r,vector<int>& nums)
    {
        if ( l > r )
            return nullptr;
        int mid = (l+r)/2;
        TreeNode* left = helper(l,mid-1,nums);
        TreeNode* node = new TreeNode(nums[cur_node++]);
        node->left = left;
        node->right = helper(mid+1,r,nums);
        return node;
    }
};

// recursive 
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(0,nums.size()-1,nums);
    }
    
    TreeNode* helper(int l, int r, vector<int>& nums)
    {
        if ( l > r ) 
            return nullptr;
        int mid = (l+r)/2;
        TreeNode *root = new TreeNode(nums[mid]);
        //if ( l != r )
        {
            root->left = helper(l,mid-1,nums);
            root->right = helper(mid+1,r,nums);
        }

        return root;
    }
};