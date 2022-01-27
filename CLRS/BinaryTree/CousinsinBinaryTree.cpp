/*
Given the root of a binary tree with unique values and the values of two different nodes of the tree x and y, return true if the nodes corresponding to the values x and y in the tree are cousins, or false otherwise.

Two nodes of a binary tree are cousins if they have the same depth with different parents.

Note that in a binary tree, the root node is at the depth 0, and children of each depth k node are at the depth k + 1.

 

Example 1:


Input: root = [1,2,3,4], x = 4, y = 3
Output: false
Example 2:


Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true
Example 3:


Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false
 

Constraints:

The number of nodes in the tree is in the range [2, 100].
1 <= Node.val <= 100
Each node has a unique value.
x != y
x and y are existent in the tree.

*/

// we can get both the parent relationship and height information via dfs. and then compare 
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        unordered_map<int,TreeNode*> path;
        unordered_map<int,int> depth;
        if ( !root )
            return false;
        path[root->val] = nullptr;
        path[root->val] = 0;
        getpath(path,depth,root,x,y);
        if (depth[x] != depth[y] || path[x] == path[y] )
            return false;
        return true;
    }
private:
    void getpath(unordered_map<int,TreeNode*> &path, unordered_map<int,int> &depth, TreeNode* root, int x, int y)
    {
        stack<TreeNode*> s;
        s.push(root);
        while( !path.count(x) || !path.count(y) )
        {
            TreeNode* cur = s.top();
            s.pop();
            if (cur->left)
            {
                path[cur->left->val] = cur;
                depth[cur->left->val] = depth[cur->val]+1;
                s.push(cur->left);
            }
            if ( cur->right )
            {
                path[cur->right->val] = cur;
                depth[cur->right->val] = depth[cur->val]+1;
                s.push(cur->right);
            }
        }
    }
};


// Natrually there is a dfs version 
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        unordered_map<int, pair<TreeNode*,int>> val2parentheight;
        dfs(val2parentheight,0,root,nullptr);
        auto px = val2parentheight[x], py = val2parentheight[y];
        if ( px.second != py.second || px.first == py.first )
            return false;
        return true;
    }
    
private:
    void dfs(unordered_map<int,pair<TreeNode*,int>> &val2parentheight, int height, TreeNode* root, TreeNode* parent )
    {
        if ( !root )
            return;
        val2parentheight[root->val] = make_pair(parent,height);
        dfs(val2parentheight,height+1,root->left,root);
        dfs(val2parentheight,height+1,root->right,root);
    }
};


// we can early terminate the search if the second depth is larger than the first depth which is recorded in a variable.
// our dfs returns a boolean to indicates if the current branch contains one of the values or if it contains both, are they on the same depth. 
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        bool is_cousin = false;
        int depth = -1;
        dfs(root,0,x,y,is_cousin,depth);
        return is_cousin;
    }
    
    bool dfs(TreeNode* root, int height, int x, int y, bool& is_cousin, int& depth)
    {
        if ( !root )
            return false;
        if ( depth != -1 && height > depth )
            return false;
        if ( root->val == x || root->val == y )
        {
            if ( depth == -1 )
                depth = height;
            return depth == height;
        }
        
        bool left = dfs(root->left, height+1, x, y, is_cousin,depth);
        bool right = dfs(root->right,height+1,x,y,is_cousin, depth);
        if ( left && right && depth != height + 1 )
            is_cousin = true;
        
        return left || right;
    }
};

// we can also use bfs to restrict only traverse to the level which first contains x, y, or both. 
// the key point is to insert a delimiter to group siblings 
// when we first encounter either x or y, it could be siblings, cousins, or only one node appearing in that level 
// so we set both siblings and cousin as true.. then if we encounter the second time on the same level, then we can determine if 
// they are siblings or cousin. If we see any siblings delimiter, we set siblings false.  
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        queue<TreeNode*> q;
        if ( !root )
            return false;
        q.push(root);
        while(q.size() > 0 )
        {
            bool siblings = false, cousin = false;
            int qsz = q.size(); 
            for ( int i = 0; i < qsz; i++ )
            {
                auto cur = q.front();
                q.pop();
                if ( cur == nullptr )
                {
                    siblings = false;
                }
                else 
                {
                    if ( cur->val == x || cur->val == y )
                    {
                        // first number appears 
                        if ( !cousin )
                        {
                            siblings = true;
                            cousin = true;
                        }
                        else 
                        {
                            // second number appears 
                            return !siblings;
                        }
                    }
                    if ( cur->left )
                        q.push(cur->left);
                    if ( cur->right )
                        q.push(cur->right);
                    q.push(nullptr);
                }
            }
            // only one node appreared in the level 
            if ( cousin )
                return false;
        }
        
        return false;
    }
};