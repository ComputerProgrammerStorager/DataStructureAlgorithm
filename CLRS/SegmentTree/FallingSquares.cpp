/*
On an infinite number line (x-axis), we drop given squares in the order they are given.

The i-th square dropped (positions[i] = (left, side_length)) is a square with the left-most point being positions[i][0] and sidelength positions[i][1].

The square is dropped with the bottom edge parallel to the number line, and from a higher height than all currently landed squares. We wait for each square to stick before dropping the next.

The squares are infinitely sticky on their bottom edge, and will remain fixed to any positive length surface they touch (either the number line or another square). Squares dropped adjacent to each other will not stick together prematurely.

 
Return a list ans of heights. Each height ans[i] represents the current highest height of any square we have dropped, after dropping squares represented by positions[0], positions[1], ..., positions[i].

Example 1:

Input: [[1, 2], [2, 3], [6, 1]]
Output: [2, 5, 5]
Explanation:
After the first drop of positions[0] = [1, 2]: _aa _aa ------- The maximum height of any square is 2.

After the second drop of positions[1] = [2, 3]: __aaa __aaa __aaa _aa__ _aa__ -------------- The maximum height of any square is 5. The larger square stays on top of the smaller square despite where its center of gravity is, because squares are infinitely sticky on their bottom edge.

After the third drop of positions[1] = [6, 1]: __aaa __aaa __aaa _aa _aa___a -------------- The maximum height of any square is still 5. Thus, we return an answer of [2, 5, 5].

 

 
Example 2:

Input: [[100, 100], [200, 100]]
Output: [100, 100]
Explanation: Adjacent squares don't get stuck prematurely - only their bottom edge can stick to surfaces.
 

Note:

1 <= positions.length <= 1000.
1 <= positions[i][0] <= 10^8.
1 <= positions[i][1] <= 10^6.
*/

#if 0 
// Idea: use segment tree 
// each falling square would cause an interval's height to increase by sidelength
class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        set<int> points;
        unordered_map<int,int> pos2id;
        vector<int> ans;
        int id = 0;
        for (auto &sq : positions )
        {
            points.insert(sq[0]);
            points.insert(sq[0]+sq[1]);
        }
        for ( auto p : points )
        {
            pos2id[p] = id++;
        }
        
        SegTreeNode *root = new SegTreeNode(0,id-1);
        SegTreeInit(root,0,id-1);
        
        int maxHeight = 0;
        for ( auto &sq : positions )
        {
            int x_id = pos2id[sq[0]];
            int y_id = pos2id[sq[0]+sq[1]];
            int land_height = SegTreeQueryRange(root,x_id,y_id-1);
            SegTreeUpdateRange(root,x_id,y_id-1,land_height+sq[1]);
            maxHeight = max(maxHeight,land_height+sq[1]);
            ans.push_back(maxHeight);
        }
        
        return ans;
    }
private:
    class SegTreeNode{
    public:
        SegTreeNode *left, *right;
        int start, end;
        int info;           // the height of the range
        bool lazytag;        // lazy update
        SegTreeNode(int s, int e) : left(nullptr), right(nullptr), start(s), end(e), info(0), lazytag(0) {}
    };
    
    void SegTreeInit(SegTreeNode *root, int s, int e )
    {
        if ( s == e )
        {
           // root->info = 0;
            return;
        }
        int mid = (s+e)/2;
        if ( root->left == nullptr )
        {
            root->left = new SegTreeNode(s,mid);
            root->right = new SegTreeNode(mid+1,e);
        }
        
        SegTreeInit(root->left,s,mid);
        SegTreeInit(root->right,mid+1,e);
        //root->info = 0;
    }
    
    void PushDown(SegTreeNode *node)
    {
        if ( node->lazytag )
        {
            node->left->info = node->info;
            node->right->info = node->info;
            node->left->lazytag = true;
            node->right->lazytag = true;
            node->lazytag = false;
        }
    }
    
    int SegTreeQueryRange(SegTreeNode *root, int s, int e)
    {
        if ( s > root->end || e < root->start )
            return 0;
        if ( s <= root->start && e >= root->end )
        {
            return root->info;
        }
        
        PushDown(root);
        return max(SegTreeQueryRange(root->left,s,e),SegTreeQueryRange(root->right,s,e));
    }
    
    void SegTreeUpdateRange(SegTreeNode *root, int s, int e, int val)
    {
        if ( e < root->start || s > root->end )
        {
            return;
        }
        if ( s <= root->start && e >= root->end )
        {
            root->info = val;
            root->lazytag = true;
            return ;
        }
        PushDown(root);
        SegTreeUpdateRange(root->left,s,e,val);
        SegTreeUpdateRange(root->right,s,e,val);
        root->info = max(root->left->info,root->right->info);
    }
};
#endif 

#include "../Common/common_api.h"

// We can also use map struct to denote the x-xis and it's height relationship
// It represent the height of the interval starting from [key, next_key)

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        set<int> points;
        map<int,int> pt2ht;     // left close and right open
        pt2ht[0] = 0;
        pt2ht[INT_MAX] = 0;
        vector<int> ans;
        for ( auto pos : positions )
        {
            points.insert(pos[0]);
            points.insert(pos[0]+pos[1]);
        }
        
        for ( auto pt : points )
        {
            pt2ht[pt] = 0;
        }
        
        for ( auto sq : positions) 
        {
            auto it_x = pt2ht.lower_bound(sq[0]);
            auto it_y = pt2ht.upper_bound(sq[0]+sq[1]-1);
            int maxH = 0;
            int temp = prev(it_y,1)->second;
            auto start_it = it_x->first == sq[0] ? it_x : prev(it_x,1);
            while ( start_it != it_y )
            {
                maxH = max(maxH,start_it->second);
                start_it = next(start_it,1);
            }
            ans.push_back(ans.empty() ? maxH+sq[1] : max(ans.back(),maxH+sq[1]));
            if ( it_x != it_y )
            {
                pt2ht.erase(it_x,it_y);
            }
            
            pt2ht[sq[0]] = maxH + sq[1];
            pt2ht[sq[0]+sq[1]] = temp;
        }
    
        return ans;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> positions = {{100,100},{200,100}};
    s.fallingSquares(positions);
}