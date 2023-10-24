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
0 <= k <= 104
0 <= lists[i].length <= 500
-104 <= lists[i][j] <= 104
lists[i] is sorted in ascending order.
The sum of lists[i].length will not exceed 104.
*/

// Priority queue method is straightforward 
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode dummy(0), *tail = &dummy;
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val >= b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        for ( const auto& l : lists )
            if ( l )
                pq.push(l);
        while(pq.size())
        {
            auto cur = pq.top();
            pq.pop();
            auto next = cur->next;
            tail->next = cur;
            tail = tail->next;
            if ( next )
                pq.push(next);
        }

        return dummy.next;
    }
};


// Divide and conquer 
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return partition(lists,0,lists.size()-1);
    }
private:
    ListNode* partition(vector<ListNode*>& lists, int s, int e)
    {
        if ( s == e )
            return lists[s];
        if ( s < e )
        {
            int m = (s+e)/2;
            ListNode *l1 = partition(lists,s,m);
            ListNode *l2 = partition(lists,m+1,e);
            return merge2lists(l1,l2);
        }
        return nullptr;
    }
    ListNode *merge2lists(ListNode* l1, ListNode*l2)
    {
        ListNode dummy(0), *tail = &dummy;
        while(l1 && l2)
        {
            if ( l1->val < l2->val )
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else {
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