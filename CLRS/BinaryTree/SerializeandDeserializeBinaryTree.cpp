/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

 

Example 1:


Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [1]
Output: [1]
Example 4:

Input: root = [1,2]
Output: [1,2]
 

Constraints:

The number of nodes in the tree is in the range [0, 104].
-1000 <= Node.val <= 1000


*/

// We can store the pre-order traversal result during serialization, which can uniquely define a tree and thus can deserialize 
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if ( !root )
            return "#";
        return to_string(root->val) + "," + serialize(root->left) + "," +serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<TreeNode*> q;
        for ( int i = 0; i < data.size(); i++ )
        {
            int j = i;
            while ( j < data.size() && data[j] != ',')
            {
                j++;
            }
            string val = data.substr(i,j-i);
            if ( val == "#")
            {
                q.push_back(nullptr);
            }
            else
            {
                q.push_back(new TreeNode(stoi(val)));
            }
            i = j;
        }
        return dfs(q,0);
    }
    
    TreeNode* dfs(vector<TreeNode*> q, int cur) 
    {
        if ( !q[cur] )
            return nullptr;
        TreeNode *left = dfs(q,cur+1);
        int left_sz = GetNumofTreeNodes(left);
        TreeNode *right = dfs(q,cur+1+left_sz);
        q[cur]->left = left;
        q[cur]->right = right;
        return q[cur];
    }
    
    int GetNumofTreeNodes(TreeNode *root)
    {
        if ( !root )
            return 1;
        return GetNumofTreeNodes(root->left) + GetNumofTreeNodes(root->right) + 1;
    }
};


// We can get rid of calculating the number of nodes by poping out the processed nodes as it proceeds 
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root)
            return "#";
        return to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        queue<string> q;
        for ( int i = 0; i < data.size(); i++ )
        {
            int j = i;
            while( j < data.size() && data[j] != ',')
            {
                j++;
            }
            q.push(data.substr(i,j-i));
            i = j;
        }
        return dfs(q);
    }
    
    TreeNode *dfs(queue<string>& q)
    {
        string cur = q.front();
        q.pop();
        if ( cur == "#")
            return nullptr;
        TreeNode *root = new TreeNode(stoi(cur));
        root->left = dfs(q);
        root->right = dfs(q);
        return root;
    }
};

// we can store the nodes in level order 
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty())
        {
            TreeNode *cur = q.front();
            q.pop();
            if ( !cur )
                res +="#,";
            else
            {
                res += to_string(cur->val) + ",";
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<TreeNode*> q;
        for ( int i = 0; i < data.size(); i++ )
        {
            int j = i;
            while( j < data.size() && data[j] != ',')
            {
                j++;
            }
            string val = data.substr(i,j-i);
            if ( val == "#" )
                q.push_back(nullptr);
            else
                q.push_back(new TreeNode(stoi(val)));
            i = j;
        }
        int p = 0, left_child = 1;
        while ( left_child < q.size() )     // left_child will be always larger than parent
        {
            if ( q[p] )
            {
                q[p]->left = q[left_child];
                q[p]->right = q[left_child+1];
                left_child += 2;
            }
            
            p++;
        }
        
        return q[0];
    }
    
};