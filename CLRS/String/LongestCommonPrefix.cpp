/*
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

 

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
 

Constraints:

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lower-case English letters.
*/

// vertical scanning 
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res;
        int minlen = INT_MAX;
        for ( auto s : strs )
            if ( s.size() < INT_MAX )
                minlen = s.size();
        
        for ( int i = 0; i < minlen; i++ )
        {
            int j = 1;
            for ( j = 1; j < strs.size(); j++ )
            {
                if ( strs[j][i] != strs[0][i] )
                    break;
            }
            if ( j != strs.size() )
                break;
            else
                res.push_back(strs[0][i]);
        }
        
        return res;
    }
};

// divide and conquer
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        return getprefix(strs,0,strs.size()-1);
    }
    
    string getprefix(vector<string>& strs, int s, int e )
    {
        if ( s == e )
            return strs[s];
        int mid = s + (e-s) / 2;
        string leftprefix = getprefix(strs,s,mid);
        string rightprefix = getprefix(strs,mid+1,e);
        return commonprefix(leftprefix,rightprefix);
    }
    
    string commonprefix(string s1, string s2)
    {
        int minlen = min(s1.size(), s2.size());
        string res;
        for ( int i = 0; i < minlen; i++ )
        {
            if ( s1[i] != s2[i] )
                break;
            else
                res.push_back(s1[i]);
        }
        return res;
    }
};