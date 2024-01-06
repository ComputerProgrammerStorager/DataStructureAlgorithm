/*
In an infinite binary tree where every node has two children, the nodes are labelled in row order.

In the odd numbered rows (ie., the first, third, fifth,...), the labelling is left to right, while in the even numbered rows (second, fourth, sixth,...), the labelling is right to left.



Given the label of a node in this tree, return the labels in the path from the root of the tree to the node with that label.

 

Example 1:

Input: label = 14
Output: [1,3,4,14]
Example 2:

Input: label = 26
Output: [1,2,6,10,26]
 

Constraints:

1 <= label <= 10^6
*/

// key insign are:
// at any level i (i >= 1), the nodes label range is [2^(i-1),2^i-1]. And if a label x is swapped, the swapped position is 2^(i-1) + 2^i - 1 - x. 
// for any parent p, its two children are swapped. Therefore, if we know a children label, the way to get its parent in zigzaged binary tree is obtain its swapped position first, and then divided it by 2.
class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
        vector<int> res;
        int level = 0, tmp = label;
        while(tmp)
        {
            level++;
            tmp >>= 1;
        }

        while( level > 0 )
        {
            res.insert(res.begin(),label);
            label = (1<<(level-1)) + (1<<level) - 1 - label;
            label /= 2;
            level--;
        }

        return res;
    }
};