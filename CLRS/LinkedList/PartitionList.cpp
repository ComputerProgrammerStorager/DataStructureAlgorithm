/*
Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

 

Example 1:


Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]
Example 2:

Input: head = [2,1], x = 2
Output: [1,2]
 

Constraints:

The number of nodes in the list is in the range [0, 200].
-100 <= Node.val <= 100
-200 <= x <= 200
*/

// split them separately to two different sublist, and then splice them 
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode dummy_less(0), *tail_less = &dummy_less, dummy_ge(0), *tail_ge = &dummy_ge;
        while( head )
        {
            ListNode *cur = head;
            head = head->next;
            cur->next = nullptr;
            if ( cur->val < x )
            {
                tail_less->next = cur;
                tail_less = cur;
            }
            else
            {
                tail_ge->next = cur;
                tail_ge = cur;
            }
        }
        
        if ( dummy_ge.next != nullptr )
            tail_less->next = dummy_ge.next;
        return dummy_less.next;
    }
};