/*
We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.

 

Example 1:



Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job. 
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
Example 2:



Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
Output: 150
Explanation: The subset chosen is the first, fourth and fifth job. 
Profit obtained 150 = 20 + 70 + 60.
Example 3:



Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
Output: 6
 

Constraints:

1 <= startTime.length == endTime.length == profit.length <= 5 * 104
1 <= startTime[i] < endTime[i] <= 109
1 <= profit[i] <= 104
*/

// thought process
// 1. In general, we want to schedule the jobs based on starttime, i.e., we want to assign the 
// jobs to the time intervals as much as possible. If we don't consider the earliest first, 
// then we might miss some of the great opportunity, greedily getting the max profit. 
// 2. Then for each of job, we need to make a decision, when take it or not, which affects our later choice. 
// If we take/schedule it, then we put those jobs whose starttime is earlier than the endtime of the one just scheduled INELIGIBLE, 
// making the next eligble job have a minimum start time of the completed endtime. 
// If we skip it, then we can consider the next earliest (sorted order helps :-) job and repeat the same decision process. 
// Overall, this again shows us nothing is free, i.e., you get profit from the current job, then you exclude some conflicting choices. 
// For each job choice we make, it leads to two different results, and we are asked to obtain a max value. 
// this hints us to use dynamic programming


// top-down + binary search 
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<vector<int>> jobs;
        int n = startTime.size();
        vector<int> memo(n,-1);
        for (int i = 0; i < n; i++ )
        {
            jobs.push_back({startTime[i],endTime[i],profit[i]});
        }
        sort(startTime.begin(),startTime.end());
        sort(jobs.begin(),jobs.end());
        
        return findmaxprofit(jobs,startTime,0,memo);
    }
    
    int findmaxprofit(vector<vector<int>> const& jobs, vector<int> const& starttime, int pos, vector<int> &memo)
    {
        int n = starttime.size();
        if ( pos == n )
            return 0;
        if ( memo[pos] != -1 )
            return memo[pos];
        
        int nextpos = lower_bound(starttime.begin(),starttime.end(),jobs[pos][1]) - starttime.begin();
        int cur_maxprofit = max(findmaxprofit(jobs,starttime,pos+1,memo), jobs[pos][2] + findmaxprofit(jobs,starttime,nextpos,memo));
        return memo[pos] = cur_maxprofit;
    }
};


// For each job, we consider if it's worth to take it or not. 
// If we take it, then the profit is the max_profit up to the job's start time's maxProfit 
// If we don't take it, then the profit is current max_profit, i.e., the max_profit up to the previous job 
// So we store all max_profit in a sorted set, i.e., for finding those required previous values 
// Note: to avoid out-of-range of prev(upper_bound(val),1) we init the map[-1] = 0 or map[0] = 0, as endtime is > 0, to ensure upper_bound never returns begin(). 
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int max_profit = INT_MIN, n = endTime.size();
        map<int,int> dp;
        dp[0] = 0;
        vector<vector<int>> jobs;
        for ( int i = 0; i < n; i++ ) {
            jobs.push_back({endTime[i],startTime[i],profit[i]});
        }

        sort(jobs.begin(),jobs.end());
        for ( int i = 0; i < n; i++ ) {
            int take = prev(dp.upper_bound(jobs[i][1]),1)->second + jobs[i][2];
            int not_take = max_profit;
            max_profit = max(take,not_take);
            dp[jobs[i][0]] = max_profit;
        }

        return max_profit;
    }
};