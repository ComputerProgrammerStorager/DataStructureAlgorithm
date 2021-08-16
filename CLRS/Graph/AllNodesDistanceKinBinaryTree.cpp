/*
We are given a binary tree (with root node root), a target node, and an integer value K.

Return a list of the values of all nodes that have a distance K from the target node.  The answer can be returned in any order.

 

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2

Output: [7,4,1]

Explanation: 
The nodes that are a distance 2 from the target node (with value 5)
have values 7, 4, and 1.



Note that the inputs "root" and "target" are actually TreeNodes.
The descriptions of the inputs above are just serializations of these objects.
 

Note:

The given tree is non-empty.
Each node in the tree has unique values 0 <= node.val <= 500.
The target node is a node in the tree.
0 <= K <= 1000.
*/

// first we use dfs to find all the parent-child relationship of all nodes 
// then use bfs to find the level of k distance
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        vector<int> res;
        unordered_map<TreeNode*, TreeNode*> parent;
        unordered_map<TreeNode*, bool> visited;
        dfs_find_parent(root,parent);
        queue<TreeNode*> q;
        q.push(target);
        visited[target] = true;
        int distance = 0;
        while(!q.empty() && distance < K )
        {
            queue<TreeNode*> tmp;
            while( !q.empty() )
            {
                TreeNode *first = q.front();
                q.pop();
                if ( first->left && !visited[first->left] )
                {
                    tmp.push(first->left);
                    visited[first->left] = true;
                }
                    
                if ( first->right && !visited[first->right] )
                {
                    tmp.push(first->right);
                    visited[first->right] = true;
                }
                    
                if ( parent[first] && !visited[parent[first]] )
                {
                    tmp.push(parent[first]);
                    visited[parent[first]] = true;
                }
                    
            }
            q = tmp;
            distance++;
        }
        
        while ( !q.empty() )
        {
            res.push_back(q.front()->val);
            q.pop();
        }
        
        return res;
    }
    
    void dfs_find_parent(TreeNode* root, unordered_map<TreeNode*,TreeNode*> &parent)
    {
        if ( root == nullptr )
            return ;
        if ( root->left )
        {
            parent[root->left] = root;
            dfs_find_parent(root->left,parent);
        }
        if ( root->right )
        {
            parent[root->right] = root;
            dfs_find_parent(root->right,parent);
        }
    }
};


// In this method, we only use DFS to explore the tree. 
// The helper function will return the distance from the current node to target, and return:
// -1: if the current node is nullptr
//  1: if the current node is target, meaning it's parent has distance 1 to the target. We also need to search it downward to find its children for starting from zero level
// its distance of left and right substree:
// if the target is in the left subtree and the left subtree returns a value of leftval, then if leftval is equal to the said height, then add the current val. Otherwise, we search right subtree with incremented level by one and also returns leftval+1 to it's parent
// if the targe is in the right subtree and the right subtree returns a value of rightval, then if rightval is equal to thesaid height, then add the val. Otherwise, we search left subtree with incremented level by one and also returns rightval + 1 to its' parent
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        vector<int> res;
        helper(root,res,K,target);
        return res;
    }
    
    int helper(TreeNode *node, vector<int> &res, int K, TreeNode* target)        // this function returns the distance from node to target to it's caller along the recursive path
    {
        if ( node == nullptr )
            return -1;
        if ( node == target )
        {
            searchDownward(node,K,res,0);
            return 1;
        }
        
        int left = helper(node->left,res,K,target);
        if ( left != -1 )
        {
            if ( left == K )
            {
                res.push_back(node->val);
            }
            else 
            {
                searchDownward(node->right,K,res,left+1);
            }
            
            return left + 1;
        }
        
        int right = helper(node->right,res,K,target);
        if ( right != -1 )
        {
            if ( right == K )
            {
                res.push_back(node->val);
            }
            else 
            {
                searchDownward(node->left,K,res,right+1);
            }
            
            return right+1;
        }
        
        return -1;
    }
    
    void searchDownward(TreeNode* node, int K, vector<int> &res, int cur_level)
    {
        if ( node == nullptr )
            return;
        if ( K == cur_level )
        {
            res.push_back(node->val);
        }
        else {
            searchDownward(node->left,K,res,cur_level+1);
            searchDownward(node->right,K,res,cur_level+1);
        }
    }
};