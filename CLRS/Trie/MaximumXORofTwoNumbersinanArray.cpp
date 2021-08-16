/*
Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 ≤ i ≤ j < n.

Follow up: Could you do this in O(n) runtime?

 

Example 1:

Input: nums = [3,10,5,25,2,8]
Output: 28
Explanation: The maximum result is 5 XOR 25 = 28.
Example 2:

Input: nums = [0]
Output: 0
Example 3:

Input: nums = [2,4]
Output: 6
Example 4:

Input: nums = [8,10,2]
Output: 10
Example 5:

Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
Output: 127
 

Constraints:

1 <= nums.length <= 2 * 104
0 <= nums[i] <= 231 - 1
*/

// Naive brute force O(n^2)
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int xor_sum = 0;
        for ( int i = 0; i < nums.size(); i++ )
            for ( int j = i+1; j < nums.size(); j++ )
                if ( (nums[j] ^ nums[i]) > xor_sum )
                    xor_sum = (nums[j] ^ nums[i]);
        return xor_sum;
    }
};


// We can also use trie to bring the complexity down to O(n)
class Solution {
    class TrieNode {
        public:  
            TrieNode() { 
                next[0] = nullptr;
                next[1] = nullptr;
                cnt = 0;
            }
            TrieNode *next[2];
            int cnt;
        };
public:
    int findMaximumXOR(vector<int>& nums) {
        
        int mx_sum = 0;
        TrieNode root;
        for ( auto num : nums )
        {
            updateMaxXOR(&root,num,mx_sum);
            insertNode(&root,num);
        }
        
        return mx_sum;
        
    }
    
    void insertNode( TrieNode *root, int num )
    {
        root->cnt++;
        TrieNode *node = root;
        for ( int pos = 31; pos >= 0; pos-- )
        {
            int val = (num>>pos) & 1;
            if ( node->next[val] == nullptr )
            {
                node->next[val] = new TrieNode;
            }
            node = node->next[val];
        }
    }
    
    void updateMaxXOR( TrieNode *root, int cur, int &mx_sum)
    {
        TrieNode *node = root;
        int mx_new = 0;
        if ( root->cnt == 0 )
            return;
        for ( int pos = 31; pos >= 0; pos-- )
        {
            int b = (cur >> pos) & 1;
            if ( node->next[!b] ) 
            {
                mx_new |= (1<<pos);
                node = node->next[!b];
            }
            else {
                node = node->next[b];
            }
        }
        
        if ( mx_new > mx_sum )
            mx_sum = mx_new;
    }
};