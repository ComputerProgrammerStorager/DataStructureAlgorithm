/*
Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

Example 1:

Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
Output: "apple"
Example 2:

Input: s = "abpcplea", dictionary = ["a","b","c"]
Output: "a"
 

Constraints:

1 <= s.length <= 1000
1 <= dictionary.length <= 1000
1 <= dictionary[i].length <= 1000
s and dictionary[i] consist of lowercase English letters.
*/

// the key point is to use two pointers technique to check if a string can be formed via deleting chars from another string 
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        vector<string> longest_str; 
        for ( auto w : dictionary )
        {
            if ( CanFormViaDelete(s,w) )
            {
                longest_str.push_back(w);
            }
        }
        
        if ( longest_str.size() == 0 )
            return "";
        auto cmp = [](string const &s1, string const &s2){
            if ( s1.size() > s2.size() )
                return true;
            else if ( s1.size() == s2.size() )
            {
                return s1 < s2;
            }
            else {
                return false;
            }
        };
        
        sort( longest_str.begin(), longest_str.end(), cmp);
        return longest_str[0];
    }
    
    bool CanFormViaDelete(string const &s, string const &t)
    {
        int s_len = s.size(), t_len = t.size();
        int i, j;
        for ( j = 0, i = 0; i < s_len && j < t_len; )
        {
            if ( s[i] == t[j])
            {
                i++;
                j++;
            }
            else {
                i++;
            }
        }
        
        return j == t_len;
        
    }
};

// same deal but no sorting involved 
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        string res = "";
        for ( auto w : dictionary )
        {
            if ( CanFormViaDelete(s,w) && (w.size() > res.size() || (w.size() == res.size() && w < res )))
            {
                res = w;
            }
        }
        return res;
    }
    
    bool CanFormViaDelete(string const &s, string const &t)
    {
        int s_len = s.size(), t_len = t.size();
        int i, j;
        for ( j = 0, i = 0; i < s_len && j < t_len; )
        {
            if ( s[i] == t[j])
            {
                i++;
                j++;
            }
            else {
                i++;
            }
        }
        
        return j == t_len;
        
    }
};

// we can use next[i][ch] to fasten the checking of subsequence 
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        string res = "";
        int m = s.size();
        s = "+" + s;
        vector<vector<int>> next(m+1,vector<int>(26,-1));
        for ( int i = m-1; i >= 0; i-- )
        {
            for ( int ch = 0; ch < 26; ch++ )
                next[i][ch] = next[i+1][ch];
            next[i][s[i+1]-'a'] = i+1;
        }

        for ( auto w : dictionary )
        {
            if ( CanFormViaDelete(next,w) && (w.size() > res.size() || (w.size() == res.size() && w < res )))
            {
                res = w;
            }
        }

        return res;
    }
    
    bool CanFormViaDelete(vector<vector<int>> const &next, string const &t)
    {
        // next[i][ch]: denotes the position of first ch after pos i, -1 if the ch doesn't exist 
        int i = 0;
        for ( auto c : t )
        {
            i = next[i][c-'a'];
            if ( i == -1 )
                return false;
        }
        return true;
    }
};