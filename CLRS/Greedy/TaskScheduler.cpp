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

// This idea uses the greedy strategy to calculate the min idle time.
// First the max possible idle time is defined by the most frequent task (max_freq - 1) * n
// Then we can try to scheduling non-conflicting taks in those idle time, reducing idle time. 
// Note the idle time should be larger or equal to zero 
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26,0);
        for ( auto t : tasks )
            freq[t-'A']++;
        sort(freq.begin(),freq.end());
        int max_freq = freq[25];
        int max_idle = (max_freq-1) * n;
        for ( int i = 24; i >= 0; i-- )
            max_idle -= min(max_freq-1,freq[i]);
        max_idle = max(0,max_idle);
        return max_idle + tasks.size();
    }
};

// this idea considers the two cases where the idle slots between the most frequent task (note cound be multiple) is enough to hold 
// all the remaining tasks 
// if there are not enough slots, then the total time would be the size of tasks 
// if there are enough slots, then we have (max_freq - 1) groups of size (n+1) and the training number of max_freq 
// A ****** A ****** A ******* ABxxx(the number of tasks sharing the same max frequency)
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26,0);
        for ( auto t : tasks )
            freq[t-'A']++;
        sort(freq.begin(),freq.end());
        int max_freq = freq[25];
        int max_cnt = 1;
        for ( int i = 24; i >= 0; i-- )
        {
            if ( freq[i] != freq[25])
                break;
            max_cnt++;
        }
        return max((int)tasks.size(), (max_freq-1) * (n+1) + max_cnt);    
    }
};

// greedy algorithm to fill the most frequent tasks first to each of n+1 slots until they are all scheduled 
// Note for the last (n+1) group, it needs the size slots and for all previous groups it needs (n+1) time slots 
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26,0);
        for ( auto t : tasks )
            freq[t-'A']++;
        priority_queue<int> pq;
        for ( auto i : freq)
            if ( i )
                pq.push(i);
        int steps = 0;
        n++;
        while ( !pq.empty() )
        {
            int cur_sz = min((int)pq.size(),n);
            vector<int> put_back; 
            for ( int i = 0; i < cur_sz; i++)
            {
                int tmp = pq.top();
                pq.pop();
                tmp--;
                if ( tmp )
                    put_back.push_back(tmp);
            }
            
            if ( (int)put_back.size() )
                steps += n;
            else
                steps += cur_sz;
            for ( auto a : put_back )
                pq.push(a);
        }
        
        return steps;
    }
};  