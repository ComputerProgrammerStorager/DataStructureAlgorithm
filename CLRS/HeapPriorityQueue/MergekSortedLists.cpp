/*
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

 

Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
Example 2:

Input: lists = []
Output: []
Example 3:

Input: lists = [[]]
Output: []
 

Constraints:

k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] is sorted in ascending order.
The sum of lists[i].length won't exceed 10^4.

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

// use priority queue heap 
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        #if 1
        struct nodecmp {
            bool operator()(ListNode *l, ListNode *r) {
                return l->val >= r->val;
            }
        };
        priority_queue<ListNode*,vector<ListNode*>, nodecmp> pq;
        #endif 
        
        #if 0 
        auto cmp = [](ListNode *a, ListNode *b ){
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        #endif 
        
        ListNode dummy, *tail = &dummy;
        int n = lists.size();
        
        for ( int i = 0; i < n; i++ )
        {
            if ( lists[i] )
                pq.push(lists[i]);
        }
        
        while( !pq.empty() )
        {
            auto t = pq.top();
            pq.pop();
            if ( t->next )
                pq.push(t->next);
            tail->next = t;
            tail = tail->next;
        }
        
        tail->next = nullptr;
        return dummy.next;
    }
};

// divide and conquer and finally return lists[0]
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if ( n == 0 )
            return nullptr;
        while ( n > 1 )
        {
            int mid = (n+1)/2;
            for ( int i = 0; i < n/2; i++ )
            {
                lists[i] = Merge2Lists(lists[i],lists[i+mid]);
            }
            n = mid;
        }
        return lists[0];
    }
    
    ListNode *Merge2Lists(ListNode* l1, ListNode* l2)
    {
        if ( !l1 )
            return l2;
        if ( !l2 )
            return l1;
        ListNode dummy, *tail = &dummy;
        while ( l1 && l2 )
        {
            if ( l1->val <= l2->val )
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        
        if ( l1 )
            tail->next = l1;
        if ( l2 )
            tail->next = l2;
        return dummy.next;
    }
};