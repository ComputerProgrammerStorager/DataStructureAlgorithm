/*
Given an integer n and an integer array rounds. We have a circular track which consists of n sectors labeled from 1 to n. A marathon will be held on this track, the marathon consists of m rounds. The ith round starts at sector rounds[i - 1] and ends at sector rounds[i]. For example, round 1 starts at sector rounds[0] and ends at sector rounds[1]

Return an array of the most visited sectors sorted in ascending order.

Notice that you circulate the track in ascending order of sector numbers in the counter-clockwise direction (See the first example).

 

Example 1:


Input: n = 4, rounds = [1,3,1,2]
Output: [1,2]
Explanation: The marathon starts at sector 1. The order of the visited sectors is as follows:
1 --> 2 --> 3 (end of round 1) --> 4 --> 1 (end of round 2) --> 2 (end of round 3 and the marathon)
We can see that both sectors 1 and 2 are visited twice and they are the most visited sectors. Sectors 3 and 4 are visited only once.
Example 2:

Input: n = 2, rounds = [2,1,2,1,2,1,2,1,2]
Output: [2]
Example 3:

Input: n = 7, rounds = [1,3,5,7]
Output: [1,2,3,4,5,6,7]
 

Constraints:

2 <= n <= 100
1 <= m <= 100
rounds.length == m + 1
1 <= rounds[i] <= n
rounds[i] != rounds[i + 1] for 0 <= i < m


*/

// special attention goes to the first round, whose start is included in this round. Otherwise, the start is included in the last round as its end
class Solution {
public:
    vector<int> mostVisited(int n, vector<int>& rounds) {
        vector<int> res;
        vector<int> freq(n+1,0);
        for ( int rnd = 1; rnd < rounds.size(); rnd++ )
        {
            int start = rnd == 1 ? rounds[rnd-1] : (rounds[rnd-1] != n ? rounds[rnd-1] + 1 : 1);
            int end = rounds[rnd];
            while( start != end )
            {
                freq[start]++;
                start = start != n ? start + 1 : 1;
            }
            freq[end]++;
        }
        
        int mx = INT_MIN;
        for ( int i = 1; i <= n; i++ )
            mx = max(mx,freq[i]);
        
        for ( int i = 1; i <= n; i++ )
            if ( freq[i] == mx )
                res.push_back(i);
        
        return res;
    }
};

// Two pointers needs a bit explanation about moving the pointers:
// 1. first if the left most pair's distance is shorter than d, then we know the current arr1[i] is not the answer, so we skip it my moving its index 
// 2. if the distance is larger, then depending on the if arr1[i] is on the right side of arr2[j] or not.
//    a. if arr1 is larger, then we need to further check it against other potential number which could make it ineligible, so move the second pointer 
//    b. if arr1 is smaller, then we know this one is a qualified candidate and shoud we should account it in and move to check the next num 
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int cnt = 0, i = 0, j = 0;
        sort(arr1.begin(),arr1.end());
        sort(arr2.begin(),arr2.end());
        if ( arr1[0] - arr2.back() > d || arr2[0] - arr1.back() > d )
            return 0;
        while( i < arr1.size() && j < arr2.size() )
        {
            if ( abs(arr1[i]-arr2[j]) <=d )
            {
                i++;
            }
            else 
            {
                if ( arr1[i] > arr2[j] )
                {
                    j++;
                }
                else {
                    cnt++;
                    i++;
                }
            }
        }
        
        return cnt + arr1.size() - i;
    }
};