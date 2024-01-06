/*
Given a root of an N-ary tree, you need to compute the length of the diameter of the tree.

The diameter of an N-ary tree is the length of the longest path between any two nodes in the tree. This path may or may not pass through the root.

(Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value.)

 

Example 1:



Input: root = [1,null,3,2,4,null,5,6]
Output: 3
Explanation: Diameter is shown in red color.
Example 2:



Input: root = [1,null,2,null,3,4,null,5,null,6]
Output: 4
Example 3:



Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: 7
 

Constraints:

The depth of the n-ary tree is less than or equal to 1000.
The total number of nodes is between [1, 104].
*/


/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    int diameter(Node* root) {
        int res = 0;
        dfs(root,res);
        return res;
    }

    int dfs(Node *root, int& res) {
        if ( !root )
            return -1;
        if ( root->children.size() == 0 ) {
            return 0;
        }

        int max1 = 0, max2 = 0;
        for ( auto child : root->children ) {
            int parent_h = dfs(child,res) + 1;
            if ( parent_h > max1 ) {
                max2 = max1;
                max1 = parent_h;
            } else if ( parent_h > max2 ) {
                max2 = parent_h;
            }

            res = max(res,max1+max2);
        }

        return max1;
    }
};

// based on depth
class Solution {
public:
    int diameter(Node* root) {
        int res = 0;
        if ( !root )
            return 0;
        dfs(root,res,0);
        return res;
    }

    int dfs(Node* root, int& res, int curdepth) {
        if ( root->children.size() == 0 ) 
            return curdepth;
        int max1 = 0, max2 = 0;
        for ( auto child : root->children ) {
            int depth = dfs(child, res, curdepth+1);
            if ( depth > max1 ) { 
                max2 = max1;
                max1 = depth;
            } else if ( depth > max2 ) { 
                max2 = depth;
            }

            res = max(res,max1+max2-2*curdepth);
        }

        return max1;
    }
};