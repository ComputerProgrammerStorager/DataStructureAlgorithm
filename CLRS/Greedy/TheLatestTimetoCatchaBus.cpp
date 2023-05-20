/*
You are given a 0-indexed integer array buses of length n, where buses[i] represents the departure time of the ith bus. You are also given a 0-indexed integer array passengers of length m, where passengers[j] represents the arrival time of the jth passenger. All bus departure times are unique. All passenger arrival times are unique.

You are given an integer capacity, which represents the maximum number of passengers that can get on each bus.

When a passenger arrives, they will wait in line for the next available bus. You can get on a bus that departs at x minutes if you arrive at y minutes where y <= x, and the bus is not full. Passengers with the earliest arrival times get on the bus first.

More formally when a bus arrives, either:

If capacity or fewer passengers are waiting for a bus, they will all get on the bus, or
The capacity passengers with the earliest arrival times will get on the bus.
Return the latest time you may arrive at the bus station to catch a bus. You cannot arrive at the same time as another passenger.

Note: The arrays buses and passengers are not necessarily sorted.

 

Example 1:

Input: buses = [10,20], passengers = [2,17,18,19], capacity = 2
Output: 16
Explanation: Suppose you arrive at time 16.
At time 10, the first bus departs with the 0th passenger. 
At time 20, the second bus departs with you and the 1st passenger.
Note that you may not arrive at the same time as another passenger, which is why you must arrive before the 1st passenger to catch the bus.
Example 2:

Input: buses = [20,30,10], passengers = [19,13,26,4,25,11,21], capacity = 2
Output: 20
Explanation: Suppose you arrive at time 20.
At time 10, the first bus departs with the 3rd passenger. 
At time 20, the second bus departs with the 5th and 1st passengers.
At time 30, the third bus departs with the 0th passenger and you.
Notice if you had arrived any later, then the 6th passenger would have taken your seat on the third bus.
 

Constraints:

n == buses.length
m == passengers.length
1 <= n, m, capacity <= 105
2 <= buses[i], passengers[i] <= 109
Each element in buses is unique.
Each element in passengers is unique.

*/


// Starting from the earliest latest time and work forward to update it if possible. 
// We try to take as many passengers as possible (greedily) for a bus. If there is no elgible passenger at one timepoint, 
// then we move to consider the following passengers in the next bus. This process is repeated. 
// A passenger is taken by the current bus if the bus still has room ( cur_taken < capacity ) and the passenger's arrival time is less than or equal to 
// the bus arrival time (passengers[j] <= buses[i]). 
class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        int bus_num = buses.size(), pass_num = passengers.size(); 
        if ( bus_num == 0 || pass_num == 0 )
            return 0;
        sort( buses.begin(), buses.end());
        sort( passengers.begin(), passengers.end());
        // special case where all passengers arrived after all buses departed, then the last bus departure time is the latest time for which the passenger can catch a (i.e., the last) bus. 
        if ( passengers.front() > buses.back() )
            return buses.back();
        int i = 0, j = 0, res = passengers[0]-1;
        while( i < bus_num )
        {
            int cur_taken = 0;
            // if the current bus has room and the next passenger in the line arrived earlier than the current bus departure time
            // if the previous onborded passenger is not one time unit before the passenger, then we could arrive right before the
            // passenger, obatining a later arrive time. Otherwise, the time was already updated the same manner when processing previous passengers. 
            while( cur_taken < capacity && j < pass_num && passengers[j] <= buses[i] )
            {
                // we find a viable later arrival time for the passenger
                if ( j > 0 && passengers[j-1] + 1 != passengers[j] ) 
                {
                    res = passengers[j]-1;
                }
                cur_taken++;
                j++;
            }
            // if the above while exit due to condition that the bus was not full and the arrival time of the last onboarded passenger is earlier than buses departure time, 
            // the we have another even later arrival time for the passenger, which is equal to the bus departure time. 
            if ( cur_taken < capacity && j > 0 && passengers[j-1] != buses[i] )
                res = buses[i];
            i++;
        }

        return res;
    }
};