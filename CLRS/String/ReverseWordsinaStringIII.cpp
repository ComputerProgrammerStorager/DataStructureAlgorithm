/*
Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

 

Example 1:

Input: s = "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
Example 2:

Input: s = "God Ding"
Output: "doG gniD"
 

Constraints:

1 <= s.length <= 5 * 104
s contains printable ASCII characters.
s does not contain any leading or trailing spaces.
There is at least one word in s.
All the words in s are separated by a single space.

*/

// using the built-in reserve function 
class Solution {
public:
    string reverseWords(string s) {
        string res;
        for ( int i = 0; i < s.size(); i++ )
        {
            int j = i; 
            while ( j < s.size() && s[j] != ' ' )
                j++;
            string tmp = s.substr(i,j-i);
            reverse(tmp.begin(),tmp.end());
            res += tmp + " ";
            i = j;
        }
        res.pop_back();
        return res;
    }
};

// without using the built in function 
class Solution {
public:
    string reverseWords(string s) {
        string res;
        for ( int i = 0; i < s.size(); i++ )
        {
            string tmp;
            int j = i;
            while ( j < s.size() && s[j] != ' ' )
                tmp.insert(tmp.begin(),s[j++]);
            res += tmp + " ";
            i = j;
        }
        res.pop_back();
        return res;
    }
};