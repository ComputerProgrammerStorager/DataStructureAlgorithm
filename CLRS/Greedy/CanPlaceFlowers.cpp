/*
You have a long flowerbed in which some of the plots are planted, and some are not. However, flowers cannot be planted in adjacent plots.

Given an integer array flowerbed containing 0's and 1's, where 0 means empty and 1 means not empty, and an integer n, return if n new flowers can be planted in the flowerbed without violating the no-adjacent-flowers rule.

 

Example 1:

Input: flowerbed = [1,0,0,0,1], n = 1
Output: true
Example 2:

Input: flowerbed = [1,0,0,0,1], n = 2
Output: false
 

Constraints:

1 <= flowerbed.length <= 2 * 104
flowerbed[i] is 0 or 1.
There are no two adjacent flowers in flowerbed.
0 <= n <= flowerbed.length
*/

// Basically we want to check if the total number of eligible positions is larger or equal than the requested 
// Then we can check if every empty position if it can be planted, by checking its adjcent positions 
// O(n) O(n)
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int cnt = 0;
        for ( int i = 0; i < flowerbed.size(); i++ )
        {
            if ( flowerbed[i] == 0 && canPlant(flowerbed,i) )
            {
                flowerbed[i] = 1;
                if ( ++cnt == n )
                {
                    break;
                }
            }
        }
        
        return cnt >= n;
    }
    
    bool canPlant(vector<int> const &flowerbed, int pos)
    {
       if ( (pos == 0 || flowerbed[pos-1] == 0) && (pos == flowerbed.size()-1 || flowerbed[pos+1] == 0) )
           return true;
        return false;
    }
};

// We can add a bit optimization by leveraging the property of flowerbed, i.e., if a pos is 1 then its left (if exist) and right (if exist) 
// must be zero, which should not be planted by the rule
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        for ( int i = 0; i < flowerbed.size() && n; i++ )
        {
            if ( flowerbed[i] )
            {
                i++;        // 1 0 x, next round to check x, thus jump two 
            }
            else 
            {
                if ( i == flowerbed.size() - 1 || flowerbed[i+1] == 0 )
                {
                    n--;
                    i++;    // 0 0 x, since we plant at the first zero, then the next zero i+1, should not be planted, so we jumpt to x position 
                }
            }
        }
        
        return n == 0;
    }
    
};