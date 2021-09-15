/*
Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

 

Example 1:


Input: p = [1,2,3], q = [1,2,3]
Output: true
Example 2:


Input: p = [1,2], q = [1,null,2]
Output: false
Example 3:


Input: p = [1,2,1], q = [1,1,2]
Output: false
 

Constraints:

The number of nodes in both trees is in the range [0, 100].
-104 <= Node.val <= 104


*/

// DFS checking: the node values are the same, the left subtrees are the same and the right subtrees are the same
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if ( !p && !q )
            return true;
        if ( !p || !q )
            return false;
        return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right,q->right);
    }
};

// can also use iterative method via a queue
class Solution {
public:
    bool isSameTree(TreeNode* s, TreeNode* t) {
        queue<pair<TreeNode*, TreeNode*>> q;
        q.push({s,t});
        while(!q.empty())
        {
            auto cur = q.front();
            q.pop();
            if ( !checkPair(cur.first,cur.second) )
                return false;
            if ( cur.first )
            {
                q.push({cur.first->left,cur.second->left});
                q.push({cur.first->right,cur.second->right});
            }
        }
        
        return true;
    }
    
    bool checkPair(TreeNode*p, TreeNode* q)
    {
        if ( !p && !q )
            return true;
        if ( !p || !q)
            return false;
        if ( p->val != q->val ) 
            return false;
        return true;
    }
};