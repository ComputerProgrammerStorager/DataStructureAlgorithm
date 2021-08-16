/*

Given an integer array instructions, you are asked to create a sorted array from the elements in instructions. You start with an empty container nums. For each element from left to right in instructions, insert it into nums. The cost of each insertion is the minimum of the following:

The number of elements currently in nums that are strictly less than instructions[i].
The number of elements currently in nums that are strictly greater than instructions[i].
For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1) (elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].

Return the total cost to insert all elements from instructions into nums. Since the answer may be large, return it modulo 109 + 7

 

Example 1:

Input: instructions = [1,5,6,2]
Output: 1
Explanation: Begin with nums = [].
Insert 1 with cost min(0, 0) = 0, now nums = [1].
Insert 5 with cost min(1, 0) = 0, now nums = [1,5].
Insert 6 with cost min(2, 0) = 0, now nums = [1,5,6].
Insert 2 with cost min(1, 2) = 1, now nums = [1,2,5,6].
The total cost is 0 + 0 + 0 + 1 = 1.
Example 2:

Input: instructions = [1,2,3,6,5,4]
Output: 3
Explanation: Begin with nums = [].
Insert 1 with cost min(0, 0) = 0, now nums = [1].
Insert 2 with cost min(1, 0) = 0, now nums = [1,2].
Insert 3 with cost min(2, 0) = 0, now nums = [1,2,3].
Insert 6 with cost min(3, 0) = 0, now nums = [1,2,3,6].
Insert 5 with cost min(3, 1) = 1, now nums = [1,2,3,5,6].
Insert 4 with cost min(3, 2) = 2, now nums = [1,2,3,4,5,6].
The total cost is 0 + 0 + 0 + 0 + 1 + 2 = 3.
Example 3:

Input: instructions = [1,3,3,3,2,4,2,1,2]
Output: 4
Explanation: Begin with nums = [].
Insert 1 with cost min(0, 0) = 0, now nums = [1].
Insert 3 with cost min(1, 0) = 0, now nums = [1,3].
Insert 3 with cost min(1, 0) = 0, now nums = [1,3,3].
Insert 3 with cost min(1, 0) = 0, now nums = [1,3,3,3].
Insert 2 with cost min(1, 3) = 1, now nums = [1,2,3,3,3].
Insert 4 with cost min(5, 0) = 0, now nums = [1,2,3,3,3,4].
​​​​​​​Insert 2 with cost min(1, 4) = 1, now nums = [1,2,2,3,3,3,4].
​​​​​​​Insert 1 with cost min(0, 6) = 0, now nums = [1,1,2,2,3,3,3,4].
​​​​​​​Insert 2 with cost min(2, 4) = 2, now nums = [1,1,2,2,2,3,3,3,4].
The total cost is 0 + 0 + 0 + 0 + 1 + 0 + 1 + 0 + 2 = 4.
 

Constraints:

1 <= instructions.length <= 105
1 <= instructions[i] <= 105
*/

// Naive approach would be to calculate the cost of an element by searching the preceding elements
class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        const long long M = 1e9 + 7;
        int n = instructions.size(); 
        vector<int> nums;
        int total_cost = 0;
        if ( n <= 1 )
            return 0;
        for ( int i = 1; i < n; i++ )
        {
            total_cost += CalCost(instructions,i);
            total_cost %= M;
        }
        return total_cost;
    }
    
    int CalCost(vector<int>& instructions, int idx)
    {
        int lessthan = 0, greaterthan = 0;
        for ( int i = 0; i < idx; i++ )
        {
            if ( instructions[i] > instructions[idx] )
            {
                greaterthan++;
            }
            if ( instructions[i] < instructions[idx] )
            {
                lessthan++;
            }
        }
        
        return min(lessthan,greaterthan);
    }
};

// For each element, we need to find how many elements are in the range less and greater than itself, respectively, therefore it comes natual that we use Segment Tree
// First step: discretized the elments 
// Second step: construct the segment tree for each and every element (i.e., it's id)
class Solution {
public:
    int createSortedArray(vector<int>& instructions) {
        set<int> elements(instructions.begin(),instructions.end());
        unordered_map<int,int> elem2id;
        const long M = 1e9 + 7;
        int id = 0;
        for ( auto x : elements )
        {
            elem2id[x] = id++;
        }
        
        SegTreeNode *root = new SegTreeNode(0,id-1);
        SegTreeInit(root,0,id-1);
        
        long cost = 0;
        for ( auto k : instructions )
        {
            int k_id = elem2id[k];
            long lessthan = SegTreeQueryRange( root, 0, k_id -1);
            long greaterthan = SegTreeQueryRange( root, k_id+1, id-1);
            cost += min(lessthan,greaterthan);
            cost %= M;
            SegTreeUpdate(root,k_id);
        }
        
        return cost;
    }
private:
    class SegTreeNode {
    public:
        SegTreeNode(int s, int e) : start(s), end(e), info(0),left(nullptr),right(nullptr){}
        SegTreeNode *left;
        SegTreeNode *right;
        int start, end;
        int info;       // appeareance
        
    };
    
    void SegTreeInit( SegTreeNode *node, int s, int e )     // tree range is [a,b];
    {
        if ( s == e )
        {
            node->info = 0;
            return;
        }
        int mid = (s+e)/2;
        if ( node->left == nullptr)
        {
            node->left = new SegTreeNode(s,mid);
            node->right = new SegTreeNode(mid+1,e);
        }
        SegTreeInit(node->left,s,mid);
        SegTreeInit(node->right,mid+1,e);
        
        node->info = node->left->info + node->right->info;
    }
    
    long SegTreeQueryRange(SegTreeNode *root, int s, int e)
    {
        if ( s > root->end || e < root->start )
        {
            return 0;
        }
        
        if ( s <= root->start && e >= root->end )
        {
            return root->info;
        }
        
        return SegTreeQueryRange(root->left,s,e) + SegTreeQueryRange(root->right,s,e);
    }
    
    void SegTreeUpdate( SegTreeNode *root, int id, int inc = 1 )
    {
        if ( id > root->end || id < root->start )
            return;
        if ( root->start == root->end )
        {
            root->info += inc;
            return;
        }
        SegTreeUpdate(root->left,id);
        SegTreeUpdate(root->right,id);
        root->info = root->left->info + root->right->info;
    }
};