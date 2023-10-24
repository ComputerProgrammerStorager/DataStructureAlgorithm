/*
Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

 

Example 1:


Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]
Example 2:


Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
 

Constraints:

The number of nodes in the list is n.
1 <= k <= n <= 5000
0 <= Node.val <= 1000
 

Follow-up: Can you solve the problem in O(1) extra memory space?
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

// Recursively handle k-nodes at a time
// We define a helper function that handles k nodes given a starting node 
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        int cnt = 0;
        ListNode* walk = head;
        while( cnt < k && walk )
        {
            cnt++;
            walk = walk->next;
        }

        if ( cnt == k )
        {
            ListNode *new_head = reverseNodes(head,k);
            head->next = reverseKGroup(walk,k);
            return new_head;
        }

        return head;
    }
private:
    ListNode* reverseNodes(ListNode* head, int k)
    {
        ListNode *new_head = nullptr, *walk = head;
        while( k > 0 )
        {
            ListNode *next = walk->next;
            walk->next = new_head;
            new_head = walk;
            walk = next;
            k--;
        }

        return new_head;
    }
};

// We can translate the above recursive to iterative 
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* new_head = nullptr;
        ListNode* walk = head;
        ListNode* ktail = nullptr;
        while( walk )
        {
            int cnt = 0;
            walk = head;
            while( cnt < k && walk )
            {
                walk = walk->next;
                cnt++;
            }
            if ( cnt == k )
            {
                ListNode *rev_head = reverseKNodes(head,k);
                if ( new_head == nullptr )
                    new_head = rev_head;
                if ( ktail )
                    ktail->next = rev_head;
                ktail = head;
                head = walk;
            }
        }
        if ( ktail )
            ktail->next = head;
        return new_head ? new_head : head;
    }
private:
    ListNode* reverseKNodes(ListNode* head, int k )
    {
        ListNode* new_head = nullptr;
        while( k > 0 )
        {
            ListNode *next = head->next;
            head->next = new_head;
            new_head = head;
            head = next;
            k--;
        }

        return new_head;
    }
};