/*
A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any path.
*/

// for each node, we could have it only part of an existing recursive path or starte a new path with it being the highest point in which we need to update the global maximum if it qualifies
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int sum = INT_MIN;
        maxnodeContribution(root,sum);
        return sum;
    }
    
    int maxnodeContribution(TreeNode* node, int &sum)
    {
        if ( node == nullptr )
            return 0;
        int left = max(0,maxnodeContribution(node->left,sum));
        int right = max(0,maxnodeContribution(node->right,sum));
        
        int partpath = node->val + max(left,right);
        int newpath = left + right + node->val;
        
        sum = max(sum,newpath);
        return partpath;
    }
};