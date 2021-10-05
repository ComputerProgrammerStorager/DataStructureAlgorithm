/*
Given the root of a binary tree, return the lowest common ancestor (LCA) of two given nodes, p and q. If either node p or q does not exist in the tree, return null. All values of the nodes in the tree are unique.

According to the definition of LCA on Wikipedia: "The lowest common ancestor of two nodes p and q in a binary tree T is the lowest node that has both p and q as descendants (where we allow a node to be a descendant of itself)". A descendant of a node x is a node y that is on the path from node x to some leaf node.

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:



Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5. A node can be a descendant of itself according to the definition of LCA.
Example 3:



Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 10
Output: null
Explanation: Node 10 does not exist in the tree, so return null.
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
*/

// Search function returns the node found in the tree rooted @root, and if found is true, then the lca of p and q. 
// since p or q might not exist in the tree, so we also need to indicate whether the a node exists or not in the tree 
// for each subtree, we return a pair of node and bool, indicating which node is on the subtree and if the node is the lca 
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        auto const &[lca,found] = Search(root,p,q);
        return found ? lca : nullptr;
    }
    
    pair<TreeNode*, bool> Search(TreeNode *root, TreeNode *p, TreeNode *q )
    {
        if ( !root )
            return {nullptr,false};
        auto const &[lnode,lfound] = Search(root->left,p,q);
        auto const &[rnode,rfound] = Search(root->right,p,q);
        if ( p == root || q == root )
        {
            return {root, lnode || rnode };
        }
        if ( lnode && rnode )
        {
            return {root,true};
        }
        else if ( lnode )
        {
            return {lnode,lfound};
        } 
        else {
            return {rnode,rfound};
        }
    }
};