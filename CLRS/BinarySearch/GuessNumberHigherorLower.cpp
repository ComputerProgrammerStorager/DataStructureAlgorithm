/*
We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I will tell you whether the number I picked is higher or lower than your guess.

You call a pre-defined API int guess(int num), which returns three possible results:

-1: Your guess is higher than the number I picked (i.e. num > pick).
1: Your guess is lower than the number I picked (i.e. num < pick).
0: your guess is equal to the number I picked (i.e. num == pick).
Return the number that I picked.

 

Example 1:

Input: n = 10, pick = 6
Output: 6
Example 2:

Input: n = 1, pick = 1
Output: 1
Example 3:

Input: n = 2, pick = 1
Output: 1
 

Constraints:

1 <= n <= 231 - 1
1 <= pick <= n
*/
// Binary search on the range 
class Solution {
public:
    int guessNumber(int n) {
        int l = 1, r = n;
        while ( l <= r )
        {
            int m = l + (r-l)/2;
            int ret = guess(m);
            if ( ret == 0 )
                return m;
            if ( ret == -1 )
                r = m-1;
            else 
                l = m+1;
        }
        
        return l;
    }
};