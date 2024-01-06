/*
Given the array houses where houses[i] is the location of the ith house along a street and an integer k, allocate k mailboxes in the street.

Return the minimum total distance between each house and its nearest mailbox.

The test cases are generated so that the answer fits in a 32-bit integer.

 

Example 1:


Input: houses = [1,4,8,10,20], k = 3
Output: 5
Explanation: Allocate mailboxes in position 3, 9 and 20.
Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5 
Example 2:


Input: houses = [2,3,5,12,18], k = 2
Output: 9
Explanation: Allocate mailboxes in position 3 and 14.
Minimum total distance from each houses to nearest mailboxes is |2-3| + |3-3| + |5-3| + |12-14| + |18-14| = 9.
 

Constraints:

1 <= k <= houses.length <= 100
1 <= houses[i] <= 104
All the integers of houses are unique.
*/

// If only 1 mailbox were to be used, then the minimum distance will be when the mailbox is placed at the median point 
// Then we can place the k-1 up to a point, and then place the last mailbox for the remaining houses 
// dp[i][k] denotes the minium distance using k mailboxes to cover i+1 houses, i.e., house[0,i]. 
// then dp[i][k] = min(dp[j][k-1], dist(j+1,i) for all j >= 0 && j <= i. 
class Solution {
public:
    int minDistance(vector<int>& houses, int k) {
        int res = 0, n = houses.size();
        vector<vector<int>> dp(n,vector<int>(k+1,INT_MAX/2));
        vector<vector<int>> dist(n,vector<int>(n,0));
        sort(houses.begin(),houses.end());

        for ( int i = 0; i < n; i++ ) 
            for ( int j = i+1; j < n; j++ ) 
                dist[i][j] = mindist(houses,i,j);
        
        for ( int i = 0; i < n; i++ ) 
            dp[i][1] = dist[0][i];
        
        for (int i = 0; i < n; i++ )
            for ( int m = 2; m <= k; m++ ) {
                for ( int l = 0; l+1 <= i; l++ ) {
                    dp[i][m] = min(dp[i][m],dp[l][m-1]+dist[l+1][i]);
                }
            }

        return dp[n-1][k];

    }

    // assume houses is sorted and s <= e 
    int mindist(vector<int>& houses, int s, int e) { 
        int res = 0;
        while( s < e ) {
            res += houses[e] - houses[s];
            s++;
            e--;
        }
        return res;
    }
};