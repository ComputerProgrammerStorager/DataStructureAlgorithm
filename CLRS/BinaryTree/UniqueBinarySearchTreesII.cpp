/*
Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.


Example 1:


Input: n = 3
Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
Example 2:

Input: n = 1
Output: [[1]]
 

Constraints:

1 <= n <= 8
*/

// Again we consider each and every number as the root and recursively consider the leftsubtree and rightsubtree.. 
// once we have left and right subtrees, then we can combine them into a the left and right subtrees of the current root.
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        return GetBST(1,n);
    }
    
    vector<TreeNode*> GetBST(int s, int e)
    {
        vector<TreeNode*> res;
        if ( e < s )
        {
            res.push_back(nullptr);
            return res;
        }
        for ( int root = s; root <= e; root++ )
        {
            vector<TreeNode*> left = GetBST(s,root-1);
            vector<TreeNode*> right = GetBST(root+1,e);
            for (auto l : left )
                for ( auto r : right )
                {
                    TreeNode *cur_node = new TreeNode(root);
                    cur_node->left = l;
                    cur_node->right = r;
                    res.push_back(cur_node);
                }
        }
        
        return res;
    }
};