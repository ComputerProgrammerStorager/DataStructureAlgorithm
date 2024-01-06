/*
You are given a 0-indexed array of positive integers tasks, representing tasks that need to be completed in order, where tasks[i] represents the type of the ith task.

You are also given a positive integer space, which represents the minimum number of days that must pass after the completion of a task before another task of the same type can be performed.

Each day, until all tasks have been completed, you must either:

Complete the next task from tasks, or
Take a break.
Return the minimum number of days needed to complete all tasks.

 

Example 1:

Input: tasks = [1,2,1,2,3,1], space = 3
Output: 9
Explanation:
One way to complete all tasks in 9 days is as follows:
Day 1: Complete the 0th task.
Day 2: Complete the 1st task.
Day 3: Take a break.
Day 4: Take a break.
Day 5: Complete the 2nd task.
Day 6: Complete the 3rd task.
Day 7: Take a break.
Day 8: Complete the 4th task.
Day 9: Complete the 5th task.
It can be shown that the tasks cannot be completed in less than 9 days.
Example 2:

Input: tasks = [5,8,8,5], space = 2
Output: 6
Explanation:
One way to complete all tasks in 6 days is as follows:
Day 1: Complete the 0th task.
Day 2: Complete the 1st task.
Day 3: Take a break.
Day 4: Take a break.
Day 5: Complete the 2nd task.
Day 6: Complete the 3rd task.
It can be shown that the tasks cannot be completed in less than 6 days.
 

Constraints:

1 <= tasks.length <= 105
1 <= tasks[i] <= 109
1 <= space <= tasks.length
*/

// remember each completed one's compeletion time 
class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        unordered_map<int,long long> prev_complete;
        long long days = 1;
        prev_complete[tasks[0]] = days;
        for (int i = 1; i < tasks.size(); i++ ) {
            days++;
            if ( prev_complete.count(tasks[i]) == 0 || days - prev_complete[tasks[i]] - 1 >= space ) {
                prev_complete[tasks[i]] = days;
                continue;
            } else {
                days += space-(days-prev_complete[tasks[i]]-1);
                prev_complete[tasks[i]] = days;
            }
        }

        return days;
    }
};


// remeber the earliest time a task can start in the future 
class Solution {
public:
    long long taskSchedulerII(vector<int>& tasks, int space) {
        long long day = 0;
        unordered_map<int,long long> earliest;
        for (int i = 0; i < tasks.size(); i++ ) {
            if ( earliest.count(tasks[i]) ) 
                day = max(day,earliest[tasks[i]]);
            earliest[tasks[i]] = day+space+1;
            day++;
        }

        return day;
    }
};