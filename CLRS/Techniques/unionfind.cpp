/*
Notes: 
1. Union find is a method to use test membership relationship and it's typically used in identify components in graph algorithm, e.g., in the MST Kruskal algorithm, and detecting cycles. 
2. Union find can be implemented in a number of forms, including graph representation, array representation, and linked list. This implementation adopt the array representation.
3. The key component is a parent arrray which remembers the root of the subtree or the component that the node belongs to. In this implementation, if the parent is negative, it indicates that 
   the node itself is a root and the absolute value of parent denotes the number of nodes currently in the subtree. 
4. Union find supports two operations namely find_root and union_roots, which respectively finds the root node of a given node and union two given root nodes. Note: when do a union, we link the smaller subtree 
   to the bigger subtree to ensure the worst case being lgN.
5. There is a variation called callapsing union find, which link a node to its root whenever we find a root for a node. 
*/ 

constexpr static int NUM_NODES = 10001;
class union_find {
public:
    int Parent[NUM_NODES];
    union_find() {
        for ( int i = 0; i < NUM_NODES; i++ )
            Parent[i] = -1;
    }
};

int find_root( union_find &uf, int node )
{
    while ( uf.Parent[node] > 0 )
    {
        node = uf.Parent[node];
    }
    
    return node;
}

void union_nodes( union_find &uf, int source_root, int target_root) 
{
    if ( uf.Parent[source_root] > uf.Parent[target_root] )
    {
        uf.Parent[target_root] += uf.Parent[source_root];
        uf.Parent[source_root] = target_root;
    }
    else
    {
        uf.Parent[source_root] += uf.Parent[target_root];
        uf.Parent[target_root] = source_root;
    }
}