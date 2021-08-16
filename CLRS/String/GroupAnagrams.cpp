/*
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.


Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:

Input: strs = [""]
Output: [[""]]
Example 3:

Input: strs = ["a"]
Output: [["a"]]
 

Constraints:

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] consists of lower-case English letters.xs
*/

#include "../Common/common_api.h"

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        vector<vector<string>> res;
        for ( auto s : strs )
        {
            int ch[26];
            for ( int i = 0; i < s.size(); i++ )
            {
                ch[s[i]-'a']++;
            }
            
            string key;
            for ( int i = 0; i < 26; i++ )
            {
                if( ch[i] != 0 )
                    key += to_string(i) + "+" + to_string(ch[i]);
            }
            m[key].push_back(s);
        }
        
        for ( auto it : m )
            res.push_back(it.second);
        
        return res;
    }
};

int main()
{
    vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
    Solution s;
    s.groupAnagrams(strs);
}