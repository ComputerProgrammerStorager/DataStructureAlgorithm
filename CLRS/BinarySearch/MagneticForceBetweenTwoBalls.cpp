/*
In the universe Earth C-137, Rick discovered a special form of magnetic force between two balls if they are put in his new invented basket. Rick has n empty baskets, the ith basket is at position[i], Morty has m balls and needs to distribute the balls into the baskets such that the minimum magnetic force between any two balls is maximum.

Rick stated that magnetic force between two different balls at positions x and y is |x - y|.

Given the integer array position and the integer m. Return the required force.

 

Example 1:


Input: position = [1,2,3,4,7], m = 3
Output: 3
Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic force between ball pairs [3, 3, 6]. The minimum magnetic force is 3. We cannot achieve a larger minimum magnetic force than 3.
Example 2:

Input: position = [5,4,3,2,1,1000000000], m = 2
Output: 999999999
Explanation: We can use baskets 1 and 1000000000.
 

Constraints:

n == position.length
2 <= n <= 105
1 <= position[i] <= 109
All integers in position are distinct.
2 <= m <= position.length
*/

// Naive approarch would be to check eacho of the m combinations (C(n,m)) and choose the miminum distance 
// We can do binary search on the possible range, i.e., [1, max_diff], and check each valud if it satisfies the condition 
class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        int n = position.size(); 
        sort(position.begin(),position.end());
        if ( n  < m )
            return -1;
        int left = 1, right = position.back() - position[0];
        while( left <= right )
        {
            int mid = (left+right)/2;
            if ( canarrange(position,mid,m) )
                left = mid+1;
            else
                right = mid-1;
        }
        
        return right;
    }
private:
    bool canarrange(vector<int>& position, int force, int balls)
    {
        int last = 0, next = 1, n = position.size();
        for ( int b = 1; b < balls; b++ )
        {
            while( next < n && position[next] < position[last] + force )
                next++;
            if ( next >= n )
                return false;
            last = next;
        }
        
        return true;
    }
};

// same idea, but alternatively, we could calculate the number of balls that can be fit for a chosen force value
class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        int n = position.size(); 
        if ( n < m )
            return -1;
        sort(position.begin(),position.end());
        int l = 1, r = position.back() - position[0];
        while( l < r )
        {
            int mid = r-(r-l)/2;
            if ( countballs(position,mid) >= m )
                l = mid;
            else
                r = mid-1;
        }
        
        return r;
    }
    
private:
    int countballs(vector<int>& position, int force)
    {
        int cnt = 1, n = position.size(),last = 0;
        for ( int i = 1; i < n; i++)
        {
            if ( position[i] - position[last] >= force )
            {
                cnt++;
                last = i;
            }
        }
        
        return cnt;
    }
};