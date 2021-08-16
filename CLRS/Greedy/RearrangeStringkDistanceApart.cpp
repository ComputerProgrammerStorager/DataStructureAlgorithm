/*
Given a string s and an integer k, rearrange s such that the same characters are at least distance k from each other. If it is not possible to rearrange the string, return an empty string "".

 

Example 1:

Input: s = "aabbcc", k = 3
Output: "abcabc"
Explanation: The same letters are at least a distance of 3 from each other.
Example 2:

Input: s = "aaabc", k = 3
Output: ""
Explanation: It is not possible to rearrange the string.
Example 3:

Input: s = "aaadbbcc", k = 2
Output: "abacabcd"
Explanation: The same letters are at least a distance of 2 from each other.
 

Constraints:

1 <= s.length <= 3 * 105
s consists of only lowercase English letters.
0 <= k <= s.length
*/

class Solution {
public:
    string rearrangeString(string s, int k) {
        unordered_map<char,int> m;
        string res;
        priority_queue<pair<int,char>> pq;
        
        if ( k == 0 )
            return s;
        for ( auto c : s )
            m[c]++;
        
        for ( auto t : m )
            pq.push({t.second,t.first});
        
        while( !pq.empty())
        {
            vector<pair<int,char>> temp; 
            if ((int)pq.size() < k)
            {
                while( !pq.empty() )
                {
                    auto t = pq.top();
                    pq.pop();
                    if (t.first != 1)
                        return "";
                    res.push_back(t.second);
                }
            }
            
            int i = 0;
            while ( i < k && !pq.empty())
            {
                auto t = pq.top();
                pq.pop();
                res.push_back(t.second);
                if ( --t.first)
                    temp.push_back(t);
                i++;
            }
            
            for ( auto t : temp )
                pq.push(t);
        }
        
        return res;
    }
};