/*
In the world of Dota2, there are two parties: the Radiant and the Dire.

The Dota2 senate consists of senators coming from two parties. Now the Senate wants to decide on a change in the Dota2 game. The voting for this change is a round-based procedure. In each round, each senator can exercise one of the two rights:

Ban one senator's right: A senator can make another senator lose all his rights in this and all the following rounds.
Announce the victory: If this senator found the senators who still have rights to vote are all from the same party, he can announce the victory and decide on the change in the game.
Given a string senate representing each senator's party belonging. The character 'R' and 'D' represent the Radiant party and the Dire party. Then if there are n senators, the size of the given string will be n.

The round-based procedure starts from the first senator to the last senator in the given order. This procedure will last until the end of voting. All the senators who have lost their rights will be skipped during the procedure.

Suppose every senator is smart enough and will play the best strategy for his own party. Predict which party will finally announce the victory and change the Dota2 game. The output should be "Radiant" or "Dire".

 

Example 1:

Input: senate = "RD"
Output: "Radiant"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And in round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.
Example 2:

Input: senate = "RDD"
Output: "Dire"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And the third senator comes from Dire and he can ban the first senator's right in round 1. 
And in round 2, the third senator can just announce the victory since he is the only guy in the senate who can vote.
 

Constraints:

n == senate.length
1 <= n <= 104
senate[i] is either 'R' or 'D'.

*/

// For each round voting, the optimal strategy would be to ban it's nearest opponent.. Note to Wrap around 
class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = senate.size();
        int dCnt = count(senate.begin(),senate.end(),'D');
        int rCnt = n - dCnt;
        vector<int> banned(n,false);
        auto ban = [&](char who, int idx) {
            while(true)
            {
                if ( senate[idx] == who && !banned[idx] ) {
                    banned[idx] = true;
                    break;
                }
                idx = (idx+1) % n;
            }
        };

        int idx = 0; 
        while( dCnt > 0 && rCnt > 0 )
        {
            if ( !banned[idx] )
            {
                if ( senate[idx] == 'R' )
                {
                    ban('D',(idx+1) % n );
                    dCnt--;
                } else {
                    ban('R', (idx+1) % n);
                    rCnt--;
                }
            }
            idx = (idx+1) % n;
        }

        return rCnt == 0 ? "Dire" : "Radiant";
    }
};

// Essentially, we need to know the next turn, and will keep the countpart  
// O(n)

class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = senate.size();
        if ( n == 0 )
            return "Radiant";
        queue<int> dTurn, rTurn;
        for ( int i = 0; i < n; i++ )
        {
            if ( senate[i] == 'R' )
                rTurn.push(i);
            else 
                dTurn.push(i);
        }

        while( !dTurn.empty() && !rTurn.empty() )
        {
            int rturn = rTurn.front();
            rTurn.pop();
            int dturn = dTurn.front();
            dTurn.pop();
            if ( rturn < dturn )
                rTurn.push(rturn+n);
            else 
                dTurn.push(dturn+n);
        }

        return dTurn.empty() ? "Radiant" : "Dire";
    }
};