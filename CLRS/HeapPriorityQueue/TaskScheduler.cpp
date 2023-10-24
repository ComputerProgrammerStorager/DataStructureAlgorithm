/*
Given a characters array tasks, representing the tasks a CPU needs to do, where each letter represents a different task. Tasks could be done in any order. Each task is done in one unit of time. For each unit of time, the CPU could complete either one task or just be idle.

However, there is a non-negative integer n that represents the cooldown period between two same tasks (the same letter in the array), that is that there must be at least n units of time between any two same tasks.

Return the least number of units of times that the CPU will take to finish all the given tasks.

 

Example 1:

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.
Example 2:

Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.
Example 3:

Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation: 
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A
 

Constraints:

1 <= task.length <= 104
tasks[i] is upper-case English letter.
The integer n is in the range [0, 100].
*/

// the max possible idle time is determined by the most frequent task(s). We can obtain the max possible idle time, when it has the 
// following pattern, which is (max_freq-1) * n. 
// T ***(n) T ***(n).... T. 
// However, these idle time slots could be used to complete any other tasks in a greedy manner. 
// So for each less frequent task, if it could leverage available idle time slot, which is min(max_freq-1, freq[i]). 
// It's possible that there is no avaliable slot time for a less frequent task, where it will placed at the last of the sequence. 
// those are counted in by tasks.size(). 

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26,0);
        for ( auto c : tasks )
            freq[c-'A']++;
        sort(freq.begin(),freq.end());
        int max_freq = freq[25], idle = (max_freq-1) * n;
        for ( int i = 0; i < 25 && idle > 0; i++ )
            idle -= min(max_freq-1,freq[i]);
        idle = max(0,idle);
        return idle+tasks.size();
    }
};

// same idea as above, but use math calculation 
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26,0);
        for ( auto c : tasks )
            freq[c-'A']++;
        int max_freq = *max_element(freq.begin(),freq.end());
        int f_max = 0;
        for ( auto f : freq )
            if ( f == max_freq )
                f_max++;
        return max((int)tasks.size(), (max_freq-1) * (n+1) + f_max);
    }
};


// use priority queue to simulate the process 
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26,0);
        for ( auto t : tasks )
            freq[t-'A']++;
        priority_queue<int> pq;
        for ( auto f : freq )
            if ( f )
                pq.push(f);
        int steps = 0;
        n++;
        while(!pq.empty())
        {
            int cur_sz = min(n,(int)pq.size());
            vector<int> put_back;
            for ( int i = 0; i < cur_sz; i++ )
            {
                int cur = pq.top();
                pq.pop();
                if ( --cur )
                    put_back.push_back(cur);
            }
            if ( (int)put_back.size())
                steps += n;
            else 
                steps += cur_sz;
            for ( auto n : put_back )
                pq.push(n);
        }
        return steps;
    }
};