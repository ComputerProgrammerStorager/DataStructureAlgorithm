/*
Given the root of a binary tree and two integers p and q, return the distance between the nodes of value p and value q in the tree.

The distance between two nodes is the number of edges on the path from one to the other.

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 0
Output: 3
Explanation: There are 3 edges between 5 and 0: 5-3-1-0.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 7
Output: 2
Explanation: There are 2 edges between 5 and 7: 5-2-7.
Example 3:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 5
Output: 0
Explanation: The distance between a node and itself is 0.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
0 <= Node.val <= 109
All Node.val are unique.
p and q are values in the tree.
*/

// we can first find the lca of the two given nodes and then the distance is the sum of distance from lca to the two nodes, respectively 
class Solution {
public:
    int findDistance(TreeNode* root, int p, int q) {
        TreeNode* lca = get_lca(root,p,q);
        if ( !lca )
            return -1;
        return dist(lca,p) + dist(lca,q);
    }
    
    TreeNode* get_lca(TreeNode* root, int p, int q)
    {
        if ( !root || root->val == p || root->val == q)
            return root;
        auto left = get_lca(root->left,p,q);
        auto right = get_lca(root->right,p,q);
        if ( left && right )
            return root;
        return left ? left : right;
    }
    
    int dist(TreeNode* lca, int val)
    {
        if (lca == nullptr)
            return INT_MAX/2;
        if ( lca->val == val )
            return 0;
        return 1 + min(dist(lca->left,val),dist(lca->right,val));
    }
};

// we can update the result during the process of finding lca, which necessitates one passs only 
// the auxiliary function returns the distance from root to any of the p and q 
class Solution {
public:
    int findDistance(TreeNode* root, int p, int q) {
        int res = 0;
        if ( p == q )
            return 0;
        root_node_height(root,p,q,res);
        return res;
    }
    
    int root_node_height( TreeNode* root, int p, int q, int &res)
    {
        if ( !root )
            return -1;
        int left = root_node_height(root->left,p,q,res);
        int right = root_node_height(root->right,p,q,res);
        if ( root->val == p || root->val == q )
        {
            if ( left < 0 && right < 0 )
                return 0;
            res = 1 + (left >= 0 ? left : right);
            return -1;
        }
        
        if ( left >= 0 && right >= 0 )
        {
            res = left + right + 2;
            return -1;
        }
        
        if ( left >= 0 ) 
            return left + 1;
        if ( right >= 0 )
            return right+1;
        return -1;
    }
};