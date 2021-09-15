/*
Given the availability time slots arrays slots1 and slots2 of two people and a meeting duration duration, return the earliest time slot that works for both of them and is of duration duration.

If there is no common time slot that satisfies the requirements, return an empty array.

The format of a time slot is an array of two elements [start, end] representing an inclusive time range from start to end.

It is guaranteed that no two availability slots of the same person intersect with each other. That is, for any two time slots [start1, end1] and [start2, end2] of the same person, either start1 > end2 or start2 > end1.

 

Example 1:

Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
Output: [60,68]
Example 2:

Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
Output: []
 

Constraints:

1 <= slots1.length, slots2.length <= 104
slots1[i].length, slots2[i].length == 2
slots1[i][0] < slots1[i][1]
slots2[i][0] < slots2[i][1]
0 <= slots1[i][j], slots2[i][j] <= 109
1 <= duration <= 106
*/
// we can sort the slots according to start time and use two pointers 
// when two slots intersect, the qualified duration is [max(slots1[i][0],slots2[j][0]),min(slotss[i][1],slots2[j][1])]
// The key point is to move which slot if the current intersection does not satisfy. We should move the one which has earlier end time 
//  because if slots1[i][1] > slots2[j][1], then for sure slots1[i+1][0] > slots1[i][1] > slots1[j][1], meaning if we move i when slots1[i][1] > slots2[j][1],
//  there will no be intersection to slots2[j] at all and we will miss the opportunity to find the an answer. 
class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        auto cmp = [](vector<int> const& a, vector<int> const& b) {
            if ( a[0] <= b[0] )
                return true;
            return false;
        };
        int i = 0, j = 0;
        sort(slots1.begin(),slots1.end(),cmp);
        sort(slots2.begin(),slots2.end(),cmp);
        while( i < slots1.size() && j < slots2.size() )
        {
            int left = max(slots1[i][0],slots2[j][0]);
            int right = min(slots1[i][1],slots2[j][1]);
            if ( right - left >= duration )
            {
                return {left, left+duration};
            }
            
            if ( slots1[i][1] < slots2[j][1] )
                i++;
            else
                j++;
        }
        
        return {};
    }
};


// same idea as above, but using a priority queue 
// we push all slots that are longer than duration in a priority queue which is sorted based on start time. 
// Then we pop the first slot and then if it's ending time is larger or equal to the next sum of next start time and duration, 
// it means we have found one intersection satisfying the condition.
class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        auto cmp = [](vector<int> const& a, vector<int> const& b) {
            if ( a[0] >= b[0] )
                return true;
            return false;
        };
        
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        for ( auto i : slots1 )
            if ( i[1] - i[0] >= duration )
                pq.push(i);
        for ( auto i : slots2 )
            if ( i[1] - i[0] >= duration )
                pq.push(i);
        
        while( pq.size() > 1 )
        {
            auto prev = pq.top();
            pq.pop();
            if ( prev[1] >= pq.top()[0] + duration )
                return {pq.top()[0],pq.top()[0]+duration};
        }
        
        return {};
    }
};