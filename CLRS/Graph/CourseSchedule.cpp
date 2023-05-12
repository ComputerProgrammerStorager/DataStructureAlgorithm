/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
 

Constraints:

1 <= numCourses <= 2000
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
All the pairs prerequisites[i] are unique.
*/

// Use topological sort
// start with all nodes having zero indegrees and reduce the degree of the nodes which have incoming nodes of zero degrees 
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g(numCourses);
        queue<int> q; 
        vector<int> indegree(numCourses,0);

        for ( auto e : prerequisites )
        {
            indegree[e[0]]++;
            g[e[1]].push_back(e[0]);
        }

        for ( int i = 0; i < numCourses; i++ )
        {
            if ( indegree[i] == 0 )
                q.push(i);
        }

        while( !q.empty())
        {
            int  cur = q.front();
            q.pop();
            for ( auto n : g[cur] )
            {
                if ( --indegree[n] == 0 )
                    q.push(n);
            }
        }

        return accumulate(indegree.begin(),indegree.end(),0) == 0;
    }
};

// Recursive DFS: if we know the result of downstream node, then we quickly know the current node state
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g(numCourses);
        vector<int> checked(numCourses);
        vector<int> path(numCourses);
        for ( auto e : prerequisites )
        {
            g[e[1]].push_back(e[0]);
        }

        for ( int i = 0; i < numCourses; i++ )
            if ( isCyclic(g,i,checked,path))
                return false;
        return true;
    }

    bool isCyclic(vector<vector<int>> const& g, int cur, vector<int> &checked, vector<int> &path)
    {
        if ( checked[cur] )
            return false;
        if ( path[cur] )
            return true;
        path[cur] = true;
        bool ret = false;
        for ( auto n : g[cur] )
        {
            ret = isCyclic(g,n,checked,path);
            if ( ret )
                break;
        }

        path[cur] = false;
        checked[cur] = true;
        return ret;
    }
};