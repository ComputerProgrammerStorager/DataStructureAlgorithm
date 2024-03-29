/*
Given a non-empty, singly linked list with head node head, return a middle node of linked list.

If there are two middle nodes, return the second middle node.

 

Example 1:

Input: [1,2,3,4,5]
Output: Node 3 from this list (Serialization: [3,4,5])
The returned node has value 3.  (The judge's serialization of this node is [3,4,5]).
Note that we returned a ListNode object ans, such that:
ans.val = 3, ans.next.val = 4, ans.next.next.val = 5, and ans.next.next.next = NULL.
Example 2:

Input: [1,2,3,4,5,6]
Output: Node 4 from this list (Serialization: [4,5,6])
Since the list has two middle nodes with values 3 and 4, we return the second one.
*/

// use slow and fast pointer 
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        if ( !head || !head->next ) 
            return head;
        ListNode *slow = head, *fast = head;
        while ( fast && fast->next )
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
};


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
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int cnt = 0;
        ListNode *walk = head;
        while(walk)
        {
            cnt++;
            walk = walk->next;
        }

        for ( int i = 0; i < cnt/2; i++ )
        {
            head = head->next;
        }

        return head;

    }
};