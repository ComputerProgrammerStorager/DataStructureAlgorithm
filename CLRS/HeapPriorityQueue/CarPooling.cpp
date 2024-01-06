/*
There is a car with capacity empty seats. The vehicle only drives east (i.e., it cannot turn around and drive west).

You are given the integer capacity and an array trips where trips[i] = [numPassengersi, fromi, toi] indicates that the ith trip has numPassengersi passengers and the locations to pick them up and drop them off are fromi and toi respectively. The locations are given as the number of kilometers due east from the car's initial location.

Return true if it is possible to pick up and drop off all passengers for all the given trips, or false otherwise.

 

Example 1:

Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false
Example 2:

Input: trips = [[2,1,5],[3,3,7]], capacity = 5
Output: true
 

Constraints:

1 <= trips.length <= 1000
trips[i].length == 3
1 <= numPassengersi <= 100
0 <= fromi < toi <= 1000
1 <= capacity <= 105
*/


class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        auto cmp1 = [] (vector<int> a, vector<int>b ) { 
          return a[1] < b[1];
        };
        auto cmp2 = [](pair<int,int> a, pair<int,int>b ) {
            return a.first > b.first;
        };

        sort(trips.begin(),trips.end(),cmp1);

        priority_queue<pair<int,int>,vector<pair<int,int>>, decltype(cmp2)> pq(cmp2);

        for ( auto t : trips ) {
          while( !pq.empty() && pq.top().first <= t[1] ) {
            capacity += pq.top().second;
            pq.pop();
          }

          if ( capacity < t[0] ) 
            return false;
          capacity -= t[0];
          pq.push({t[2],t[0]});
        }

        return true;
    }
};

// check the changes to the car at every timestamp 
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        map<int,int> changes;
        for ( auto t : trips ) {
          changes[t[1]] = changes[t[1]] - t[0];
          changes[t[2]] = changes[t[2]] + t[0];
        }

        int sum = 0;
        for ( auto it : changes ) {
          sum += it.second;
          if ( sum < -capacity ) 
            return false;
        }

        return true;
    }
};