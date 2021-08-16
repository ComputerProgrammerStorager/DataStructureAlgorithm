/*
*/

#include "../Common/common_api.h"
#include "tree.h"

// walk up one path to find all parents and then walk up the other node and find the first existing parent 
class Solution {
public:
    NodeWithParent* lowestCommonAncestor(NodeWithParent* p, NodeWithParent * q) {
        set<Node*> p_path;
        Node * lca = nullptr;
        while ( p )
        {
            p_path.insert(p);
            p = p->parent;
        }
        while(q)
        {
            if ( p_path.count(q) )
            {
                lca = q;
                break;
            }
            q = q->parent;
        }
        return lca;
    }
};


// we can just loop one time and return early 
// O(n) space
class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        unordered_set<Node *> path;
        Node *lca = nullptr;
        while ( p || q )
        {
            if ( p ) 
            {
                if ( path.count(p)) {
                    lca = p;
                    break;
                }
                path.insert(p);
                p = p->parent;
            }
            
            if ( q )
            {
                if ( path.count(q) )
                {
                    lca = q;
                    break;
                }
                path.insert(q);
                q = q->parent;
            }
        }
        
        return lca;
    }
};

// O(1) space: let the two walk up at the same height, then them must meet at their LCA
class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        int d1 = 0, d2 = 0;
        Node *tmp1 = p, *tmp2 = q;
        while ( tmp1 )
        {
            if ( tmp1 == q )
                return q;
            d1++;
            tmp1 = tmp1->parent;
        }
        
        while (tmp2)
        {
            if ( tmp2 == p )
                return p;
            d2++;
            tmp2 = tmp2->parent;
        }
        
        while( d1 > d2)
        {
            p = p->parent;
            d1--;
        }
        while ( d2 > d1 )
        {
            q = q->parent;
            d2--;
        }
        while ( p != q )
        {
            p = p->parent;
            q = q->parent;
        }
        
        return p;
    }
};

