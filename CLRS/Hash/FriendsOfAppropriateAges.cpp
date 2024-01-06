/*
There are n persons on a social media website. You are given an integer array ages where ages[i] is the age of the ith person.

A Person x will not send a friend request to a person y (x != y) if any of the following conditions is true:

age[y] <= 0.5 * age[x] + 7
age[y] > age[x]
age[y] > 100 && age[x] < 100
Otherwise, x will send a friend request to y.

Note that if x sends a request to y, y will not necessarily send a request to x. Also, a person will not send a friend request to themself.

Return the total number of friend requests made.

 

Example 1:

Input: ages = [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:

Input: ages = [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:

Input: ages = [20,30,100,110,120]
Output: 3
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
 

Constraints:

n == ages.length
1 <= n <= 2 * 104
1 <= ages[i] <= 120
*/

// use age cnt to match age cnt 
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        unordered_map<int,int> m1, m2;
        int res = 0;
        for ( auto age : ages ) {
            m1[age]++;
            m2[age]++;
        }

        for ( auto it1 : m1 ) 
            for ( auto it2 : m2 ) {
                if ( cansend(it1.first, it2.first) ) {
                    res += it1.second * it2.second;
                    if ( it1.first == it2.first ) {
                        res -= it1.second;
                    }
                }
            }

        return res;
    }

    bool cansend(int from, int to) {
        if ( (to > 100 & from < 100) || to <= 0.5 * from + 7 || to > from ) 
            return false;
        return true;
    }
};