/*
Leetcode 1803:
Given a (0-indexed) integer array nums and two integers low and high, return the number of nice pairs.

A nice pair is a pair (i, j) where 0 <= i < j < nums.length and low <= (nums[i] XOR nums[j]) <= high.

 

Example 1:

Input: nums = [1,4,2,7], low = 2, high = 6
Output: 6
Explanation: All nice pairs (i, j) are as follows:
    - (0, 1): nums[0] XOR nums[1] = 5 
    - (0, 2): nums[0] XOR nums[2] = 3
    - (0, 3): nums[0] XOR nums[3] = 6
    - (1, 2): nums[1] XOR nums[2] = 6
    - (1, 3): nums[1] XOR nums[3] = 3
    - (2, 3): nums[2] XOR nums[3] = 5
Example 2:

Input: nums = [9,8,4,2,1], low = 5, high = 14
Output: 8
Explanation: All nice pairs (i, j) are as follows:
​​​​​    - (0, 2): nums[0] XOR nums[2] = 13
    - (0, 3): nums[0] XOR nums[3] = 11
    - (0, 4): nums[0] XOR nums[4] = 8
    - (1, 2): nums[1] XOR nums[2] = 12
    - (1, 3): nums[1] XOR nums[3] = 10
    - (1, 4): nums[1] XOR nums[4] = 9
    - (2, 3): nums[2] XOR nums[3] = 6
    - (2, 4): nums[2] XOR nums[4] = 5
 

Constraints:

1 <= nums.length <= 2 * 104
1 <= nums[i] <= 2 * 104
1 <= low <= high <= 2 * 104
*/

// Naive brute force approach 
class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        int n = nums.size(), nice_pairs = 0;
        for ( int i = 0; i < n; i++ )
            for ( int j = i+1; j < n; j++ )
                if ( (nums[i] ^ nums[j]) >= low && (nums[i] ^ nums[j]) <= high )
                    nice_pairs++;
        return nice_pairs;
    }
};

// this approach uses trie that has a complexity of O(32*n)
// 1. translate the function to find how many existing numbers in the trie that xors a number (b) results in less than a given bound(threshold, c)
// 2. we know the current threshhold bit and the examined value (b), then we examine the branches of the trie and if the branch would lead less than c, then count in all the number under that branch
// 3. we maintain a count in each node to denote the count of numbers having the current value of the node at the current level
class Solution {
    class TrieNode {
        public:
        TrieNode() {
            next[0] = nullptr;
            next[1] = nullptr;
            cnt = 0;
        }
        TrieNode *next[2];
        int cnt;        // the count of number having 0/1 as its value at this node level/position
    };
public:
    int countPairs(vector<int>& nums, int low, int high) {
        return countpairsSmallerthan(nums,high+1) - countpairsSmallerthan(nums,low);
    }
    
    int countpairsSmallerthan(vector<int> const &nums, int val)
    {
        TrieNode root;
        int ret = 0;
        for ( auto num : nums )
        {
            ret += countSmallerthan(&root,num,val);
            insert(&root,num);
        }
        return ret;
    }
    
    void insert(TrieNode *root, int num)
    {
        auto node = root;
        for ( int pos = 31;  pos >= 0; pos-- )
        {
            int val = (num >>pos) & 1;
            if ( val )
            {
                if ( node->next[1] == nullptr )
                    node->next[1] = new TrieNode;
                node->next[1]->cnt++;
                node = node->next[1];
            }
            else 
            {
                if (node->next[0] == nullptr)
                    node->next[0] = new TrieNode;
                node->next[0]->cnt++;
                node = node->next[0];
                
            }
        }
    }

    int countSmallerthan(TrieNode *root, int num, int val )
    {
        int ret = 0;
        TrieNode *node = root;
        for ( int pos = 31; pos >= 0; pos-- )
        {
            int b = (num>>pos) & 1;
            int c = (val>>pos) & 1;

            if ( b && c )   // b == 1, c == 1
            {
                if ( node->next[1] )
                    ret += node->next[1]->cnt;
                node = node->next[0];
            }
            if ( b && !c )  // b == 1, c == 0
            {
                node = node->next[1];
            }
            if ( !b && c ) // b == 0, c == 1
            {
                if ( node->next[0] )
                    ret += node->next[0]->cnt;
                node = node->next[1];
            }
            if ( !b && !c ) // b == 0, c == 0
            {
                node = node->next[0];
            }
            if ( node == nullptr )
                break;
        }
        return ret;
    }
};