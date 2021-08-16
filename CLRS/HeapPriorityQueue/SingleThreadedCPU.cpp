/*
You are given n​​​​​​ tasks labeled from 0 to n - 1 represented by a 2D integer array tasks, where tasks[i] = [enqueueTimei, processingTimei] means that the i​​​​​​th​​​​ task will be available to process at enqueueTimei and will take processingTimei to finish processing.

You have a single-threaded CPU that can process at most one task at a time and will act in the following way:

If the CPU is idle and there are no available tasks to process, the CPU remains idle.
If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest processing time. If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.
Once a task is started, the CPU will process the entire task without stopping.
The CPU can finish a task then start a new one instantly.
Return the order in which the CPU will process the tasks.

 

Example 1:

Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
Output: [0,2,3,1]
Explanation: The events go as follows: 
- At time = 1, task 0 is available to process. Available tasks = {0}.
- Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
- At time = 2, task 1 is available to process. Available tasks = {1}.
- At time = 3, task 2 is available to process. Available tasks = {1, 2}.
- Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it is the shortest. Available tasks = {1}.
- At time = 4, task 3 is available to process. Available tasks = {1, 3}.
- At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the shortest. Available tasks = {1}.
- At time = 6, the CPU finishes task 3 and starts processing task 1. Available tasks = {}.
- At time = 10, the CPU finishes task 1 and becomes idle.
Example 2:

Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
Output: [4,3,2,0,1]
Explanation: The events go as follows:
- At time = 7, all the tasks become available. Available tasks = {0,1,2,3,4}.
- Also at time = 7, the idle CPU starts processing task 4. Available tasks = {0,1,2,3}.
- At time = 9, the CPU finishes task 4 and starts processing task 3. Available tasks = {0,1,2}.
- At time = 13, the CPU finishes task 3 and starts processing task 2. Available tasks = {0,1}.
- At time = 18, the CPU finishes task 2 and starts processing task 0. Available tasks = {1}.
- At time = 28, the CPU finishes task 0 and starts processing task 1. Available tasks = {}.
- At time = 40, the CPU finishes task 1 and becomes idle.
 

Constraints:

tasks.length == n
1 <= n <= 105
1 <= enqueueTimei, processingTimei <= 109
*/

#include "../Common/common_api.h"

class Solution {
    typedef pair<int,int> PII;
public:
    vector<int> getOrder(vector<vector<int>>& tasks) { 
        vector<int> res;
        priority_queue<PII,vector<PII>, greater<PII>> pq;       // processing time vs index
        long curtime = 0;
        int N = tasks.size(), i = 0;
        
        for ( int i = 0; i < N; i++ )
            tasks[i].push_back(i);
        
        sort(tasks.begin(),tasks.end());
        
        while ( i < N )
        {
            if ( tasks[i][0] <= curtime )
            {
                pq.push({tasks[i][1],tasks[i][2]});
                i++;
                continue;
            }
            
            if ( pq.empty() )
            {
                curtime = tasks[i][0];
            }
            else
            {
                auto t = pq.top();
                pq.pop();
                res.push_back({t.second});
                curtime += t.first;
            }
        }
    
        while ( !pq.empty() )
        {
            auto t = pq.top();
            res.push_back(t.second);
            pq.pop();
        }
        return res;
    }
};

int main()
{
    //vector<vector<int>> tasks = {{1,2},{2,4},{3,2},{4,1}};
    vector<vector<int>> tasks = {{19,13},{16,9},{21,10},{32,25},{37,4},{49,24},{2,15},{38,41},{37,34},{33,6},{45,4},{18,18},{46,39},{12,24}};
    Solution s;
    s.getOrder(tasks);
}

#if 0

{{19,13},{16,9},{21,10},{32,25},{37,4},{49,24},{2,15},{38,41},{37,34},{33,6},{45,4},{18,18},{46,39},{12,24}}
{6,1,2,9,4,10,0,11,13,5,3,8,12,7}
{6,1,2,9,4,10,0,11,5,13,3,8,12,7}

class Solution {
    typedef pair<int, int> T; // processing time, index
public:
    vector<int> getOrder(vector<vector<int>>& A) {
        priority_queue<T, vector<T>, greater<>> pq; // min heap of tasks, sorted first by processing time then by index.
        long N = A.size(), time = 0, i = 0; // `time` is the current time, `i` is the read pointer
        for (int i = 0; i < N; ++i) A[i].push_back(i); // append the index to each task
        sort(begin(A), end(A)); // sort the input array so that we can take the tasks of small enqueueTime first
        vector<int> ans;
        while (i < N || pq.size()) { // stop the loop when we exhausted the input array and the tasks in the heap.
            if (pq.empty()) {
                time = max(time, (long)A[i][0]); // nothing in the heap? try updating the current time using the processing time of the next task in array
            }
            while (i < N && time >= A[i][0]) { // push all the tasks in the array whose enqueueTime <= currentTime into the heap
                pq.emplace(A[i][1], A[i][2]);
                ++i;
            }
            auto [pro, index] = pq.top();
            pq.pop();
            time += pro; // handle this task and increase the current time by the processingTime
            ans.push_back(index);
        }
        return ans;
    }
};
#endif