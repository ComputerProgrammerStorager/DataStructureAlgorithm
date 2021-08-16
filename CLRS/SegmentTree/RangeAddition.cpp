/*
You are given an integer length and an array updates where updates[i] = [startIdxi, endIdxi, inci].

You have an array arr of length length with all zeros, and you have some operation to apply on arr. In the ith operation, you should increment all the elements arr[startIdxi], arr[startIdxi + 1], ..., arr[endIdxi] by inci.

Return arr after applying all the updates.

Example 1:
Input: length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
Output: [-2,0,3,5,3]

Example 2:
Input: length = 10, updates = [[2,4,6],[5,6,8],[1,9,-4]]
Output: [0,-4,2,2,2,4,4,-4,-4,-4]
 

Constraints:

1 <= length <= 105
0 <= updates.length <= 104
0 <= startIdxi <= endIdxi < length
-1000 <= inci <= 1000
*/

// Naive solution 
// O(n*k): k the number of updates

#if 0
class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> arr(length,0);
        for ( auto op : updates )
        {
            for ( int s = op[0]; s <= op[1]; s++ )
                arr[s] += op[2];
        }
        
        return arr;
    }
};


// use partial_sum, similar to accumulative.. 
// if we add a val to idx, then all elements after it will also be incremented by val, so for each update we need to set -val for elements after the end 
class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> arr(length,0);
        for ( auto &op : updates )
        {
            arr[op[0]] += op[2];
            if ( op[1] < length - 1 )
                arr[op[1]+1] -= op[2];
        }
        
        partial_sum(arr.begin(), arr.end(),arr.begin());
        return arr;
    }
};
#endif 

#include "../Common/common_api.h"

class Solution {
    class SegTreeNode{
        public:
            int start, end;
            int info;       // the value if it's a leaf 
            int tag;    // the amount that pending propagation 
            SegTreeNode *left, *right; // children
            SegTreeNode(int s, int e):start(s),end(e),left(nullptr),right(nullptr),info(0),tag(0){}
    };
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        SegTreeNode *root = new SegTreeNode(0,length-1);
        InitSegTree(root,0,length-1);
        vector<int> res(length,0);
        for ( auto &op : updates )
        {
            SegTreeUpdateRange(root,op[0],op[1],op[2]);
        }
        
        for ( int i = 0; i < length; i++ )
        {
            res[i] = SegTreeQuerySingle(root,i);
        }
        
        return res;
    }
    
    void InitSegTree(SegTreeNode *root, int s, int e)
    {
        if ( s == e )
        {
            root->info = 0;
            return;
        }
        int m = s + (e-s)/2;
        if ( root->left == nullptr )
        {
            root->left = new SegTreeNode(s,m);
            root->right = new SegTreeNode(m+1,e);
        }
        
        InitSegTree(root->left,s,m);
        InitSegTree(root->right,m+1,e);
        root->info = 0;
    }
    
    void SegTreeUpdateRange(SegTreeNode *root, int s, int e, int val)
    {
        if ( e < root->start || s > root->end )
        {
            return;
        }
        if ( root->start == root->end )
        {
            root->info += val;
            return;
        }
        if ( s<= root->start && root->end <= e )
        {
            root->tag += val;
            return ;
        }
        
        SegTreePushDown(root);
        SegTreeUpdateRange(root->left,s,e,val);
        SegTreeUpdateRange(root->right,s,e,val);
    }
    
    void SegTreePushDown(SegTreeNode *root)
    {
        if ( root->tag )
        {
            root->left->tag += root->tag;
            root->right->tag += root->tag;
            root->tag = 0;

            if ( root->left->start == root->left->end )
            {
                root->left->info += root->left->tag;
                root->left->tag = 0;
            }
                
            if ( root->right->start == root->right->end )
            {
                root->right->info += root->right->tag;
                root->right->tag = 0;
            }       
        }
    }
    
    int SegTreeQuerySingle(SegTreeNode *root, int id)
    {
        if ( id < root->start || id > root->end )
            return INT_MAX;
        if ( root->start == id && root->end == id )
            return root->info;
        SegTreePushDown(root);
        int left_res = SegTreeQuerySingle(root->left,id);
        int right_res = SegTreeQuerySingle(root->right,id);
        if ( left_res != INT_MAX )
            return left_res;
        else 
            return right_res;
    }
};

int main()
{
    Solution s;
    int len = 5;
    vector<vector<int>> updates = {{1,3,4},{2,4,3},{0,2,-2}};
    s.getModifiedArray(len,updates);
}