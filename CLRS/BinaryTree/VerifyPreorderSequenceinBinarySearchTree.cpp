/*
Given an array of unique integers preorder, return true if it is the correct preorder traversal sequence of a binary search tree.

 

Example 1:


Input: preorder = [5,2,1,3,6]
Output: true
Example 2:

Input: preorder = [5,2,6,1,3]
Output: false
 

Constraints:

1 <= preorder.length <= 104
1 <= preorder[i] <= 104
All the elements of preorder are unique.
 

Follow up: Could you do it using only constant space complexity?

*/

// Since we are given the prorder sequence, then we know the first element is the tree root, and the remaining are left and right substree, 
// meaning the first bulk are all less than the root and the second bulk are all larger than the root. 
// Then we recursively check the left and right subtree. 
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        return dfs(preorder,0,preorder.size()-1);
    }
    
    bool dfs(vector<int> const &preorder, int s, int e )
    {
        if ( e - s <= 1 )
            return true;
        int root = preorder[s];
        int i = s+1;
        while( i <= e && preorder[i] < root)
            i++;
        for ( int j = i; j <= e; j++ )
            if ( preorder[j] <= root )
                return false;
        return dfs(preorder,s+1,i-1) && dfs(preorder,i,e);
    }
};