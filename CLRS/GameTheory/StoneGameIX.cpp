/*
Alice and Bob continue their games with stones. There is a row of n stones, and each stone has an associated value. You are given an integer array stones, where stones[i] is the value of the ith stone.

Alice and Bob take turns, with Alice starting first. On each turn, the player may remove any stone from stones. The player who removes a stone loses if the sum of the values of all removed stones is divisible by 3. Bob will win automatically if there are no remaining stones (even if it is Alice's turn).

Assuming both players play optimally, return true if Alice wins and false if Bob wins.

 

Example 1:

Input: stones = [2,1]
Output: true
Explanation: The game will be played as follows:
- Turn 1: Alice can remove either stone.
- Turn 2: Bob removes the remaining stone. 
The sum of the removed stones is 1 + 2 = 3 and is divisible by 3. Therefore, Bob loses and Alice wins the game.
Example 2:

Input: stones = [2]
Output: false
Explanation: Alice will remove the only stone, and the sum of the values on the removed stones is 2. 
Since all the stones are removed and the sum of values is not divisible by 3, Bob wins the game.
Example 3:

Input: stones = [5,1,2,4,3]
Output: false
Explanation: Bob will always win. One possible way for Bob to win is shown below:
- Turn 1: Alice can remove the second stone with value 1. Sum of removed stones = 1.
- Turn 2: Bob removes the fifth stone with value 3. Sum of removed stones = 1 + 3 = 4.
- Turn 3: Alices removes the fourth stone with value 4. Sum of removed stones = 1 + 3 + 4 = 8.
- Turn 4: Bob removes the third stone with value 2. Sum of removed stones = 1 + 3 + 4 + 2 = 10.
- Turn 5: Alice removes the first stone with value 5. Sum of removed stones = 1 + 3 + 4 + 2 + 5 = 15.
Alice loses the game because the sum of the removed stones (15) is divisible by 3. Bob wins the game.
 

Constraints:

1 <= stones.length <= 105
1 <= stones[i] <= 104

*/

// In this type of game, obviously we need a helper function which takes as input parameters the current state (sum), the current player
// and the current choices set (count). 
// In this game, first the current sum should not be multiple of 3, otherwise the other player has already lost the game. 
// Then the current player should greedily choose a value of multiple three.. as this would keep himself absolutely safe while reducing the other 
// player's safe choice
// Then if not avaiable, then the choice has to depend on the sum.. if the sum % 3 == 1, then he has to choose count%3 == 1. Same for the other case. 
class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        vector<int> count(3,0);
        int sum = 0;
        for ( int x : stones )
            count[x%3]++;
        auto tmp = count;
        if ( count[1] )
        {
            count[1]--;
            if ( !win(count,sum+1,1) )
                return true;
        }
        count = tmp;
        if ( count[2] )
        {
            count[2]--;
            if ( !win(count,sum+2,1) )
                return true;
        }
        
        return false;
    }
    
    bool win(vector<int>& count, int sum, int player)
    {
        if ( accumulate(count.begin(),count.end(),0) == 0 )
        {
            if ( player == 1 )
                return true;
            return false;
        }
        if ( count[0] )
        {
            count[0]--;
            return !win(count,sum,!player);
        }
        if ( sum%3 == 1 )
        {
            if ( count[1] )
            {
                count[1]--;
                return !win(count,sum+1,!player);
            }
            return false;
        }
        else 
        {
            if ( count[2] )
            {
                count[2]--;
                return !win(count,sum+2,!player);
            }
            return false;
        }
    }
};