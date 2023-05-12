/*
You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array relations where relations[i] = [prevCoursei, nextCoursei], representing a prerequisite relationship between course prevCoursei and course nextCoursei: course prevCoursei has to be taken before course nextCoursei.

In one semester, you can take any number of courses as long as you have taken all the prerequisites in the previous semester for the courses you are taking.

Return the minimum number of semesters needed to take all courses. If there is no way to take all the courses, return -1.

 

Example 1:


Input: n = 3, relations = [[1,3],[2,3]]
Output: 2
Explanation: The figure above represents the given graph.
In the first semester, you can take courses 1 and 2.
In the second semester, you can take course 3.
Example 2:


Input: n = 3, relations = [[1,2],[2,3],[3,1]]
Output: -1
Explanation: No course can be studied because they are prerequisites of each other.
 

Constraints:

1 <= n <= 5000
1 <= relations.length <= 5000
relations[i].length == 2
1 <= prevCoursei, nextCoursei <= n
prevCoursei != nextCoursei
All the pairs [prevCoursei, nextCoursei] are unique.
*/

// Take courses which have zero indegrees (no prerequisites) first... while remembering which courses have already learned 
class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        if ( n == 0 || relations.size() == 0 )
            return 0;
        set<int> learned;
        queue<int> q;
        vector<int> indegree(n+1);
        vector<vector<int>> graph(n+1);
        int res = 0;
        for (auto it : relations)
        {
            indegree[it[1]]++;
            graph[it[0]].push_back(it[1]);
        }

        for ( int i = 1; i <= n; i++ )
        {
            if ( indegree[i] == 0 )
            {
                learned.insert(i);
                q.push(i);
            }
        }

        while( !q.empty() )
        {
            int cur_sz = q.size();
            for ( int i = 0; i < cur_sz; i++ )
            {
                int cur = q.front();
                q.pop();
                for (auto next : graph[cur])
                {
                    if ( --indegree[next] == 0 )
                    {
                        q.push(next);
                        learned.insert(next);
                    }
                }
            }

            res++;
        }

        return learned.size() == n ? res : -1;
    }
};


// If a directed graph has cycles, then there is no way to sort in levels (i.e., semesters)
// if there is no cycle, then the longest path is the number of minimum semester 
// Thus, we need to first detect if a directed graph has a cycle or not. 
// Then we calculate the longest path of a directed graph 

class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<vector<int>> graph(n+1);
        for ( auto it : relations )
            graph[it[0]].push_back(it[1]);
        vector<int> visited(n+1,0);
        for ( int i = 1; i <= n; i++ )
            if ( dfsCheckcycle(i,graph,visited) == -1 )
                return -1;
        vector<int> visited_length(n+1,0);
        int res = 1;
        for ( int i = 1; i <= n; i++ )
        {
            int len = longestpath(i,graph,visited_length);
            res = max(res,len);
        }

        return res;
    }
private: 
    // use dfs to check cycle in a direct graph
    // we use visited[i] to denote the state of a node: -1 being visited, 1 visited, 0 unvisited 
    // for each node, we put it in -1 (being visited) state and dfs its neighbors, if during the process we encounter any node being visited 
    // it means it has a cycle. After finish visiting its neighbors without encountering nodes being visited, it's marked as visited. 

    int dfsCheckcycle(int node, const vector<vector<int>>& graph, vector<int>& visited)
    {
        if ( visited[node] != 0 )
            return visited[node];
        visited[node] = -1;
        for ( auto next : graph[node] )
            if ( dfsCheckcycle(next,graph,visited) == -1 )
                return -1;
        visited[node] = 1;
        return 1;
    }

    // we employ memoization to calculate the max length starting from a node
    // the max length of node is the max of all it's neighbors plus 1 
    int longestpath(int node, const vector<vector<int>>& graph, vector<int>& visited_length)
    {
        if ( visited_length[node] != 0 )
            return visited_length[node];
        int len = 1; 
        for ( auto next : graph[node] ) {
            int next_len = longestpath(next,graph,visited_length);
            len = max(len,next_len+1);
        }
        visited_length[node] = len;
        return len;
    }
};