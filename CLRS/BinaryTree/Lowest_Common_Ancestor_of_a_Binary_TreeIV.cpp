/*
Given the root of a binary tree and an array of TreeNode objects nodes, return the lowest common ancestor (LCA) of all the nodes in nodes. All the nodes will exist in the tree, and all values of the tree's nodes are unique.

Extending the definition of LCA on Wikipedia: "The lowest common ancestor of n nodes p1, p2, ..., pn in a binary tree T is the lowest node that has every pi as a descendant (where we allow a node to be a descendant of itself) for every valid i". A descendant of a node x is a node y that is on the path from node x to some leaf node.

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [4,7]
Output: 2
Explanation: The lowest common ancestor of nodes 4 and 7 is node 2.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [1]
Output: 1
Explanation: The lowest common ancestor of a single node is the node itself.

Example 3:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [7,6,2,4]
Output: 5
Explanation: The lowest common ancestor of the nodes 7, 6, 2, and 4 is node 5.
Example 4:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], nodes = [0,1,2,3,4,5,6,7,8]
Output: 3
Explanation: The lowest common ancestor of all the nodes is the root node.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-109 <= Node.val <= 109
All Node.val are unique.
All nodes[i] will exist in the tree.
All nodes[i] are distinct.
*/


// The lca will be the first node that has both left and right subtree containing some of the nodes. 
// Since it's using DFS, then the return returned while walking back will be the result. 
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        for ( auto n : nodes ) 
            if ( n == root ) 
                return root;
        bool leftcontainnode = ContainNode(root->left, nodes);
        bool rightcontainnode = ContainNode(root->right,nodes);
        if ( leftcontainnode && rightcontainnode )
            return root;
        if ( !leftcontainnode )
            return lowestCommonAncestor(root->right,nodes);
        else 
            return lowestCommonAncestor(root->left,nodes);
    }
    
    bool ContainNode( TreeNode *root,  TreeNode *node )
    {
        if ( !root )
            return false;
        if ( root == node )
            return true;
        return ContainNode( root->left, node) || ContainNode(root->right,node);
    }
    
    bool ContainNode( TreeNode *root, vector<TreeNode*> const& nodes )
    {
        for ( auto n : nodes )
            if ( ContainNode(root,n) )
                return true;
        return false;
    }
};

// using dfs to find the amount of nodes contained in the tree rooted @root. 
// the first root which has all the nodes is the lca 
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        unordered_set<TreeNode*> s;
        TreeNode *res = nullptr;
        for ( auto n : nodes )
            s.insert(n);
        dfs(root,s,&res);
        return res;
    }
    
    int dfs( TreeNode *root, unordered_set<TreeNode *> const &s, TreeNode **res )
    {
        if ( !root )
            return 0;
        int left = dfs(root->left,s,res);
        int right = dfs(root->right,s,res);
        int cur = s.count(root);
        int cur_total = left+right+cur;
        if ( *res == nullptr && cur_total == s.size() )
            *res = root;
        return cur_total;
    }
};