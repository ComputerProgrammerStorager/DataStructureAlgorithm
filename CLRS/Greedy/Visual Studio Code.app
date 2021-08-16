/*
Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

 

Example 1:

Input: s = "aab"
Output: "aba"
Example 2:

Input: s = "aaab"
Output: ""
 

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.

*/

// use greedy algorithm to construct the string 
class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> m;
        string res;
        for ( auto c : s )
            m[c]++;
        priority_queue<pair<int,char>> pq;
        for ( auto it : m )
            pq.push({it.second,it.first});
        while( !pq.empty())
        {
            vector<pair<int,char>> temp; 
            if ( pq.size() == 1 && pq.top().first > 1 )
                return "";
            int i = 0;
            while ( i < 2 && !pq.empty())
            {
                auto t = pq.top();
                pq.pop();
                res.push_back(t.second);
                if (--t.first)
                    temp.push_back(t);
                i++;
            }
            for ( auto t : temp )
                pq.push(t);
        }
        return res;
    }
};