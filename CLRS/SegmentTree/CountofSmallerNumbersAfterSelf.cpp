/*
You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example 1:

Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Example 2:

Input: nums = [-1]
Output: [0]
Example 3:

Input: nums = [-1,-1]
Output: [0,0]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
*/

#if 0
// Naive solution 
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n,0);
        if ( n < 2 ) 
            return res;
        for ( int i = n-2; i >=0; i-- )
        {
            int count = 0;
            for ( int j = n-1; j > i; j--) 
            {
                if ( nums[j] < nums[i] )
                    count++;
            }
            res[i] = count;
        }
        
        return res;
    }
};
#endif


// We could also use Segment tree
#include "../Common/common_api.h"

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        set<int> s(nums.begin(),nums.end());
        int n = nums.size();
        vector<int> res(n,0);
        unordered_map<int,int> num2id;
        
        int id = 0;
        for ( auto it : s )
            num2id[it] = id++;
        SegTreeNode *root = new SegTreeNode(0,id-1);
        InitSegTree(root,0,id-1);
        id = num2id[nums[n-1]];
        UpdateSegTree(root,id);
        for ( int i = n-2; i >= 0; i-- )
        {
            id = num2id[nums[i]];
            res[i] = QuerySegTree(root,0,id-1);
            UpdateSegTree(root,id);
        }
        
        return res;
    }
private:
    class SegTreeNode{
    public:
        SegTreeNode(int s, int e):start(s),end(e),info(0),left(nullptr),right(nullptr){}
        int start, end;
        SegTreeNode *left;
        SegTreeNode *right;
        int info;   // the occurrence 
    };
    
    void InitSegTree( SegTreeNode *node, int s, int e)
    {
        if( s == e)
        {
            node->info = 0;
            return;
        }
        int mid = (s+e)/2;
        if ( node->left == nullptr )
        {
            node->left = new SegTreeNode(s,mid);
            node->right = new SegTreeNode(mid+1,e);
        }
        
        InitSegTree(node->left,s,mid);
        InitSegTree(node->right,mid+1,e);
        node->info = 0;
    }
    
    void UpdateSegTree(SegTreeNode *root, int id, int inc = 1)
    {
        if ( id < root->start || id > root->end )
            return ;
        if ( root->start == root->end )
        {
            root->info += inc;
            return;
        }
        UpdateSegTree(root->left,id);
        UpdateSegTree(root->right,id);
        root->info = root->left->info + root->right->info;
    }
    
    int QuerySegTree(SegTreeNode *root, int s, int e)
    {
        if (s > root->end || e < root->start)
            return 0;
        if ( s <= root->start && e >= root->end )
        {
            return root->info;
        }
        return QuerySegTree(root->left,s,e) + QuerySegTree(root->right,s,e);
    }
};

int main()
{
    vector<int> data = {-1,-1};
    Solution s;
    s.countSmaller(data);
}