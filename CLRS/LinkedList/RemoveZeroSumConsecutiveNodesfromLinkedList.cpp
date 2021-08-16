/*
Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.

After doing so, return the head of the final linked list.  You may return any such answer.


(Note that in the examples below, all sequences are serializations of ListNode objects.)

Example 1:

Input: head = [1,2,-3,3,1]
Output: [3,1]
Note: The answer [1,2,1] would also be accepted.
Example 2:

Input: head = [1,2,3,-3,4]
Output: [1,2,4]
Example 3:

Input: head = [1,2,3,-3,-2]
Output: [1]
 

Constraints:

The given linked list will contain between 1 and 1000 nodes.
Each node in the linked list has -1000 <= node.val <= 1000.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


// idea:using prefix sum 
// if we encounter a previous same prefix sum, then need to delete the nodes between the prevsum->next, and cur. 
// using a dummy head (0) could significantly simply the handling 
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
            unordered_map<int, ListNode*> sum2node;
            ListNode dummy(0), *cur = &dummy;
            dummy.next = head;
            int prefixsum = 0;
            while (cur)
            {
                prefixsum += cur->val;
                if (sum2node.count(prefixsum))
                {
                    int sum = prefixsum;
                    ListNode *del = sum2node[prefixsum]->next;
                    while(del != cur)
                    {
                        sum += del->val;
                        sum2node.erase(sum);
                        del = del->next;
                    }
                    
                    sum2node[prefixsum]->next = cur->next;
                }
                else 
                {
                    sum2node[prefixsum] = cur;
                }
                
                cur = cur->next;
            }
        
            return dummy.next;
        }
};