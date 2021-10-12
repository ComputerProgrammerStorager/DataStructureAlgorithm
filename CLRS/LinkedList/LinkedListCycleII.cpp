/*
Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed). It is -1 if there is no cycle. Note that pos is not passed as a parameter.

Do not modify the linked list.

 

Example 1:


Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.
Example 2:


Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.
Example 3:


Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.
 

Constraints:

The number of the nodes in the list is in the range [0, 104].
-105 <= Node.val <= 105
pos is -1 or a valid index in the linked-list.
 

Follow up: Can you solve it using O(1) (i.e. constant) memory?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// Maintain the nodes that have been visited so far
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        set<ListNode*> visited;
        while( head )
        {
            if ( visited.count(head) ) 
                return head;
            visited.insert(head);
            head = head->next;
        }
        
        return nullptr;
    }
};

// find the meetnode (if cycle exists) and then reset a node from, then when they meet, the node is then entrance of the cycle 
// Proof: assume the meetnode divides the cycle into a and b lengths, and cycle lenght c = a + b. Note the length of acyclic part is L
// Then we have 2*(L+a) = (L+nc+a)  n > 0. 
// This means: L + a = nC, meaning L = nc - a (n > 0).. We know b = c - a, therefore if we have two nodes start from the meetnode and head, 
// respectively, and walk both one node at a time, then they will meet at the entrance of the cycle.
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* meetnode = nullptr;
        ListNode *fast = head, *slow = head;
        while( slow && fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if ( slow == fast )
            {
                meetnode = slow;
                break;
            }
        }
        
        if ( meetnode )
        {
            fast = head;
            while( fast != meetnode )
            {
                fast = fast->next;
                meetnode = meetnode->next;
            }
        }
        return meetnode;
    }
};