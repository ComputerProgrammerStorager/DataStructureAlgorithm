/*
Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.

 

Example 1:


Input: head = [1,1,2]
Output: [1,2]
Example 2:


Input: head = [1,1,2,3,3]
Output: [1,2,3]
 

Constraints:

The number of nodes in the list is in the range [0, 300].
-100 <= Node.val <= 100
The list is guaranteed to be sorted in ascending order.

*/

// check the previous value if it's the same 
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if ( !head || !head->next )
            return head;
        ListNode dummy(0), *tail = &dummy, *walk = head;
        while( walk )
        {
            ListNode* next = walk->next;
            if ( tail == &dummy || tail->val != walk->val )
            {
                tail->next = walk;
                tail = tail->next;
                tail->next = nullptr;
            }
            
            walk = next;
        }
        
        return dummy.next;
    }
};